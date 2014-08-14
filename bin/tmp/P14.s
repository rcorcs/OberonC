#file "tmp/P14.OBE"
	.data
_a:	.word	0
_b:	.word	0
new_line_str:	.asciiz "\n"
str_1:	.asciiz "Digite um numero: "
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
	j L1
L3:
	nop
	li $t0, 2
	la $t9, _a
	lw $t9, 0($t9)
	bne $t0, $t9, L4
	nop
	j L2
	j L5
L4:
	nop
L5:
	li $v0, 1
	la $a0, _a
	lw $a0, 0($a0), 
	syscall
	li $v0, 4
	la $a0, new_line_str
	syscall
	la $t0, _a
	lw $t0, 0($t0)
	li $t9, 1
	sub $t0, $t0, $t9
	la $t9, _a
	sw $t0, 0($t9)
L1:
	li $t0, 0
	la $t9, _a
	lw $t9, 0($t9)
	ble $t0, $t9, L3
	j L2
L2:
	jr $ra
