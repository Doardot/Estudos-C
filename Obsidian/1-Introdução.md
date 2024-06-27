## Tipos de dados em C

- _char_, _int_, _float_, _double_: tipos numéricos básicos
    - _char_, caractere representado em 1 byte com sinal (-128 a 127) ou sem sinal (0 a 255)
    
    - Podem ser combinados com modificadores:
        - _short_: forma curta
        - _long_: forma longa (às vezes igual ao sem modificador)
        - _unsigned_: representação sem sinal (somente positivos)
        - _signed_: representação com sinal (default)
    
- Na prática:
	- _short int_ <= _int_ <= _long int_
	- _float_ <= _double_ <= _long double_

- Exemplo de entrada com a função _scanf_:
```
int i;
scanf("%d", &i);
```

- Exemplo completo em C
```
#include <stdio.h>

int main()
{
  int valor1, valor2;
  printf("Digite os dois valores: ");
  scanf("%d %d", &valor1, &valor2);
  printf("Você digitou: %d e %d\n", valor1, valor);
}
```

- Modificadores de formato para printf/scanf
![[Pasted image 20240625104321.png]]
[Tabela completa](https://en.cppreference.com/w/c/io/fprintf)

### Vetores e matrizes
- Estruturas de dados **homogêneas**
    - Armazenam vários valores, mas todos de um mesmo tipo (ex: todos _int_, _double_, _float_ ou _char_)
    
- Declaração de _arrays_ unidimensionais ("vetores") em C:
```
int v[10];  // vetor de 10 inteiros (0-9)
char s[30]; // vetor de 30 caracteres (0-29)
```
    
- Declaração de _arrays_ com mais de uma dimensão ("matrizes"):
```
int mat[4][4];    // matriz 4x4, 16 inteiros
float c[6][4][2]; // matriz 6x4x2, 48 reais
```

- Acesso é feito através do operador [ ]
```
int v[10], i;
for(i=0; i<10; i++)
  v[i] = i;
...
```
    
- Idem para matrizes:
```
int mat[4][4], i, j;
for(i=0; i<4; i++)
  for(j=0; j<4; j++)
	v[i][j] = i;
...
```
