## Modularização

- Agrupam-se as funções relacionadas em módulos. Para cada módulo são utilizados dois arquivos:
    
- Declarações (arquivos **.h**)
    - Contém apenas as declarações das funções (protótipos) e das constantes
    
- Implementação (arquivos **.c**)
    - Contém a implementação das funções declaradas no arquivo _.h_ correspondente
    - Inclui o arquivo _.h_ correspondente
    
- Para usar uma função em outro módulo, basta então incluir o arquivo _.h_ correspondente

### Criação do _header_ da biblioteca de funções

- Para exemplificar, criaremos uma biblioteca simples de funções matemáticas
    
- Primeiro, escrevemos os protótipos das funções no arquivo **bibfunc.h**:

```cpp
float fatorial(int v);
float somatorio(int v);
...
```
- Porém, se por engano esse arquivo for incluído mais de uma vez, haverá uma duplicidade de todas as definições
- Como isso pode acontecer facilmente, acrescentamos 3 linhas no arquivo _.h_:
```cpp
#ifndef BIBFUNC_H
#define BIBFUNC_H

float fatorial(int v);
float somatorio(int v);
...
#endif
```
    
- Essas linhas contêm comandos do pré-processador, que definem um símbolo `BIBFUNC_H` caso este ainda não exista
- Se existir, é porque o arquivo já foi incluído e portanto, o pré-processador pula o código até o _#endif_
### Implementação das funções

- A seguir, escrevemos o arquivo **bibfunc.c**, que contém a implementação das funções definidas anteriormente
	-  Note que este arquivo **deve incluir** o arquivo _bibfunc.h_
    
```cpp
#include "bibfunc.h"

float fatorial(int v) {
	int res = 1, i;
	for(i=1; i<=v; i++) res = res * i;
	return res;
}

float somatorio(int v) {
	float soma = 0, i;
	for(i=1; i<=v; i++) soma += i;
	return soma;
}
```
### Programa principal

- Finalmente, o programa principal deve ser implementado em um arquivo separado, como por exemplo **main.c**:
	-  Observe que o arquivo _bibfunc.h_ também deve ser incluído, pois contém a definição das funções

```cpp
#include <stdio.h>
#include "bibfunc.h"

int main()
{
	int v;
	printf("Digite um valor: ");
	scanf("%d", &v);
	printf("Fatorial: %f\n", fatorial(v));
	printf("Somatório: %f\n", somatorio(v));
	...
}
```
    
## Compilação dos módulos
- Para compilar o programa completo, é preciso indicar todos os fontes na linha de comando:
    `gcc -o main main.c bibfunc.c
    
    ![[Pasted image 20240626154025.png]]
- Porém, essa estratégia tem algumas implicações:
    
    - Todos os módulos são SEMPRE compilados novamente
    - Mas e se apenas mudar a implementação das funções?
    - E se apenas o programa principal mudar?
    
- Para um programa tão pequeno, isso não faz tanta diferença...
    
- Mas se o programa for composto por muitos módulos, compilá-los separadamente pode ter um custo considerável, além de não ser muito prático

- Uma solução é compilar individualmente cada módulo:
```
gcc -c bibfunc.c
gcc -c main.c
```
![[Pasted image 20240626154321.png]]

- O comando `gcc -c...` apenas **compila** um módulo especificado, gerando o **código objeto** sem ligação com bibliotecas (arquivo .o)
    
- Finalmente, geramos o **programa executável**, ligando os módulos e as bibliotecas do sistema:
    
```
gcc -o main main.o bibfunc.o
```
    
- Mas como decidir **quais** módulos precisam ser compilados?

### Compilação modular: _Makefiles_

- Um _Makefile_ é um **roteiro de compilação**:
    - Informa as dependências entre os arquivos
    - Indica os comandos necessários para a compilação
    
- Para utilizá-lo, basta digitar o comando _make_ no terminal
```
all: main

main: main.o bibfunc.o
    gcc -o main main.o bibfunc.o

main.o: main.c
    gcc -c main.c

bibfunc.o: bibfunc.c
    gcc -c bibfunc.c
```

* É possível definir regras genêricas:
```
CFLAGS = -Wall -g    # Opções do compilador: todos warnings e debug info

PROG = main
FONTES = main.c bibfunc.c
OBJETOS = $(FONTES:.c=.o)

$(PROG): $(OBJETOS)
    gcc $(CFLAGS) $(OBJETOS) -o $@

clean:
    -@ rm -f $(OBJETOS) $(PROG)
```

- `PROG = ...` define o nome do programa executável
- `FONTES = ...` define todos os módulos
- `OBJETOS = ...` define como transformar um .cpp em um .o
- `clean` permite apagar os arquivos _.o_ e executável gerados (`make clean`)

- Se estiver disponível, o comando `makedepend` pode ser usado para gerar automaticamente todas as dependências dos módulos:
	- Ao digitarmos `make depend`, o comando `makedepend` será ativado, e verificará as dependências de cada módulo, incluindo estas no final do próprio _Makefile_:
    
```
...
clean:
	-@ rm -f $(OBJETOS)

depend:
	makedepend -- ${CFLAGS} -- ${FONTES}

# DO NOT DELETE

main.o: bibfunc.h
bibfunc.o: bibfunc.h
```
### Alternativas ao make
    
- [Scons](http://www_scons.org) - escrito em Python, oferece uma sintaxe mais flexível, é multiplataforma e tem diversos recursos interessantes
	
- [CMake (Cross-Platform Make)](http://cmake.org) - este sistema tem o objetivo de gerar _Makefiles_ adaptados para a plataforma de compilação
	
- [QMake](http://qt-project.org/doc/qt-4.8/qmake-manual.html) - outro sistema semelhante, normalmente distribuído com o toolkit _Qt_, também multiplataforma
	
- [Boost.Build](http://www.boost.org/boost-build2/) - específico para C++, também multiplataforma e com uma sintaxe simples
	
- [GNU Build System (autotools)](https://en.wikipedia.org/wiki/GNU_build_system) - sistema mais utilizado atualmente para instalação de software no _Linux/Unix_ (Com software adicional instalado, pode ser utilizado também no _Windows_)
    
- Obs: projetos criados em IDEs como _Visual Studio_, _Code::Blocks_, _Qt Creator_, _XCode_, _NetBeans_, etc... simplesmente automatizam essa tarefa