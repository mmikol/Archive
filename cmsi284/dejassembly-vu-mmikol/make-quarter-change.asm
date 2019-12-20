	global main
	extern atoi
	extern printf
	extern puts

	section	.text
main:
	push rbp ; save caller register

	cmp rdi, 2 ; check if exactly one input given
	jne throwErr ; if not, throw error
	mov rdi, [rsi +  8] ; atoi(argv[1])
	call atoi ; save input as int in eax
	movsxd rbp, eax ; save converted input for later
        cmp rbp, 0 ;  check if input is  0 or non-numeric
        je print ; if so, just print a result
divByTwentyFive:
	xor rdi, rdi ; clear dividend
	mov rsi, rbp ; set dividend low
	mov r8, 25 ; set divisor
	div r8 ; store quotient in eax
print:
	mov rdi, result ; arg1: string format
	movsxd rsi, eax ; arg2: quotient
	mov rdx, rbp  ; arg3: input
	xor rax, rax ; arg4: varargs
	call printf ; printf(arg1, arg2, arg3, arg4)
        jmp exit
throwErr:
	mov rdi, inputCountError ; arg: error string
	call puts ; puts(arg)
exit:
	pop rbp ; restore caller register
	ret ; exit

	section .data
inputCountError:
	db "This program requires exactly one integer command line argument.", 0
result:
	db "%d quarters make partial change for %d cents", 10, 0

