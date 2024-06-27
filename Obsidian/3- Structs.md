## Registro (ou _struct_)

- Tipo de dado estruturado heterogêneo
    
- Coleção de variáveis referenciadas sob um mesmo nome
    
- Permite agrupar dados de diferentes tipos numa mesma estrutura (ao contrário de _arrays_, que possuem elementos de um mesmo tipo)
    - Cada componente de um registro pode ser de um tipo diferente (int, char, ...)
        
    - Estes componentes são referenciados por um **nome**
        
    - Os elementos do registro são chamados de **campos** ou **membros** da _struct_
## Definindo uma _struct

- Uma _struct_ é uma **definição de tipo** (deve ser definida antes de ser usada, normalmente antes das funções)
    
- Por conveniência, em geral também se usa uma **substituição de tipo** (_typedef_), de forma que o nome da _struct_ possa ser usado diretamente no código
```cpp
#include <stdio.h>

typedef struct {
	float p1;
	float p2;
	float trab;
	int faltas;
} Aluno;
```

## Definindo e utilizando variáveis do tipo criado

- Para se definir e utilizar variáveis do tipo especificado pela _struct_, faz-se simplesmente:
    
```cpp
int main()
{
	Aluno aluno1, aluno2;

	aluno1.p1 = 10;
	aluno1.p2 = 7.5;
	aluno1.trab = 8;
	...
	aluno2.p1 = 6.5;
	aluno2.p2 = 4.8;
	...
}
```
    
- O acesso aos campos utiliza a mesma notação empregada em Java para acessar elementos públicos de uma classe (o operador ".")
## Considerações no uso

- Se o compilador C for compatível com o padrão _C ANSI_ (praticamente todos atualmente):
    
    - Informação contida em uma _struct_ pode ser atribuída a outra _struct_ do mesmo tipo
        
        - Ex: `aluno2 = aluno1`
        - Todos os campos de _aluno2_ receberão os valores correspondentes aos campos de _aluno1_

# Passagem de parâmetros com _structs_
## Passagem por valor com _structs_

- _Structs_ podem ser passadas por valor ou por referência
    
- Exemplo: função recebe uma _struct_ representando uma fração, calcula e retorna o valor armazenado
    
```cpp
typedef struct {
  float numerador;
  float denominador;
} Fracao;

float calcula(Fracao frac) {
  return frac.numerador / frac.denominador;
}

int main() {
  Fracao f1;
  f1.numerador = 10;
  f1.denominador = 2;
  printf("Valor: %f\n", calcula(f1));
}
```
## Passagem por referência com _structs_

- Na verdade, é recomendado passar por referência, pois o custo é menor (passa apenas um ponteiro ao invés de copiar a variável inteira)
    
- Nesse caso, como é enviado um ponteiro, o acesso deve ser feito da seguinte forma:
```cpp
float calcula(Fracao* frac) {
	return (*frac).numerador / (*frac).denominador);  
}
```
    
- Uma forma mais curta e direta é através do operador seta (**->**):
```cpp
float calcula(Fracao* frac) {
	return frac->numerador / frac->denominador;  
}
```