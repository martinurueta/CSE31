.text
main:
	addi $t1, $t1, 257
foo:
	add $v0, $v0, $s0
	addi $t1, $t1, -1
	bne $t1, $zero, foo
	j end
end:addi $t1, $t1, 257
	
	