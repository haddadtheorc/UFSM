.data
	array: .word  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	var_I: .word 0
	var_J: .word 0
	var_K: .word 0

.text
	#i = 1
        addi, $s0, $zero, 1  #i = 1
        la $t0, var_I  #$t0 -> end(i)
        sw $s0, 0($t0) #$t0 = i
        
        #j = 3
        addi $s1, $zero, 3  #j = 3
	la $t0, var_J #$t0-> end(j)
	sw $s1, 0($t0) #$t0 = j
        
        #k = 4
        addi $s2, $zero, 4  #k = 4
	la $t0, var_K #$t0-> end(k)
	sw $s2, 0($t0) #$t0 = k	
	
	la $t0, array #$t0 = array[0]
	
	#array[1] = 5
	li $t1, 5 #aux = 5
	sw $t1, 4($t0) #array[1] = aux 
	
	#array[2] = array[3] + 20;
	lw $t1, 12($t0) #aux = array[3]
	addi $t1, $t1, 20 #aux+=20
	sw $t1, 8($t0) #array[2] = aux
	
	#array[3] = array[4] + 200000
	lw $t1, 16($t0) #aux = array[4]
	addi $t1, $t1, 200000 #aux += 200000
	sw $t1, 12($t0) #array[3] = aux

	#array[4] = 10000
	li $t1, 10000 #aux = 10000
	sw $t1, 16($t0) #array[4] = aux

	#array[5] = array[6] + array[7] - array[8]
	lw $t1, 24($t0) #aux = array[6]
	lw $t2, 28($t0) #aux2 = array[7]
	add $t1, $t1, $t2 #aux += aux2
	lw $t2, 32($t0) #aux2 = array[8]
	sub $t1, $t1, $t2 #aux -= aux2
	sw $t1, 20($t0) #array[4] = aux

	#array[6] = array[7] + i
	lw $t1, 28($t0) #aux = array[7]
	add $t1, $t1, $s0 #aux +=i
	sw $t1, 24($t0) #array[6] = aux

	#array[7] = array[8] - array[i]
	lw $t1, 32($t0) #aux = array[8]
	sll $t2, $s0, 2 #aux2 = i*4
	add $t2, $t0, $t2 #aux2 = endereço array[i]
	lw  $t3, 0($t2) #aux3 = array[i]
	sub $t1, $t1, $t3 #aux-=aux3
	sw $t1, 28($t0) #array[7] = aux

	#a[j] = a[i+2] - i + j
	addi $t2, $s0, 2 #aux2 = i+2
	sll $t2, $t2, 2 #aux2 = (i+2)*4
	add $t2, $t0, $t2 #aux2 = endereço array[i+2]
	lw $t3, 0($t2) #aux3 = array[i+2]
	sub $t3, $t3, $s0 #aux3 -= i
	add $t3, $t3, $s1 #aux3 += j
	sll $t1, $s1, 2 #aux = j*4
	add $t1, $t0, $t1 #aux = endereço array[j]
	sw $t3, 0($t1) #array[j] = aux3
	
	#a[k] = a[a[i]]
	sll $t2, $s0, 2 #aux2 = i*4
	add $t2, $t0, $t2 #aux2 = endereço array[i]
	lw $t3, 0($t2) #aux3 = array[i]
	sll $t3, $t3, 2 #aux3 = array[i]*4
	add $t2, $t0, $t3  #aux2 = endereço array[array[i]]
	lw $t3, 0($t2) #aux3 = array[array[i]]
	sll $t1, $s2, 2 #aux = k*4
	add $t1, $t0, $t1 #aux = endereço array[k]
	sw, $t3, 0($t1) #array[j] = aux3

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