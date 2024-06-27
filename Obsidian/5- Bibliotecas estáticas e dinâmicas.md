**No Windows, as chamadas para "make" devem ser trocadas para "mingw32-make".**

# 1- Ligação estática x dinâmica

![[Pasted image 20240626160232.png]]

As bibliotecas são incluídas na etapa de ligação (_linking_), que é normalmente feita de forma automática pelo compilador.

Há duas formas de ligação:
- **Estática**: os módulos são incorporados diretamente no código-objeto, isto é, o programa executável resultante conterá todo o código utilizado de cada módulo.

- **Dinâmica**: os módulos são referenciados no código-objeto, mas não incluídos no programa executável.

## 1.1- Ligação estática

A **ligação estática** é o que ocorre normalmente ao compilarmos um programa com vários módulos (exemplo: várias funções, separadas em arquivos diferentes). Cada código-fonte é compilado e produz um arquivo com código objeto equivalente (.c para .o, no caso do Linux).

É possível também ligar bibliotecas de forma estática. Uma **biblioteca** nada mais é do que uma coleção de módulos, contendo funcionalidades relacionadas (ex: biblioteca de funções matemáticas, biblioteca gráfica, etc). 
	No Linux, bibliotecas estáticas são arquivos com o sufixo .a (de _archive_) e são criadas com o aplicativo *ar*.

As bibliotecas estáticas normalmente ficam nos diretórios _/usr/lib_ ou _/usr/local/lib_. Por exemplo, verifique o conteúdo de _/usr/lib_:
```
ls /usr/lib/*.a
```

Se a biblioteca já estiver no diretório _/usr/lib_, você pode especificá-la na linha de comando de forma mais simples, com a opção **-l** (letra “L” minúscula:):
	A opção _-l_ faz com que o ligador procure a biblioteca com o prefixo _lib..._, ou seja, no caso acima ele irá procurar em _/usr/lib/libz.a_
```
gcc -o programa programa.c -lz
```

É possível também especificar um ou mais diretórios adicionais de busca, com a opção **-L**:
```
gcc -o programa programa.c -L/usr/local/lib -lgraphics
```

### 1.2- Criando uma biblioteca estática

Para criar uma biblioteca estática, utiliza-se a seguinte linha de comando:
```
ar rcs minhalib.a modulo1.o modulo2.o modulo3.o ...
```

- Onde _minhalib.a_ é o nome do arquivo resultante e _modulo*.o_ são os diversos módulos a ser inseridos na biblioteca.

Uma vez criada a biblioteca, basta especificá-la na linha de comando do compilador:
```
gcc -o programa programa.c minhalib.a
```

- Considerando que _minhalib.a_ e _programa.c_ estejam no mesmo diretório, esse comando irá utilizar a biblioteca durante a fase de ligação. **Observação**: mesmo assim, para compilar o programa é necessário ter acesso aos _headers_ (.h) utilizados pela biblioteca.
## 1.3- Ligação dinâmica

Atualmente, a forma mais comum do uso de bibliotecas é através de **ligação dinâmica**. Isso significa que o código executável (programa) não irá mais conter todo os módulos utilizados de cada biblioteca, mas apenas uma referência para eles.

- No momento da execução, o sistema operacional identifica essas referências e carrega as bibliotecas necessárias, automaticamente.

- Isso torna o código menor, e permite que a implementação interna das bibliotecas sofra alterações, sem que seja necessário recompilar todos os programas que dependem dela.

- Isso também tem um efeito colateral benéfico: o sistema consegue manter uma cópia de cada biblioteca utilizada na memória, e compartilha ela com todos os programas que a utilizam.

Existe um comando que permite identificar as ligações dinâmicas de um executável, denominado _ldd_. Por exemplo, para visualizar as ligações dinâmicas do programa:
```
ldd glshapes
```

- O sufixo _.so_ significa _shared object_, ou seja, objeto compartilhado. O comando também informa a **localização** das bibliotecas.

### 1.4 Criando uma biblioteca dinâmica
Para criar uma biblioteca dinâmica, utiliza-se o próprio _gcc._ Acrescente as seguintes linhas ao _Makefile_:
```
libshapes2.so: $(OBJETOS2)
	gcc -fPIC -shared -o libshapes2.so $(OBJETOS2) $(LDFLAGS)
```

- A opção _-fPIC_ significa que o compilador deve gerar _position independent code_, isto é, código sem endereçamento absoluto, que pode ser carregado em qualquer ponto da memória. Já a opção _-shared_ indica a geração de uma biblioteca dinâmica.
- Uma vez criada, a biblioteca dinâmica é utilizada da mesma forma que a estática, ou seja, através da opção -l do compilador.

- A última etapa é adicionar uma regra para criar um executável que use a biblioteca dinâmica:
```
glshapes-shared: $(OBJETOS) libshapes2.so
	$(CC) $(OBJETOS) -o glshapes-shared -L. -lshapes2 $(LDFLAGS)
```