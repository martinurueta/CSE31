.data 

n: .word 25

str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to \n"
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"
input: .asciiz "Enter a number: "


.text
main:
	la $t1, n
	lw $t1, 0($t1)
	li $v0, 4
	la $a0, input
	syscall
	li $v0, 5
	syscall
 	move $t0, $v0
 	
 	#blt $t0, $t1, less
 	#bge $t0, $t1, greatequal
 	
 	bgt $t0, $t1, great
 	ble $t0, $t1, lessequal
 	
great:  
	la $a0, str3
	j end

greatequal:
	la $a0, str4
        j end
        
less:         
	la $a0, str1
        j end
        
lessequal:     
	la $a0, str2
        j end


end:    
	li $v0, 4
	syscall
