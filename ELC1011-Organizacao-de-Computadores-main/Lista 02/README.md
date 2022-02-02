# Exercício 02 da Lista 02 da disciplina.

## Traduzir para Assembly MIPS o código em C:

```
int a[10]={0,1,2,3,4,5,6,7,8,9};
int i, j, k;

int main(void){
  i = 1;
  j = 3;
  k = 4;
  a[1] = 5;
  a[2] = a[3] + 20;
  a[3] = a[4] + 200000;
  a[4] = 10000;
  a[5] = a[6] + a[7] - a[8];
  a[6] = a[7] + i;
  a[7] = a[8] - a[i];
  a[j] = a[i+2] - i + j;
  a[k];
}
```
