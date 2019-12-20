	global main
	extern atoi
	extern printf
	extern puts

	section .text
main:
	push rbp ; save caller register

	cmp rdi, 2 ; check if exactly one input given
	jne throwError ; if not, throw error
	mov rdi, [rsi + 8] ; atoi(argv[1])
	call atoi ; save input as int in eax
	movsxd rbp, eax ; save converted input for later
	cmp rbp, 0 ; check if given 0 or non-numeric
        je printProb ; if so, prob a leap year since 0 divides 4
divByFour:
	xor rdi, rdi ; clear dividend
	mov rsi, rbp ; set dividend low
	mov rcx, 4 ; set divisor
	div rcx ; store quotient in rdx
checkResult:
	cmp rdx, 0 ; check if input divisible by 4
	jne printProbNot; prob not a leap year
printProb:
	mov rdi, probIsLeapYear ; arg1: string format
        mov rsi, rbp  ; arg 2: input
	xor rax, rax ; arg3: varargs
	call printf ; printf(arg1, arg2, arg3)
	jmp exit
printProbNot:
	mov rdi, probNotLeapYear ; arg1: string format
        mov rsi, rbp ; arg2: input
	xor rax, rax ; arg3: varargs
	call printf ; printf(arg1, arg2, arg3)
	jmp exit
throwError:
	mov rdi, inputCountError ; arg: error string
	call puts ; puts(arg)
	jmp exit
exit:
	pop rbp ; restore caller register
	ret ; exit

	section .data
inputCountError:
	db "This program requires exactly one command line argument specifying a year.", 0
probNotLeapYear:
	db "%d is probably not a leap year", 10, 0
probIsLeapYear:
	db "%d is probably a leap year", 10, 0

