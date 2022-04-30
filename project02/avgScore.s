.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100
space: .asciiz " "
nextLine: .asciiz "\n"

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded up) with dropped scores removed: "


.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0   # a0 = lens for selsort(lens)
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it
	move $t0, $v0 # $t0 = ouput of calcSum
	li $v0, 4 
	la $a0, str5 
	syscall 
	div $t0, $t0, $a1
	move $a0, $t0
	li $v0, 1  
	syscall
	
	
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray: # $a0 = array and $a1 = lens
	# Your implementation of printList here	
	move $t0, $0 #$t0 = int i
	move $t1, $a0 #$t1 = array
print:
	sll $t2, $t0, 2 
	add $t2, $t2, $t1
	lw $a0, 0($t2) # a0 = array[i]
	li $v0, 1  
	syscall # print array[i]
	li $v0, 4 
	la $a0, space # print " "
	syscall 
	
	addi $t0, $t0, 1
	bne $t0, $a1, print
	li $v0, 4 
	la $a0, nextLine # print "\n"
	syscall 
	
	jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort: # $a0 = lens
	# Your implementation of selSort here
	move $t0, $0 #$ t0 = int i
	move $t7, $a0 # $t7 = $a0 = lens
copy:
	sll $t1, $t0, 2 
	add $t1, $t1, $s1
	lw $v0, 0($t1)
	sll $t2, $t0, 2 
	add $t2, $t2, $s2
	sw $v0, 0($t2)
	addi $t0, $t0, 1
	bne $t0, $a0, copy
	
	move $t0, $0 # $t0 = int i
	
sort_loop1:
	add $t2, $t0, $zero # $t2 = maxindex
	addi $t1, $t0, 1 # $t1 = int j = i+1
	
sort_loop2:
	# sort[j]
	sll $t3, $t1, 2 
	add $t3, $t3, $s2
	lw $t4, 0($t3) # $t4 = sort[j]
	
	#sort[maxindex]
	sll $t5, $t2, 2 
	add $t5, $t5, $s2
	lw $t6, 0($t5) # $t6 = sort[maxindex]
	
	#sort[j] > sort[maxindex]
	blt $t4, $t6, sort_else1
	move $t2, $t1
	
sort_else1:
	addi $t1, $t1, 1
	bne $t1, $a0, sort_loop2
	
	#sort[maxindex]
	sll $t5, $t2, 2 
	add $t5, $t5, $s2
	lw $t6, 0($t5) # $t6 = sort[maxindex] temp = $t6
	
	#sort[i]
	sll $t3, $t0, 2 
	add $t3, $t3, $s2
	lw $t4, 0($t3) # t4 = sort[i]
	
	#sort[maxindex]
	sll $t5, $t2, 2 
	add $t5, $t5, $s2
	sw $t4, 0($t5) # sort[maxindex] = sort[i]
	
	#sort[i]
	sll $t3, $t0, 2 
	add $t3, $t3, $s2
	sw $t6, 0($t3) #s sort[i] = temp
	
	
	addi $t0, $t0, 1 # i = i + 1
	addi $t7, $a0, -1 #make $t7 be lens - 1
	bne $t0, $t7, sort_loop1 # i < lens - 1
	
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum: # $a1 = lens - drop $a0 = array 
	# Your implementation of calcSum here
	move $t2, $0
	move $t3, $a1 # $t3 = lens - drop = $a2
recur:
	addi     $sp, $sp, -8
	sw $ra, 0($sp)
	bgt $t3, $zero, not_zero
	j end_recur
	
not_zero:
	#arr[lens - 1]
	addi $t3, $t3, -1 # lens -1
	
	sll $t0, $t3, 2 
	add $t0, $t0, $a0
	lw $t1, 0($t0) # $t1 = arr[lens - 1]
	sw $t1, 4($sp) #save arr[lens - 1]
	add $t2, $t1, $t2 # $t2 = arr[lens - 1] + $t2
	j recur
	j     end_recur
	
end_recur:    
        lw     $ra, 0($sp)
        addi     $sp, $sp, 8    # Pop stack frame 
        add $v0, $zero, $t2 #v0 = (calcSum(arr, len - 1) + arr[len - 1])
	jr $ra
	
