			.text
			.globl main
main:
			j label
			add $1, $2, $3
			addi $4, $5, 100
label:
			sub $8, $7, $6
			nop
			mul $13, $24, $12
			sw $3, 4($5)
			lw $4, 4($5)
			beq $4, $3, main
			sll $4, $6, 2
			srl $7, $3, 2
