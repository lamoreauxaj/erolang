     .data
.extern ero_write
.extern ero_plane
.extern ero_sphere
.extern ero_line
.extern ero_point
.extern ero_intersection
.extern ero_point_on
.extern ero_center
.extern ero_endpoints
.extern ero_segment
.extern ero_ray
.extern ero_arc
.extern ero_equals
format: .byte '%', '.', '2', 'f', 10, 0
v0_a: .quad 13
v1_a: .quad 0
v0_arc: .quad 11
v1_arc: .quad ero_arc
v0_b: .quad 13
v1_b: .quad 0
v0_c: .quad 13
v1_c: .quad 0
v0_center: .quad 11
v1_center: .quad ero_center
v0_circ: .quad 13
v1_circ: .quad 0
v0_endpoints: .quad 11
v1_endpoints: .quad ero_endpoints
v0_false: .quad 14
v1_false: .quad 0
v0_intersection: .quad 11
v1_intersection: .quad ero_intersection
v0_line: .quad 11
v1_line: .quad ero_line
v0_plane: .quad 11
v1_plane: .quad ero_plane
v0_pln: .quad 13
v1_pln: .quad 0
v0_point: .quad 11
v1_point: .quad ero_point
v0_point_on: .quad 11
v1_point_on: .quad ero_point_on
v0_ray: .quad 11
v1_ray: .quad ero_ray
v0_segment: .quad 11
v1_segment: .quad ero_segment
v0_sphere: .quad 11
v1_sphere: .quad ero_sphere
v0_sphr: .quad 13
v1_sphr: .quad 0
v0_true: .quad 14
v1_true: .quad 1
v0_write: .quad 11
v1_write: .quad ero_write
     .text
    .extern printf
    .global main
main:
     push %rbp
     mov %rsp, %rbp
     push v1_point(%rip)
     push v0_point(%rip)
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdi
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rsi
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdx
     mov 56(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
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
     push v1_point(%rip)
     push v0_point(%rip)
     pushw $16368
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdi
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rsi
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdx
     mov 56(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     push %rdx
     push %rax
     mov (%rsp), %rax
     mov %rax, v0_a(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_a(%rip)
     pop %rax
     pop %rax
     push v1_point(%rip)
     push v0_point(%rip)
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdi
     pushw $16368
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rsi
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     pushw $0
     mov %rsp, %rdx
     mov 56(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     push %rdx
     push %rax
     mov (%rsp), %rax
     mov %rax, v0_b(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_b(%rip)
     pop %rax
     pop %rax
     push v1_plane(%rip)
     push v0_plane(%rip)
     push v1_a(%rip)
     push v0_a(%rip)
     mov %rsp, %rdi
     push v1_b(%rip)
     push v0_b(%rip)
     mov %rsp, %rsi
     push v1_c(%rip)
     push v0_c(%rip)
     mov %rsp, %rdx
     mov 56(%rsp), %rax
     call *%rax
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     pop %rbx
     push %rdx
     push %rax
     mov (%rsp), %rax
     mov %rax, v0_pln(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_pln(%rip)
     pop %rax
     pop %rax
     push v1_sphere(%rip)
     push v0_sphere(%rip)
     push v1_c(%rip)
     push v0_c(%rip)
     mov %rsp, %rdi
     push v1_a(%rip)
     push v0_a(%rip)
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
     mov %rax, v0_sphr(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_sphr(%rip)
     pop %rax
     pop %rax
     push v1_intersection(%rip)
     push v0_intersection(%rip)
     push v1_pln(%rip)
     push v0_pln(%rip)
     mov %rsp, %rdi
     push v1_sphr(%rip)
     push v0_sphr(%rip)
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
     mov %rax, v0_circ(%rip)
     mov 8(%rsp), %rax
     mov %rax, v1_circ(%rip)
     pop %rax
     pop %rax
     push v1_write(%rip)
     push v0_write(%rip)
     push v1_circ(%rip)
     push v0_circ(%rip)
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
