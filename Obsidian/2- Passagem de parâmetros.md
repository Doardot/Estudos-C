### Declaração x definição
- Declaração (funções devem ser declaradas antes)
    - **Protótipo** é o cabeçalho da declaração da função (tipo de retorno + nome + parâmetros)
    
- Definição:
    - Contém todos os comandos da função e inclui a declaração
    
- Caso uma função não seja definida **antes** da _main_ é obrigatório o uso de um protótipo
#### Exemplo

```cpp
#include <stdio.h>

void quadrado(); // protótipo

void quadrado() //sem valor de retorno/parâmetros de entrada
{ // corpo da função}
  int k;   
  for (k=1; k<=10; k++)
	printf("%d\n", k*k);
} 

int main()
{ 
  quadrado(); // chamada da função
}
```

### Passagem de parâmetros
- Os parâmetros são passados para uma função de acordo com a sua posição
    
- Os **parâmetros formais** de uma função se comportam como variáveis locais (criados na entrada e destruídos na saída)
    
- Os argumentos podem ser passados de duas maneiras:
    - Passagem por valor
    - Passagem por referência
### Passagem por valor
- Copia o valor do argumento no parâmetro formal
    
- Alterações feitas nos parâmetros da função **não têm efeito** nas variáveis usadas para chamá-la
    
```cpp
int multiplica (int x) {
  x = x * x;
  return x;
}

int main() {
  int t=10;
  printf("%d - %d\n", multiplica(t), t);
  // saída: 100 10
}
```
### Passagem por referência
- É passado não é o valor de uma variável, mas sim uma **referência** para ela
    
- Alterações feitas nos parâmetros da função afetam as variáveis usadas
    
- Em C, a passagem por referência é feita com **ponteiros**
    - Variável que armazena o endereço de memória de outra variável
        
### Ponteiros na passagem por ref.
- Recebendo e alterando um valor dentro da função

```cpp
void multiplica(int* x) {
	*x = *x * *x;
}

int main() {
	int t = 10;
	multiplica(&t);
	printf("%d\n", t); // saída: 100
}
```

- Para **enviar** um ponteiro: usa-se o operador **&**
- Para **receber** e **acessar** o conteúdo apontado: usa-se o operador *****
### Comparando com Java
- Como isso funciona em Java?
    - Não existe o conceito de “passagem por referência”
    - Tudo é **passado por valor**
### Passagem de vetores para funções
- Em C, vetores são **sempre** passados por referência
    
- Exemplo: função que recebe um vetor com 10 valores, e retorna o maior deles
#### Maior int em vetor de 10 posições
```cpp
int maior(int vetor[], int tam) {
	int m = vetor[0];
	int i;
	for(i=1; i<tam; i++)
		if(vetor[i] > m) m = vetor[i];
	return m;
}

int main() {
	int numeros[10] = {5, 7, 80, 12, 30, 9, 4, 1, 10, 3};
	int valMaior = maior(numeros, 10);
	printf("Maior: %d\n", valMaior);
}
```
