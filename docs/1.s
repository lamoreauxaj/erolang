     .data
.extern ero_write
.extern ero_equals
format: .byte '%', '.', '2', 'f', 10, 0
v0_a: .quad 13
v1_a: .quad 0
v0_add: .quad 13
v1_add: .quad 0
v0_b: .quad 13
v1_b: .quad 0
v0_c: .quad 13
v1_c: .quad 0
v0_false: .quad 14
v1_false: .quad 0
v0_true: .quad 14
v1_true: .quad 1
v0_write: .quad 11
v1_write: .quad ero_write
     .text
    .extern printf
    .global main
f_1:
     push %rbp
     mov %rsp, %rbp
     sub $48, %rsp
     mov (%rdi), %rax
     mov %rax, -16(%rbp)
     mov 8(%rdi), %rax
     mov %rax, -8(%rbp)
     mov (%rsi), %rax
     mov %rax, -32(%rbp)
     mov 8(%rsi), %rax
     mov %rax, -24(%rbp)
     push -8(%rbp)
     push -16(%rbp)
     push -24(%rbp)
     push -32(%rbp)
     movsd 0x18(%rsp), %xmm0
     addsd 0x8(%rsp), %xmm0
     movsd %xmm0, 0x18(%rsp)
     add $16, %rsp
     pushw $16384
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     movsd 0x18(%rsp), %xmm0
     addsd 0x8(%rsp), %xmm0
     movsd %xmm0, 0x18(%rsp)
     add $16, %rsp
     mov (%rsp), %rax
     mov %rax, -48(%rbp)
     mov 8(%rsp), %rax
     mov %rax, -40(%rbp)
     pop %rax
     pop %rax
     mov -48(%rbp), %rax
     mov -40(%rbp), %rdx
     add $48, %rsp
     pop %rbp
     ret
main:
     push %rbp
     mov %rsp, %rbp
     push $f_1
     push $11
     mov (%rsp), %rax
     mov %rax, v0_add(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_add(%rip)
     pop %rax
     pop %rax
     pushw $16392
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov (%rsp), %rax
     mov %rax, v0_a(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_a(%rip)
     pop %rax
     pop %rax
     pushw $16400
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov (%rsp), %rax
     mov %rax, v0_b(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_b(%rip)
     pop %rax
     pop %rax
     push v1_add(%rip)
     push v0_add(%rip)
     push v1_a(%rip)
     push v0_a(%rip)
     mov %rsp, %rdi
     push v1_b(%rip)
     push v0_b(%rip)
     mov %rsp, %rsi
     mov 40(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     push %rdx
     push %rax
     mov (%rsp), %rax
     mov %rax, v0_c(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_c(%rip)
     pop %rax
     pop %rax
     push v1_write(%rip)
     push v0_write(%rip)
     push v1_c(%rip)
     push v0_c(%rip)
     mov %rsp, %rdi
     mov 24(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     push %rdx
     push %rax
     pop %rax
     pop %rax
     pop %rbp
     ret
