#include "compile.h"

map<int, map<string, Data>> scope_levels;
queue<Node*> function_queue;

void compile_expr(Expr *expr);

int16_t pack(int16_t v) {
    return ((v & 0xff) << 8) | ((v & 0xff00) >> 8);
}

void compile_real_expr(RealExpr *expr) {
    double tmp = stod(expr->val.text);
    uint64_t val = *((uint64_t*) &tmp);
    // not really sure if endianness is correct here
    add_to_function("main", "pushw $" + to_string(((int16_t) (val >> 48))));
    add_to_function("main", "pushw $" + to_string(((int16_t) ((val >> 32) & 0xffff))));
    add_to_function("main", "pushw $" + to_string(((int16_t) ((val >> 16) & 0xffff))));
    add_to_function("main", "pushw $" + to_string(((int16_t) (val & 0xffff))));
    add_to_function("main", "pushw $0");
    add_to_function("main", "pushw $" + to_string(sizeof(RealVar)));
    add_to_function("main", "pushw $0");
    add_to_function("main", "pushw $" + to_string((int32_t) (val & 0xffff)));
}

void compile_identifier_expr(IdentifierExpr *expr) {
    // identify shit here
}

void compile_unary_expr(UnaryExpr *expr) {
    compile_expr(expr->val);
}

void compile_addition_op(BinaryExpr *expr) {
    compile_expr(expr->left);
    compile_expr(expr->right);
    // add_to_data("format: .byte 'h', 'e', 'l', 'o', 10, 0");
    add_to_function("main", "movsd 0x18(%rsp), %xmm0");
    add_to_function("main", "addsd 0x8(%rsp), %xmm0");
    add_to_function("main", "movsd %xmm0, 0x18(%rsp)");
    add_to_function("main", "add $16, %rsp");
    // add_to_function("main", "movq $4611686018427387904, %rax");
    // add_to_function("main", "movq %rax, %xmm0");
    // add_to_function("main", "movsd 0x8(%rsp), %xmm0");
    // add_to_function("main", "lea format(%rip), %rdi");
    // add_to_function("main", "mov $1, %eax");
    // add_to_function("main", "sub $8, %rsp");
    // add_to_function("main", "call printf");
    // add_to_function("main", "add $8, %rsp");
    // add_to_function("main", "add $16, %rsp");
    // add_to_function("main", "pop %rax");
}

void compile_assign_op(BinaryExpr *expr) {
    if (expr->left->type != IDENTIFIEREXPR) {
        log_error("expected identifier as lvalue");
        return;
    }
    compile_expr(expr->right);
    // compile_expr(expr->left);
    IdentifierExpr *lvalue = (IdentifierExpr*) expr->left;
    string name = "v_" + lvalue->val.text;
    add_to_function("main", "pop %rax");
    add_to_function("main", "mov %rax, p0" + name + "(%rip)");
    add_to_function("main", "pop %rax");
    add_to_function("main", "mov %rax, p1" + name + "(%rip)");
}

void compile_binary_expr(BinaryExpr *expr) {
    if (expr->op.type == PLUS) compile_addition_op(expr);
    else if (expr->op.type == ASSIGN) compile_assign_op(expr);
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
    else {
        log_error("unknown expr type");
        return;
    }
}

void compile_expr_stmt(ExprStmt *stmt) {
    compile_expr(stmt->expr);
}

void compile_if_stmt(IfStmt *stmt) {

}

void compile_while_stmt(WhileStmt *stmt) {

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
    for (auto p : scope_levels[0]) {
        add_to_data("p0" + p.second.pos + ": .quad 0");
        add_to_data("p1" + p.second.pos + ": .quad 0");
        // cout << p.first << " " << p.second.pos << "\n";
    }
}

void compile(Stmts *tree) {
    scope_levels = scope_variables(tree);
    compile_data_segment();
    compile_stmts(tree);
    add_to_function("main", "ret");
    add_to_data("format: .byte '%', '.', '2', 'f', 10, 0");
}
