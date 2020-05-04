#include "compile.h"

queue<Node*> function_queue;

void compile_expr(Expr *expr);
void compile_stmts(Stmts *stmts);

void compile_real_expr(RealExpr *expr) {
    double tmp = stod(expr->val.text);
    uint64_t val = *((uint64_t*) &tmp);
    // not really sure if endianness is correct here
    add_to_function("main", "pushw $" + to_string((int16_t) (val >> 48)));
    add_to_function("main", "pushw $" + to_string((int16_t) ((val >> 32) & 0xffff)));
    add_to_function("main", "pushw $" + to_string((int16_t) ((val >> 16) & 0xffff)));
    add_to_function("main", "pushw $" + to_string((int16_t) (val & 0xffff)));
    add_to_function("main", "pushw $0");
    add_to_function("main", "pushw $0");
    add_to_function("main", "pushw $0");
    add_to_function("main", "pushw $0");
}

void compile_call_expr(CallExpr *expr) {
    compile_expr(expr->val);
    int offset = 8;
    int i = 0;
    for (Expr *arg : expr->args->vals) {
        if (i == 0) {
            compile_expr(arg);
            add_to_function("main", "mov %rsp, %rdi");
        }
        else if (i == 1) {
            compile_expr(arg);
            add_to_function("main", "mov %rsp, %rsi");
        }
        else {
            log_error("too many arguments");
            return;
        }
        offset += 16;
        i++;
    }
    add_to_function("main", "mov " + to_string(offset) + "(%rsp), %rax");
    // add_to_function("main", "sub $8, %rsp");
    add_to_function("main", "call *%rax");
    // add_to_function("main", "add $8, %rsp");
    while (offset > 0) {
        add_to_function("main", "pop %rbx");
        add_to_function("main", "pop %rbx");
        offset -= 16;
    }
    add_to_function("main", "push %rdx");
    add_to_function("main", "push %rax");
}

void compile_identifier_expr(IdentifierExpr *expr) {
    // identify shit here
    string name = expr->val.text;
    Data loc = scope_levels[node_scopes[expr]][name];
    if (loc.loc == DATA_SEGMENT) {
        add_to_function("main", "push v1_" + name + "(%rip)");
        add_to_function("main", "push v0_" + name + "(%rip)");
    }
    else if (loc.loc == STACK) {
        add_to_function("main", "push -" + to_string(loc.pos + 8) + "(%rbp)");
        add_to_function("main", "push -" + to_string(loc.pos + 16) + "(%rbp)");
    }
    else {
        log_error("unexpected data loc");
    }
}

void compile_unary_expr(UnaryExpr *expr) {
    compile_expr(expr->val);
}

void compile_addition_op(BinaryExpr *expr) {
    compile_expr(expr->left);
    compile_expr(expr->right);
    add_to_function("main", "movsd 0x18(%rsp), %xmm0");
    add_to_function("main", "addsd 0x8(%rsp), %xmm0");
    add_to_function("main", "movsd %xmm0, 0x18(%rsp)");
    add_to_function("main", "add $16, %rsp");
}

void compile_is_op(BinaryExpr *expr) {
    compile_expr(expr->left);
    compile_expr(expr->right);
    add_to_function("main", "lea 16(%rsp), %rdi");
    add_to_function("main", "mov %rsp, %rsi");
    add_to_function("main", "call ero_equals");
    add_to_function("main", "pop %rbx");
    add_to_function("main", "pop %rbx");
    add_to_function("main", "pop %rbx");
    add_to_function("main", "pop %rbx");
    add_to_function("main", "push %rdx");
    add_to_function("main", "push %rax");
}

void compile_assign_op(BinaryExpr *expr) {
    if (expr->left->type != IDENTIFIEREXPR) {
        log_error("expected identifier as lvalue");
        return;
    }
    compile_expr(expr->right);
    IdentifierExpr *lvalue = (IdentifierExpr*) expr->left;
    string name = lvalue->val.text;
    Data loc = scope_levels[node_scopes[expr]][name];
    add_to_function("main", "mov (%rsp), %rax");
    if (loc.loc == DATA_SEGMENT)
        add_to_function("main", "mov %rax, v0_" + name + "(%rip)");
    else
        add_to_function("main", "mov %rax, -" + to_string(loc.pos + 16) + "(%rbp)");
    add_to_function("main", "mov 8(%rsp), %rax");
    if (loc.loc == DATA_SEGMENT)
        add_to_function("main", "mov %rax, v1_" + name + "(%rip)");
    else
        add_to_function("main", "mov %rax, -" + to_string(loc.pos + 8) + "(%rbp)");
}

