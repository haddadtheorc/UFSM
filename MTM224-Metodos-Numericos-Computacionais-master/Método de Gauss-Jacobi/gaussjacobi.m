function gaussjacobi_12 (A, b, x0, e)

  i =  0;
  n = size (A,1);
    
  #construcao do C
  m = rows(A);
  n = size(A, 1);
  C = zeros (n, m);

  for i = 1 : m
    for j = 1 : n 
      if (i == j)
        C(i, j) = 0;
      else
        C(i, j) = -A(i, j) / A(i, i);
      endif
    endfor
  endfor  
  C 
  ###  
  
  
  #construcao do g
  g = zeros (n, 1);

  for i = 1: n
    g (i,1) = b(i,1) / A(i,i);
  endfor
  g
  ###
  
   
  x1 = 0;
  i = 0;

  
  while (true)  
    
   x1 = C*x0+g ; 
   i++;
   d =  max(abs(x1-x0));   
   
   if(d < e)  
      break
   endif
   
   x0 = x1;
   
   endwhile

  printf("o numero de iteracoes foi de %d \n", i); 
  printf("a solucao aproximada x encontrada foi\n");
  x1
 
endfunction
