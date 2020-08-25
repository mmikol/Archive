# registers used
# $s0 - holds the count of digits in the input
# $s1 - used to access the input char bytes
# $t0 - is an incrementor used to access the next byte in the input
# $t1 - holds the current character byte being examined
# $t2 - used to load the character byte

        .data
prompt: .asciiz "Input a text string.\n-> "
result: .asciiz "The total number of digits in your string is: "
input:  .space 52

        .text
collect:la $a0, prompt                 # load address of prompt
        li $v0, 4                      # system call for printing a string
        syscall                        # print prompt
        li $v0, 8                      # system call for reading an integer
        la $a0, input                  # save user input at input address
        li $a1, 100                    # max number of characters to read
        syscall                        # collect user input
        
init:   xor $s0, $s0, $s0              # set digit count to 0
        la $s1, input                  # set address of input
        li $t0, 0                      # set incrementor to 0
       
loop:   add $t1, $s1, $t0              # get the char byte
        lb $t2, 0($t1)                 # load the byte
        addi $t0, $t0, 1               # increment to next byte
        beq $t2, $0, show              # continue if char is not \0
        j count                        # check and count if an ascii digit
        j loop                         # break if char is not \0

count:  blt $t2,48,loop                # not an ascii digit if byte < 40
        bgt $t2,57,loop                # not an ascii digit if byte > 58
        addi $s0, $s0, 1               # increment digit count if ascii digit
        j loop                         # return to loop
  
show:   la $a0, result                 # load address of result string
        li $v0, 4                      # system call for printing a string
        syscall                        # print result string
        la $a0, ($s0)                  
        li $v0, 1                      
        syscall                        # print result string

exit:   li $v0, 10                     # system call for exit
        syscall                        # terminate program
