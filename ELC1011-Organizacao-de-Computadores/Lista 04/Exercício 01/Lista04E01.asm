
.data 
valor1: .word 0
valor2: .word 0


.text
.globl      main

# iniciamos o programa
init:

	jal main           
finit:                              # terminamos o programa
	addu    $a0, $zero, $v0 # fazemos o valor de retorno do programa igual o retorno de main
	addi    $v0, $zero, 17  # escolhemos o serviÃ§o 17: exit2, termina o programa
	syscall                 # fazemos uma chamada ao sistema
# terminamos o programa

procedimento3:
	# ajuste da pilha
	addiu $sp, $sp, -8    
	# guardamos o valor do registrador $s0
	sw $s0, 0($sp)   
	sw $ra, 4($sp)
	#branch se y >= x
	bge $a0, $a1, end_if
		# tmp = x;
		move $s0, $a0
		# x = y;
		move $a0, $a1
		# y = tmp;
		move $a1, $s0
	end_if:
	#branch se x <= y
	while:
		ble $a0, $a1, end_while
		# x = x - 1;
		subi $a0, $a0, 1
		# y = y + 1;
		addi $a1, $a1, 1
		j while
	end_while:
	# return x;
	move $v0, $a0
	# restauração da pilha
	lw $s0, 0($sp)         
	lw $ra, 4($sp)
	addiu $sp, $sp, 8
	# retrorno ao procedimento chamador
	jr  $ra        
	
	 
procedimento2:
	# ajuste da pilha
	addiu $sp, $sp, -20
	sw $ra, 16($sp)
	sw $s3, 12($sp)
	sw $s2, 8($sp)
	sw $s1, 4($sp)
	sw $s0, 0($sp)
	
	#argumento 1 = x
	move $a0, $s0 
	# argumento 2 = valor1
	lw $a1, valor1
	# chamada do procedimento3
	jal procedimento3
	# resultado = procedimento3(x, valor1);
	move $s2, $v0
	
	#argumento 1 = x
	move $a0, $s0 
	# argumento 2 = valor2
	lw $a1, valor2
	# chamada do procedimento3
	jal procedimento3
	sub $s2, $s2, $v0
	
	# return resultado;
	move $v0, $s2

	# restauração da pilha
	lw $s0, 0($sp)         
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $s3, 12($sp)
	lw $ra, 16($sp)
	addiu $sp, $sp, 20
	# retrorno ao procedimento chamador
	jr  $ra    
		
		
procedimento1: 
	# ajuste da pilha
	addiu $sp, $sp, -16
	sw $ra, 12($sp)
	sw $s2, 8($sp)
	sw $s1, 4($sp)
	sw $s0, 0($sp)
	
	li $s0, 0 #int acumulador = 0
	li $s1, 0 #aux
	li $s2, 0 #int i = 0;
	
	for:
		beq $s2, 10, end_for
	
		move $s1, $s2 # aux = i
		mul $s1 $s1, $a0 # aux = i * x
		# aux = i * x + y
		add $s1, $s1, $a1 		
		#argumento 1 = aux
		move $a0, $s1 

		# chamada do proc
		jal procedimento2 

		# aux = procedimento2(aux)
		move $s1, $v0

		# acumulador = acumulador + aux		
		add $s0, $s0, $s1 
		
		addi $s2, $s2, 1 #i++
		
		j for

	end_for:
		# return resultado;
		move $v0, $s0
		
	# restauração da pilha
	lw $s0, 0($sp)         
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $ra, 12($sp)
	addiu $sp, $sp, 16
	# retrorno ao procedimento chamador
	jr  $ra   

            
main:
	# ajuste da pilha
	addiu $sp, $sp, -16
	sw $ra, 12($sp)
	sw $s2, 8($sp)
	sw $s1, 4($sp)
	sw $s0, 0($sp)
        
        # $s0 = 10
        li $s0, 10
        # $t0 = endereço de valor1
        la $t0,  valor1 
        #valor1 = 3
        sw $s0, 0($t0)
         # $s0 = 20
        li $s0, 20
        # $t0 = endereço de valor2
        la $t0,  valor2 
        #valor1 = 3
        sw $s0, 0($t0)

        
        # n = 5;
	li $s0, 5     
	# m = 3;
	li $s1, 3
	# argumento 1 = n
	move $a0, $s0 
	# argumento 2 = m
	move $a1, $s1
	# chamada do procedimento2
	jal procedimento1
	# resultado = procedimento2(n, m);
	move $s2, $v0
	# printf(resultado)
	li $v0, 1
	move $a0, $s2
	syscall
	# restauração da pilha
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $ra, 12($sp)
	addiu $sp, $sp, 16
	# retrorno ao procedimento chamador
