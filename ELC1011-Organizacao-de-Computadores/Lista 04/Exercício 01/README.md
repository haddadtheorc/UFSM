# Exercício 01 da Lista 04 da disciplina.

## Traduzir para Assembly MIPS o código em C:

```
int valor1 = 10;
int valor2 = 20;

int procedimento3(int x, int y) {
  int tmp;

  if (x < y) {
    tmp = x;
    x = y;
    y = tmp;
  }

  while (x > y) {
    x = x - 1;
    y = y + 1;
  }

  return x;
}

int procedimento2(int x) {
  int resultado;
  resultado = procedimento3(x, valor1) - procedimento3(x, valor2);
  return resultado;
}

int procedimento1(int x, int y) {
  int vetorA[10];
  int i;
  int acumulador;
  
  acumulador = 0;
  for (int i = 0; i < 10; i++) {
    vetorA[i] = i * x + y;
    vetorA[i] = procedimento2(vetorA[i]);
    acumulador = acumulador + vetorA[i];
    }
  return acumulador;
}

int main(void) {
  int n;
  int m;
  int resultado;
  n = 5;
  m = 3;
  
  resultado = procedimento1(n, m);
  return 0;
}
```
