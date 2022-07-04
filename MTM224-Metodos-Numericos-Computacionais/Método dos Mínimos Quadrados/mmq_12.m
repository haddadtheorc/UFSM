function mmq_12(x,y,g)
  
  n = rows(g);
  m = rows(x);
 
  #Matriz A
  for i = 1:n
    for j = 1:n
      A(i,j)=0;
      for c = 1:m
        A(i, j) = A(i, j) + ( g{i}(x(c)) * g{j}(x(c)) );
      endfor
    endfor
  endfor
        
        
  #Matriz B
  for i = 1:n
    b(i) = 0;
    for c = 1:m
      b(i) = b(i)+ ( y(c) * g{i} (x(c)) );
    endfor
  endfor
  b = transpose(b);
  
  
  #Alpha
  alpha = inv(A) * b;
  
  
  #Resultados
  printf("Alpha = \n")
  disp(alpha)
  
endfunction
