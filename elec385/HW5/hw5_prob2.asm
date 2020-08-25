               .data
Test:          .ascii    "1 abc dsjf 3 4 30"

               .text
               la        $t0, Test                 # message
               li        $t1, 0                    # iterator
search:        lb        $t2, 0($t0)               # load char
               beq       $t2, $0, exit
               add       $t2,$t2,4
exit:          li        $v0, 10                   # system call for exit
               syscall                             # terminate program
