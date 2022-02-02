function integral_12(f, a, b, m)
  h = (b - a)/m;
  
  res_trap = 0;
  for i = 1 : m
    t = a + (i*h); 
    res_trap += 2 * f(t);
  endfor
  res_trap += f(a);
  res_trap *= (h/2);
 
  printf("\nRegra dos trap�zios repetida: %f \n", res_trap);
  
  
  
  con = 4;  
  res_simp = 0;
  for i = 1:(m-1)
    s = i*h;
    res_simp += con*f(s);
    if (con == 4)
      con = 2;
    else
      con = 4;
    endif
  endfor
  res_simp += f(a);
  res_simp += f(b);
  res_simp *= (h/3);  

  printf("\nRegra 1/3 de Simpson repetida: %f \n", res_simp);
  endfunction
