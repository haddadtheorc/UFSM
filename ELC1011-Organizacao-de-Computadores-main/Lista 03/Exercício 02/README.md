# Exercício 02 da Lista 03 da disciplina.

## Traduzir para Assembly MIPS o código em C:

```
int a[10]={0,1,2,3,4,5,6,7,8,9};
int i, j, k;
int acc = 0;

int main(void){
  i = 1;
  j = 2;
  k = 4;
  
  for(i=0; i<10; i++){
    a[i] = a[i] + 3;
  }
  
  for(i=0; i<10; i++){
    for(j = i; j<10; j++){
      acc = acc + a[j];
    }
  }
  
  a[6] = acc;
  
  while(a[k]<acc){
    a[k] = a[k] + 10;
  }
  
  do{
    a[7] = a[k] + 1;
  }while(a[7]<a[8])
}
```
