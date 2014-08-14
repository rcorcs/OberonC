#file "tmp/P2.OBE"
	.data
_a:	.word	0
new_line_str:	.asciiz "\n"
str_1:	.asciiz "Digite um valor: "
str_2:	.asciiz "O valor digitado foi "
	 .text
main:
	nop
	li $v0, 4
	la $a0, str_1
	syscall
	li $v0, 5
	syscall
	la $a0, _a
	sw $v0, 0($a0), 
	li $v0, 4
	la $a0, str_2
	syscall
	li $v0, 1
	la $a0, _a
	lw $a0, 0($a0), 
	syscall
	li $v0, 4
	la $a0, new_line_str
	syscall
	jr $ra
