function secante_12(f, x0, x1, erro)

  i = 0; 
  flag = true;
  
  while(flag)
    
    if(abs(f(x1))<erro && abs(x1-x0)<erro) #critério de parada para sair do laço de repetição
      flag=false;
    endif  
    
    x2 = x1 - (x1-x0)/(f(x1)-f(x0)) * f(x1)

    i++;
    
    x0 = x1;
    x1 = x2; 
      
  endwhile
  
  printf("o numero de iteracoes eh i = %d \n", i);
  printf("a raiz aproximada eh x = %.15f \n", x1);
    
endfunction
