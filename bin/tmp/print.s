# Program: Hello, World!
	.data # data declaration section; specifies values to be stored
# in memory and labels whereby the values are accessed
new_line: .asciiz "\n"
	.text # Start of code section
main: # Execution begins at label "main"
	li $v0, 1 # system call code for printing integer = 1
	li $a0, 3
	syscall # call operating system to perform operation;
	li $v0, 4 # system call code for printing string = 4
	la $a0, new_line
	syscall
	li $v0, 5 # system call code for reading integer = 5
	syscall # call operating system to perform operation;
	move $a0, $v0
	li $v0, 1 # system call code for printing string = 1
	syscall
	li $v0, 4 # system call code for printing string = 4
	la $a0, new_line
	syscall

