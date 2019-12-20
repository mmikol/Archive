	global main
	extern puts

	section	.text
main:
    cmp rdi, 2 ; exactly one input must be given
    jl useDefaultPathname ; if none, use default pathname
    jg showError ; if several, error
    mov rdi, [rsi + 8] ; pathname is argv[1]
    jmp createDir
useDefaultPathname:
    mov rdi, defaultPathname ; pathname is untitled
createDir:
    mov rax, 83 ; system call for mkdir
    mov rsi, 755  ; user may r-w-e, others may e
    syscall ; make directory
    ret
showError:
    mov rdi, inputErrorMsg ; address of string to output
    call puts ; puts(inputErrorMsg)
    ret

    section .data
defaultPathname:
    db "untitled", 0
inputErrorMsg:
    db "ERROR: only one folder name may be given.", 0