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
        j abc #goto abc
        
        
        def:
        	#j = 1
        	addi $s1, $zero, 1  #j = 3
		la $t0, var_J #$t0-> end(j)
		sw $s1, 0($t0) #$t0 = j
        	#k = 4
        	addi $s2, $zero, 4  #k = 4
		la $t0, var_K #$t0-> end(k)
		sw $s2, 0($t0) #$t0 = k	
		j ghi #goto def
	
	li $s0, 2 #i = 2
	
	abc:
		j def #goto def
	
	
	ghi:
		la $t0, array #$t0 = array[0]
		
		#if (i==j)
		beq $s0, $s1, if_true #comparar se i == j, se sim vai para if_true
			lw $t1, 16($t0) #aux = array[4]
			sw $t1, 8($t0) #array[2] = aux
			j end_if
		if_true:
			lw $t1, 12($t0) #aux = array[3]
			sw $t1, 8($t0) #array[2] = aux
		end_if_true:

		#while(k>0)
		while:
			blez $s2, end_while #if k == 0, branch e sai do loop
			move $t1, $s2 #aux = k
			sll $t1, $t1, 2 #aux = k*4
			add $t1, $t1, $t0 #aux = endereço array[k]
			li $t2, 7 #aux2 = 7
			sw $t2, 0($t1) #a[k] = aux2
			subi $s2, $s2, 1
			j while
		end_while:
		
		#if((i>k) && (i<10))
		ble $s0, $s2, end_if #if(i>k) segue na execuçao, senao pula
		bgt $s0, 10, end_if #if(i<100) segue na execuçao, senao pula
		
		#if((k==6) || (j>=i))
		inner_if:
			beq $s2, 6, inner_if_true #if k == 6 já vai para o procedimento
			bge $s1, $s0, inner_if_true # ou if j>=1 vai para o procedimento
			#else
			li $t1, 500 #aux = 500
			sw $t1, 36($t0) #array[9] = aux
			j end_inner_if
			inner_if_true:		
			li $t1, 400 #aux = 500
			sw $t1, 36($t0) #array[9] = aux
			end_inner_if:
		end_if:
		
		#switch case para o j podendo ser = 0, 1, 2, 3
		beq $s1, 0, case_0
		beq $s1, 1, case_1
		beq $s1, 2, case_2
		beq $s1, 3, case_3
		
		case_0:	
			li $t1, 4 #aux = 4
			sw, $t1, 24($t0) #array[6] = aux
			j end_case #break
		case_1:	
			li $t1, 5 #aux = 5
			sw, $t1, 24($t0) #array[6] = aux
			j end_case #break
		case_2:	
			li $t1, 6 #aux = 6
			sw, $t1, 24($t0) #array[6] = aux
			j end_case #break
		case_3:	
			li $t1, 7 #aux = 7
			sw, $t1, 24($t0) #array[6] = aux
			j end_case #break

		end_case:
		

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
