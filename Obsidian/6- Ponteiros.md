- Cada variável em um programa C é armazenada em algum lugar na memória
- A linguagem possui um operador para obter esses endereços: o operador **&**
    
- Por exemplo, vamos exibir o endereço de uma variável:
```cpp
int main()
{
	int b = 200;
	printf("%p\n", &b);
}
```
- O operador **&** retorna o endereço do seu operando
- O modificador **%p** exibe o valor como um end. de memória em hexa

- Definição: uma variável que armazena um **endereço de memória** (usualmente de outra variável)
    
- Por exemplo: criando um ponteiro para a variável _b_ (chamado _a_):
```cpp
int main()
{
	int b = 200;
	int* a = &b;
}
```
    
- O operador * declara que _a_ é um **ponteiro para um int**
- ![[Pasted image 20240626170143.png]]

## Ponteiros podem ser maus: falha de segmentação

- Precisamos ter certeza de sempre usar **ponteiros válidos**
- Um ponteiro válido é um ponteiro que aponta para uma área de memória válida (usualmente uma variável no programa)
- Se esquecermos de atribuir um valor ao ponteiro e tentarmos usá-lo, **coisas ruins podem acontecer!**
    
```cpp
int main()
{
	int a = 200;
	int* b;
	printf("Conteúdo apontado por b: %d\n", *b); // oops!
}
```
    
- Este código provavelmente irá gerar uma **falha de segmentação** no Linux

## O ponteiro NULL

- É considerada uma prática saudável armazenar o valor _NULL_ em ponteiros não inicializados
    - _NULL_ é simplesmente uma constante definida como ZERO
    
- No código, pode ser usado com segurança para testar se um ponteiro está inicializado ou não:
```cpp
int main()
{
	int a = 200;
	int* b = NULL;
	...
	if(b != NULL)
		printf("Conteúdo apontado por b: %d\n", *b); // b é válido
	else
		printf("Ponteiro inválido!\n");
}
```

## Ponteiros e _arrays_

- Em C, um _array_ é armazenado como um **ponteiro para o seu primeiro elemento**
- Os demais elementos são armazenados contiguamente a partir do end. inicial
    
- Por exemplo:
```cpp
char c[10];
```
    
- _c_ é um ponteiro para uma área de memória capaz de armazenar 10 _char_
- Portanto, o tamanho da área de memória é 10 * sizeof(char) = 10 bytes
### _Arrays_ são sempre passados por referência

- Uma consequência interessante dessa implementação é que os _arrays_ são **sempre** passados por referência:
```cpp
void incArray(int v[]) {
  int c;
  for(c=0; c<10; c++)
	v[c]++;
}

int main() {
  int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  incArray(data);
}
```
    
- Ou podemos escrever a função desta forma:
```cpp
void incArray(int* v) {
...
```

### Aritmética de ponteiros

- Considerando o seguinte _array_ de _char_:
```cpp
char c[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
```
    
- Podemos declarar um ponteiro _p_ para ele:
```cpp
char* p = c; // não precisa &, c já é um ponteiro
```
    
- E agora _p_ é o **mesmo** que _c_:
```cpp
printf("%c\n", *p);    // exibe o primeiro elemento do array
printf("%c\n", p[0]);  // idem

printf("%p\n", p);     // exibe o endereço do primeiro elemento
printf("%p\n", c);     // idem
printf("%p\n", &c[0]); // idem
```

- A _aritmética de ponteiros_ nos permite acessar outros elementos através do operador de adição:

![chararray](https://www.inf.pucrs.br/flash/progswb2/present/U02_pointers/pointers/C_language_pointer_arithmetic_chars.png)

```cpp
char* p = c;

printf("%c\n", *p);     // exibe 'a'
printf("%c\n", *(p+1)); // exibe 'b'
printf("%c\n", *(p+2)); // exibe 'c'
printf("%c\n", *(p+3)); // exibe 'd'
...
```

- Se o _array_ armazena _ints_, o pŕóximo elemento estará a **4 bytes** de distância
- O tamanho da área de memória será 10 * sizeof(int) = 40 bytes
    
![intarray](https://www.inf.pucrs.br/flash/progswb2/present/U02_pointers/pointers/C_language_pointer_arithmetic_ints.png)

```cpp
int m[] = { 3, 2, 1, 4, 5, 6, 9, 8, 7, 10 };

printf("%p\n", m);     // end. do primeiro elem., e.g. 0x7fff5fbfebf8
printf("%p\n", &m[0]); // idem
printf("%p\n", m+1);   // end. do segundo elem., e.g. 0x7fff5fbfebfc
printf("%p\n", &m[1]); // idem
```

### Experimento: aritmética de ponteiros

- Compare os seguintes programas:

```cpp
#include <stdio.h>

int main()
{
    int vet[] = { 4, 9, 12 };
    int i, *ptr;
    ptr = vet;
    for(i =0; i<3; i++)
        printf("%d ", *ptr++);
    return 1;
}
```
- No primeiro programa, o ponteiro `ptr` é incrementado para apontar para o próximo elemento do array, resultando na impressão dos valores originais do array `4 9 12`.

```cpp
#include <stdio.h>

int main()
{
    int vet[] = { 4, 9, 12 };
    int i, *ptr;
    ptr = vet;
    for(i =0; i<3; i++)
        printf("%d ", (*ptr)++);
    return 1;
}
```
- No segundo programa, o valor do elemento apontado por `ptr` é incrementado a cada iteração, resultando na impressão de `4 5 6` e modificando o primeiro elemento do array a cada passo.