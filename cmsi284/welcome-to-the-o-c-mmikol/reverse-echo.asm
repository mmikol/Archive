	global main
	extern puts
    extern strlen
	extern reverse_range_in_place  ; Look ma, no .h

	section .text
main:
	push rdi ; save num of args
    push rsi ; save index in args
    sub rsp, 8 ; must align stack before call
    mov rbp, rsi ; save string to callee reg
    mov rdi, [rbp] ; get length of string arg
    
    call strlen ; save string length to rax

    mov rdi, [rsi] ; string to reverse
    mov rsi, 0 ; start index
	mov rdx, rax; end index

	call reverse_range_in_place
   
	mov rdi, [rbp] ; print reversed string

    call puts

    add rsp, 8 ; restore %rsp to pre-aligned value
    pop rsi ; restore registers puts used
    pop rdi

    add rsi, 8 ; point to next argument
    dec rdi ; decrease num of args
    jnz main ; if args still remain, recurse

	ret