void compile_binary_expr(BinaryExpr *expr) {
    if (expr->op.type == PLUS) compile_addition_op(expr);
    else if (expr->op.type == ASSIGN) compile_assign_op(expr);
    else if (expr->op.type == IS) compile_is_op(expr);
    else {
        log_error("unknown binary operator");
        return;
    }
}

void compile_expr(Expr *expr) {
    if (expr->type == BINARYEXPR) compile_binary_expr((BinaryExpr*) expr);
    else if (expr->type == UNARYEXPR) compile_unary_expr((UnaryExpr*) expr);
    else if (expr->type == REALEXPR) compile_real_expr((RealExpr*) expr);
    else if (expr->type == IDENTIFIEREXPR) compile_identifier_expr((IdentifierExpr*) expr);
    else if (expr->type == CALLEXPR) compile_call_expr((CallExpr*) expr);
    else {
        log_error("unknown expr type");
        return;
    }
}

void compile_expr_stmt(ExprStmt *stmt) {
    compile_expr(stmt->expr);
    add_to_function("main", "pop %rax");
    add_to_function("main", "pop %rax");
}

static int if_counter;
static int while_counter;

void compile_if_stmt(IfStmt *stmt) {
    compile_expr(stmt->cond);
    add_to_function("main", "pop %rax");
    add_to_function("main", "pop %rax");
    add_to_function("main", "cmp $0, %rax");
    string jump_label = "if_" + to_string(if_counter++);
    add_to_function("main", "jz " + jump_label);
    compile_stmts(stmt->block);
    add_to_function("main", jump_label + ":");
}

void compile_while_stmt(WhileStmt *stmt) {
    string loop_label1 = "loop_" + to_string(while_counter++);
    string loop_label2 = "loop_" + to_string(while_counter++);
    add_to_function("main", loop_label1 + ":");
    compile_expr(stmt->cond);
    add_to_function("main", "pop %rax");
    add_to_function("main", "pop %rax");
    add_to_function("main", "cmp $0, %rax");
    add_to_function("main", "jz " + loop_label2);
    compile_stmts(stmt->block);
    add_to_function("main", "jmp " + loop_label1);
    add_to_function("main", loop_label2 + ":");
}

void compile_stmt(Stmt *stmt) {
    if (stmt->type == EXPRSTMT) compile_expr_stmt((ExprStmt*) stmt);
    else if (stmt->type == IFSTMT) compile_if_stmt((IfStmt*) stmt);
    else if (stmt->type == WHILESTMT) compile_while_stmt((WhileStmt*) stmt);
    else {
        log_error("unknown stmt type");
        return;
    }
}

void compile_stmts(Stmts *stmts) {
    for (Stmt *stmt : stmts->stmts) {
        compile_stmt(stmt);
    }
}

void compile_data_segment() {
    add_to_data(".extern ero_write");
    add_to_data(".extern ero_equals");
    add_to_data("format: .byte '%', '.', '2', 'f', 10, 0");
    for (auto p : scope_levels[0]) {
        if (p.second.loc == DATA_SEGMENT) {
            add_to_data("v0_" + p.second.label + ": .quad " + to_string((int64_t) p.second.default_type));
            add_to_data("v1_" + p.second.label + ": .quad " + p.second.default_value);
        }
        // cout << p.first << " " << p.second.pos << "\n";
    }
}

void compile(Stmts *tree) {
    if_counter = 0;
    while_counter = 0;

    scope_variables(tree);
    for (auto p : scope_levels) {
        cout << p.first << ":\n";
        auto scope = p.second;
        for (auto p1 : scope) {
            cout << p1.first << " " << p1.second.tostring() << "\n";
        }
    }
    compile_data_segment();
    add_to_function("main", "push %rbp");
    add_to_function("main", "mov %rsp, %rbp");
    if (stack_size[0] > 0)
        add_to_function("main", "sub $" + to_string(stack_size[0]) + ", %rsp");
    compile_stmts(tree);
    if (stack_size[0] > 0)
        add_to_function("main", "add $" + to_string(stack_size[0]) + ", %rsp");
    add_to_function("main", "pop %rbp");
    add_to_function("main", "ret");
}
