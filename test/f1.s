        .data
input: .asciiz "\nEnter a number: "


        .text
main: 	add     $t0, $0, $zero
		addi    $t1, $zero, 1
		li $v0, 4
		la $a0, input
		syscall
		li $v0, 5
		syscall 
		move $a0, $v0
		
		
f1: 	
        bgt $a0, $zero, if
        ble $a0, $zero, else
		
if:
        addi $a0, $a0, -1
        j end

else:
        add $a1, $a1, $zero
        add $a1, $a0, $a1
        addi $a0, $a0, 2
        j f1
        add $a0, $a1, $a0
        j end
end:
        li $v0, 1
        syscall
        li $v0, 10

