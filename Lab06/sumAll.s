.data 
input: .asciiz "\nEnter a number: "
evenSum: .asciiz "\nSum of even numbers is: "
oddSum: .asciiz "\nSum of odd numbers is: "

.text
main:
	li $v0, 4
	la $a0, input
	syscall
	li $v0, 5
	syscall
 	move $t0, $v0
 	
 	beq $t0, $zero, end
	add $t3, $t0, $zero
	bgt $t3, $zero, poscheck
	blt $t3, $zero, negcheck
	
poscheck:
	beq $t3, 1, odd
	addi $t3, $t3, -2
	beq $t3, 0, even
	j poscheck
	
negcheck:
	beq $t3, -1, odd
	addi $t3, $t3, 2
	beq $t3, 0, even
	j negcheck
		 
even:
 	add $t1, $t1, $t0
 	j main
 
odd:
	add $t2, $t2, $t0
 	j main

end:
	li $v0, 4
 	la $a0, evenSum
	syscall
	li $v0, 1
	la $a0, ($t1)
	syscall
	li $v0, 4
 	la $a0, oddSum
	syscall
	li $v0, 1
 	la $a0, ($t2)
	syscall