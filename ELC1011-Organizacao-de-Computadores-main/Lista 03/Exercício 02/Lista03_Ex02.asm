.data
	array: .word  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	var_I: .word 0
	var_J: .word 0
	var_K: .word 0
	var_ACC: .word 0

.text
	#i = 1
        addi, $s0, $zero, 1  #i = 1
        la $t0, var_I  #$t0 -> end(i)
        sw $s0, 0($t0) #$t0 = i
        
        #j = 3
        addi $s1, $zero, 2  #j = 2
	la $t0, var_J #$t0-> end(j)
	sw $s1, 0($t0) #$t0 = j
        
        #k = 4
        addi $s2, $zero, 4  #k = 4
	la $t0, var_K #$t0-> end(k)
	sw $s2, 0($t0) #$t0 = k	
	
	#acc = 0
	addi $s3, $zero, 0 #acc = 0
	la $t0, var_ACC #$t0 -> end(acc)
	sw $s3, 0($t0) #$t0 = acc
	
	la $t0, array #$t0 = array[0]
	
	#Dois registradores para fazermos o controle do final do nosso branch, $s0 o valor base(0) e $t9 o valor alvo(10)
	li $s0, 0
	li $t9, 10
	#primeiro for = for(i=0; i<10; i++)
	increment_array:
		beq $s0, $t9, end_increment_array #i = 0; i < 10; 
		move $t1, $s0    #aux = i
		sll $t1, $t1, 2 #aux = i*4
		add $t1, $t0, $t1 #aux = endereço array[i]
		lw $t2, 0($t1) #aux2 = array[i]
		add $t2, $t2, 3 #aux2 +=3
		sw $t2, 0($t1) #array[i] = aux2
		addi $s0, $s0, 1 #i++
		j increment_array
	end_increment_array:
		
	#i = 0
	li $s0, 0
	#for de fora = for(i=0; i<10; i++)	
	outer_for:
		beq $s0, $t9, end_outer_for #i = 0; i < 10
		move $s1, $s0 #j = 0
		#for de dentro = for(j=i; i<10; j++)
		inner_for:
			beq $s1, $t9, end_inner_for #j = i; j < 10
			move $t1, $s1 #aux = j
			sll $t1, $t1, 2 #aux = j*4
			add $t1, $t0, $t1 #aux = endereço array[j]
			lw $t2, 0($t1) #aux2 = array[j]
			add $s3, $s3, $t2 #acc +=array[j]
			addi $s1, $s1, 1 #j++
			j inner_for
		end_inner_for:
		addi $s0, $s0, 1 #i++
		j outer_for
	end_outer_for:
	sw $s3, 24($t0) #array[6] = acc
	
	#laço while = while(a[k] < acc)
	laco_while:
		move $t1, $s2 #aux = k

	 	sll $t1, $t1, 2 #aux = k*4
		add $t1, $t0, $t1 #aux = enderço array[k]
		lw $t2, 0($t1) #aux2 = array[k]
		ble $s3, $t2, end_laco_while
		#bgt  $t2, $s3, end_laco_while #(a[k] < acc)
		addi $t2, $t2, 10 #aux2 +=10
		sw $t2, 0($t1) #array[k] = aux2
		j laco_while
	end_laco_while:

	lw $t1, 32($t0) #aux = array[8]
	laco_do_while:
		addi $t2, $t2, 1 #array[k] + 1
		sw $t2, 28($t0) #array[7] = array[k] + 1
		lw $t3, 28($t0) #aux2 = array[7]
		bge $t3, $t1, end_laco_do_while #salta se a[7] for maior ou igual a a[8]
		j laco_do_while
	end_laco_do_while:
	
	#print do array
	li, $t2, 40
	move $t0, $zero
	print_array:
		beq $t0, $t2, end_print_array
		li $v0, 1
		lw $a0, array($t0)
		syscall
		addi $t0, $t0, 4
		j print_array
	end_print_array:
