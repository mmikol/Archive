        global  gcd       ; uint64_t gcd(uint64_t x, uint64_t y)
        section .text
gcd:
        cmp rsi, 0

        jne recursiveCall ; if y != 0, recurse
        mov rax, rdi ; else gcd is x
        ret
recursiveCall:        
        xor rdx, rdx ; clear dividend high
        mov rax, rdi ; set dividend low to x
        div rsi ; save remainder in rdx

        mov rdi, rsi ; x = y
        mov rsi, rdx ; y = x % y

        call gcd

        ret