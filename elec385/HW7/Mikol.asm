# Registers Used
# $s0 - stores iterator
# $t1 - stores current address for Notes
# $t2 - stores current address for Dur

         .eqv    E, 250
         .eqv    Q, 500
         .eqv    QQ, 700
         .eqv    H, 1000

         .data
Notes:   .word   72, 77, 72, 65, 72, 77, 72, 1
         .word   72, 77, 72, 77, 81, 1, 79, 77, 76, 75, 74
         .word   72, 77, 72, 65, 72, 77, 72, 1
         .word   77, 74, 72, 70, 69, 67, 65, 0

Dur:     .word   Q, Q, Q, Q, Q, Q, H, Q
         .word   Q, Q, Q, Q, QQ, Q, Q, E, E, E, E
         .word   Q, Q, Q, Q, Q, Q, H, Q
         .word   QQ, Q, Q, Q, Q, Q, Q, 0

         .text
Init:    xor     $s0, $s0, $s0                          # clear iterator
         la      $t1, Notes                             # save address of Notes
         la      $t2, Dur                               # save address of Dur
         
Play:    li      $v0, 31                                # system call for MIDI Out
         lw      $a0, 0($t1)                            # set pitch
         lw      $a1, 0($t2)                            # set note duration
         li      $a2, 25                                # set instrument to acoustic guitar
         li      $a3, 100                               # set volume to 100/120
         syscall                                        # MIDI Out
         jal     Sleep                                  # call nested sleep function 
         addi    $s0, $s0, 1                            # increment iterator
         beq     $s0, 35, Exit                          # exit if all elements seen
         addi    $t1, $t1, 4                            # set index of next note
         addi    $t2, $t2, 4                            # set index of next duration
         j       Play                                   # loop until song is complete
         
Sleep:   li      $v0, 32                                # system call for sleep
         li      $a0, 400                               # sleep duration is 400ms
         syscall                                        # Sleep
         jr      $ra                                    # function return

Exit:    li      $v0, 10                                # system call for exit
  	 syscall                                        # Exit

