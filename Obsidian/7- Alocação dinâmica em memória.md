## 1- Layout de memória de um processo em execução no Linux:

![[program_in_memory2.png]]

- _User stack_: armazena **todas as variáveis locais** de uma função, registradores, endereço de retorno, etc
	
- _Runtime heap_: **compartilhado por todos os processos** em execução no sistema, usado para **alocação dinâmica**
    
- _Read-write segment_: as variáveis globais de um programa
    
- _Read-only segment_: o código do programa (pode ser compartilhado entre instâncias)

### Limites
- Podem ser consultados e alterados pela linha de comando: o comando _ulimit_
	`ulimit -a`

```c
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
...
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 15333
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```
#### Tamanho da pilha é limitado!

- A parte importante é destacada abaixo:

```c
...
stack size              (kbytes, -s) 8192
...
```
- O tamanho da pilha para qualquer processo é 8192 Kb, i.e. **8 Mb**

## 2- Alocação dinâmica 

- Resolve o problema de armazenar grandes quantidades de dados na pilha
    
- Também nos permite alocar memória que irá persistir além do escopo de uma função
    - Por exemplo, para estruturas encadeadas (listas, etc)
    
- Lembre-se do layout de memória: alocação dinâmica usa memória do **runtime heap**
    
- Precisamos usar **funções** para gerenciar memória dinamicamente

### Funções para gerência de memória

- Geralmente presentes no header `stdlib.h`
    
- Para **alocar memória**, usamos [_malloc_, _calloc_ ou _realloc_](obsidian://open?vault=2024-Workflow&file=Estudos%2F3%20SEM%2FC%2F7.1%20-%20malloc%2C%20calloc%2C%20realloc):
```c
void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void* realloc(void* ptr, size_t size);
```

- Para **liberar memória**, usamos _free_:
```c
void free(void* ptr);
```

- `size_t` é um tipo sem sinal de pelo menos 16 bits (geralmente é um _unsigned int_)

### Alocando memória: malloc

- O **ponteiro void** é um ponteiro para uma área de memória cujo tipo não é definido (pode apontar para qualquer coisa - _array_ de _int_, _char_, …)
    
- A função `malloc` é a mais simples - tenta alocar _size_ bytes de memória, retorna ponteiro para o bloco (NULL se falhar)
```c
void* malloc(size_t size);
```

- Usar quantidade desejada de bytes, ou seja, usando `sizeof`:
```c
// Aloca um array de 10 int
int* numbers = malloc(sizeof(int) * 10);
// Faz o mesmo, e é considerado mais seguro
int* numbers = malloc(10 * sizeof *numbers);
```

### Alocando memória: calloc

- A função `calloc` aloca memória para um array de _nmemb_ itens, onde cada um requer _size_ bytes
    
- Também inicializa a memória com **zeros** (`malloc` não faz isso)
    
```c
void* calloc(size_t nmemb, size_t size);
```

- O exemplo anterior com `calloc`:  
```c
// Aloca e zera um array de 10 int
int* numbers = calloc(10, sizeof *numbers));
```

### Alocando memória: realloc

- A função `realloc` altera o tamanho de um bloco já alocado (_ptr_)
    - Se é maior e não cabe, a função irá movê-lo para outro lugar e liberar o ponteiro original
        
    - Retorna um ponteiro para o novo bloco alocado

```c
void* realloc(void* ptr, size_t size);
```

- Exemplo: criando espaço para mais 20 _int_ no array
```c
int* newarray = realloc(numbers, 30);
```
### Liberando memória

- Para liberar memória alocada dinamicamente, precisamos chamar a função `free`, passando o ponteio do bloco de memória para ela:
```c
void free(void* ptr);
```

- Exemplo: liberando o array de inteiros
```c
free(numbers);
```

- **Observação importante**: não há **garbage collection** em C, portanto lembre-se de liberar **toda** a memória alocada dinamicamente
# 3. Exemplo com alocação dinâmica

- Jeito errado:
```c
#include <stdio.h>
#define SIZE 2000000 // dois milhões
int main()
{
    double array[SIZE];
    printf("tam. mem: %zu\n", sizeof(double)*SIZE);
    for(int i=0; i<SIZE; i++)
        array[i] = i;
}
```

- Jeito certo usando alocação dinâmica:
```c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000000 // dois milhões
int main()
{
   double* array = malloc(sizeof *array * SIZE);
   printf("tam. mem: %zu\n", sizeof *array * SIZE);
   for(int i=0; i<SIZE; i++)
      array[i] = i;
   free(array);
}
```

# 4. Alocação de matrizes
- Uma matriz pode ser vista como memória linear, ou como uma estrutura realmente bidimensional
    ![[realmatrix.png]]
- O primeiro caso é simples - se desejamos uma matriz 5x5 de _int_, podemos fazer:
```c
int* mat = malloc(5 * 5 * sizeof *mat);
```

- Mas agora o problema é acessar através de um índice único:
```c
mat[0] = 1; // armazena 1 na pos (0,0)
mat[1] = 2; // armazena 2 na pos (0,1)
...
mat[4] = 5; // armazena 5 na pos (0,4)
mat[5] = 6; // armazena 6 na pos (1,0)
...
// genericamente: mat[5 * linha + coluna] = valor;
```

### Alocando dinamicamente uma matriz

- Para trabalhar com dois índices, precisamos primeiro alocar um array de linhas:
```c
int** mat = malloc(5 * sizeof(int*));
```

- Então, para cada linha, alocamos espaço para as colunas:
```c
for(int i=0; i<5; i++)
mat[i] = malloc(5 * sizeof(int));
```
    
- Agora basta usar o operador de matriz:
```c
// Armazena 6 na pos (1,0)
mat[1][0] = 6;
```
    
- **Obs**: isto provavelmente impedirá a alocação contígua das linhas
- ![[jaggedmatrix.png]]

### Liberando a memória da matriz

- Para liberar a matriz, basta reverter o processo
    
- Primeiro liberamos cada linha, e depois liberamos o array de linhas:
```c
for(int i=0; i<5; i++)
  free(mat[i]);
free(mat);
```

### Método alternativo usando uma única chamada
- Outra opção, se o compilador C suportar o padrão C99 (_variable-length arrays_)
    
- Alocar uma matriz inteira **em uma única chamada**:
```c
int n = 5;
int (*mat)[n] = malloc(n * sizeof *mat);
```
    
- Usar normalmente:
```c
...
mat[1][0] = 6; // armazena 6 na pos (1,0)
```
    
- E liberar no final:
```c
free(mat);
```

# 5. Estruturas Encadeadas

### Estruturas Encadeadas

- Alocação dinâmica é **essencial** para a criação de estruturas dinâmicas usuais, como listas encadeadas, pilhas, filas, árvores e grafos.

### Criando uma lista encadeada

- Por exemplo, o nodo de uma lista poderia ser pensado assim:
```c
typedef struct {
    int data;
    Node* next;
} Node;
```

- Porém, isso **não funciona**: C não permite uma auto-referência para um tipo que **está sendo definido neste momento**.

- A solução é definir um nome **temporário** para a definição da struct:
```c
typedef struct TNode {
    int data;
    struct TNode* next;
} Node;
```

- Uma estrutura de lista então poderia ser definida assim:
```c
typedef struct {
    Node* head;
    Node* tail;
    int size;   // conveniente sempre saber o tamanho
} List;
```

- Basta criar agora um conjunto de funções para manipular _List_ e _Node_.