		.data
x:		.word 5
y:		.word 10
m:		.word 15
b:		.word 2

		.text
MAIN:	la $t0, x
		lw $s0, 0($t0)		# s0 = x   5
		la $t0, y
		lw $s1, 0($t0)		# s1 = y   10
		
		# Prepare to call sum(x)
		add $a0, $zero, $s0	# Set a0 as input argument for SUM    a0 = 5
		jal SUM
		add $t0, $s1, $s0  #t0 = 5 + 10 = 15
		add $s1, $t0, $v0  #s1 = 15 + 23 = 38
		addi $a0, $s1, 0  #a0 = 38
		li $v0, 1		 
		syscall	
		j END

		
SUM: 	addi $sp, $sp, -4		
		sw $s0, 0($sp)		# Backup s0 from MAIN        sp = [5]
        	la $t0, m
		lw $s0, 0($t0)		# s0 = 15
        	addi $sp, $sp, -4
        	sw $a0, 0($sp)      # Backup a0 from SUM  sp = [5,5]
		add $a0, $s0, $a0	# Update a0 as new argument for SUB a0 = 20
        	addi $sp, $sp, -4
        	sw $ra, 0($sp)      # Backup ra to return to MAIN sp =[5,5,ra]
		jal SUB
		lw $a0, 4($sp)	#a0 = 5
		lw $s0, 8($sp)  #s0 = 5
		add $v0, $a0, $v0 # v0 = 23
        	lw $ra, 0($sp) # $ra = ra(of line 15) to return back to 
		jr $ra		
		
SUB:	la $t0, b  # t0 = 2
		addi $sp, $sp -4
		sw $s0, 0($sp)		# Backup s0 from SUM sp =[5,5,ra,15]
		lw $s0, 0($t0)		# s0 = 2
		sub $v0, $a0, $s0	# v0 = 18
		lw $s0, 0($sp)		# Restore s0 from SUM  s0 = 15
		addi $sp, $sp 4		
		jr $ra

		
END:
