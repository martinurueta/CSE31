.data
	myMessage : .asciiz "Hello World\n"


.text
main:
	li $v0, 4
	la $a0, myMessage
	syscall
	
