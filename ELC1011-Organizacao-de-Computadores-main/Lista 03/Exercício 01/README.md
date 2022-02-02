# Exercício 01 da Lista 03 da disciplina.

## Traduzir para Assembly MIPS o código em C:

```
int a[10]={0,1,2,3,4,5,6,7,8,9};
int i, j, k;

int main(void){
  i = 1;
  goto abc;
  
  def:
  j = 1;
  k = 4;
  goto ghi;
  i = 2;
  
  abc:
  goto def;
  
  ghi:
  if (i==j){
    a[2] = a[3];
  }else{
    a[2] = a[4];
  }
  
  while(k>0){
    a[k] = 7;
    k = k - 1;
  }
  
  if((i>k) && (i<10)){
    if((k==6) || (j>=i)){
      a[9] = 400;
    }else{
    a[9] = 500;
    }
  }
  
  switch(j){
    case 0: a[6] = 4; break;
    case 1: a[6] = 5; break;
    case 2: a[6] = 6; break;
    case 3: a[6] = 7; break;
  }
}

```
