- Dados numéricos podem ser representados através de várias bases:
    - Decimal
    - Binária
    - Hexadecimal
    - …
- Uma base numérica é apenas uma forma de **interpretar os dados**, mas isso **não altera** o valor armazenado
    
    - Não existe um número “em base 10” que é diferente de um número “em base 2”!
    
- LSB: **least significant bit**, i.e. o bit que contribui **menos** para o valor (menos significativo, bit 0)
    
- MSB: **most significant bit**, i.e. o bit que contribui **mais** para o valor (mais significativo, bit 31)
## 1- Revisando bases numéricas: hexadecimal (base 16)

- Oferece um bom equilíbrio entre a **facilidade** do decimal e a **visão direta** do binário

| Dec | Bin  | Hex | Dec | Bin  | Hex | Dec | Bin  | Hex |
| --- | ---- | --- | --- | ---- | --- | --- | ---- | --- |
| 0   | 0000 | 0   | 6   | 0110 | 6   | 12  | 1100 | C   |
| 1   | 0001 | 1   | 7   | 0111 | 7   | 13  | 1101 | D   |
| 2   | 0010 | 2   | 8   | 1000 | 8   | 14  | 1110 | E   |
| 3   | 0011 | 3   | 9   | 1001 | 9   | 15  | 1111 | F   |
| 4   | 0100 | 4   | 10  | 1010 | A   |     |      |     |
| 5   | 0101 | 5   | 11  | 1011 | B   |     |      |     |
- Base 16 é uma potência de 2 (2^4 ), portanto a conversão entre binário e hex é simples
    
- A partir do bit mais significativo, lê-se 4 bits de cada vez:
```python
	binário: 1111 0000 1010 1110 0001 0100 1110 1100
	hex:       F    0    A    E    1    4    E    C
```
- O mesmo número em hex é: **F0AE14EC**
    - **Mais curto** que o número binário!
    - **Mais legível** que o número binário!
- Converter de volta para decimal é simples:
![](https://mflash.github.io/progswb2/aulas/bits/base_hexadecimal.png)

- Em um programa C, você pode usar exatamente a mesma notação:
```c
unsigned int var;
var = 254;         // decimal
var = 0xFE;        // mesmo em hex
var = 0b11111110   // mesmo em binário
```
- Obs: suporte para binário **está disponível no GCC 4.7+** e alguns outros compiladores (não é padrão)

- Para exibir a saída em hex, use o modificador **%X** na função _printf_:
```c
printf("%02X\n", var);
```
- Obs: **não existe** modificador para exibir números em binário!

- Podemos usar o operador _sizeof_ para obter o tamanho em bytes de qualquer variável ou valor
- _sizeof_ é essencial para manipulação de bits, de forma que se possa saber qual é o bit mais significativo

## 2- Operadores bitwise
- Operadores _bitwise_ são aqueles que manipulam individualmente cada bit dos operandos
    
- Podem ser usados com valores inteiros: _int_, _char_, _short int_, _long int_, de preferência _unsigned_ (e.g, _unsigned int var_)
    
- Dois tipos:
    - Operadores **lógicos**
    - Operadores **de deslocamento**
### Operadores _bitwise_ lógicos

- Aplicam operações lógicas usuais, mas bit a bit

- AND (&)
	- Ambos bits precisam ser 1 para o resultado ser 1
```c
z = x & y; 

printf("AND = %d\n", z); // 0110 & 1100 = 0100
```

 - OR   (|)
	 - Pelo menos 1 bit precisa ser 1 para o resultado ser 1
```c
z = x | y; 

printf("OR = %d\n", z); // 0110 | 1100 = 1110
```

- NOT (~)
	- Inverte os bits
```c
z = ~x; 

printf("NOT = %d\n", z); // ~0110 = 1001
```

- XOR (^)
	- Gera 0 se ambos bits forem 1
```c
z = x ^ y; 

printf("XOR = %d\n", z); // 0110 ^ 1100 = 1010
```

### Operadores de deslocamento (_shifting_)

- Recebem este nome porque **deslocam os bits** para a direita ou para a esquerda
- Espaços “vazios” são preenchidos com zeros
- São particularmente úteis quando combinados com operadores lógicos
#### _Shift_ para a esquerda

![](https://mflash.github.io/progswb2/aulas/bits/Rotate_left_logically.png)

- Em C/Python: o operador **<<**
- Argumentos: valor a ser deslocado e quantidade de bits para deslocar para a esquerda (o valor original fica inalterado)
    
- Exemplo: considere _x_ armazenando 23 (0x17):
```c
unsigned char x = 0x17;   // 23 em decimal
unsigned char y = x << 1; // left shift por 1 bit
// agora y armazenará 46 (0x2E)
```

- Deslocando vários bits de cada vez:
```c
y = x << 2; // y armazenará 92  (0x5C)
y = x << 3; // y armazenará 184 (0xB8)
```

#### _Shift_ para a direita

![](https://mflash.github.io/progswb2/aulas/bits/Rotate_right_logically.png)

- Em C/Python: o operador **>>**
- Argumentos: valor a ser deslocado e quantidade de bits para deslocar para a direita (o valor original fica inalterado)
    
- Exemplo: considere _x_ armazenando 23 (0x17):
```c
unsigned char x = 0x17;   // 23 em decimal
unsigned char y = x >> 1; // shift right por 1 bit
// agora y armazenará 11 (0x0B)
```

- Como antes, pode-se deslocar vários bits de cada vez:
```c
y = x >> 2; // y armazenará 5 (0x5)
y = x >> 3; // y armazenará 2 (0x2) 
```

# 3- Campos de bit

### Campos de bit

- Denomina-se **campo de bit** ou palavra parcial (_bit field_, _partial word_) quando extraímos apenas um grupo de bits de uma palavra
    
- Supondo que desejamos armazenar uma cor através dos seus componentes RGB (_red_, _green_, _blue_), onde cada componente armazena um valor de 0 a 1023 (1024 valores diferentes)
    - A solução mais simples é criar uma _struct_:
        
        ```c
        typedef struct {
          int red;
          int green;
          int blue;
        } RGB;
        ```
        
    - Qual é o problema?
    - 3 variáveis _int_ * sizeof(int) = 3 * 4 = 12 bytes
	- Mas isso é apenas UM ponto - e se tiveremos uma matriz de… 1024 x 768 pontos?
	    - 1024 x 768 x 12 = 9437184 bytes ~ **9 Mb**
		- Dependendo da aplicação e do hardware, pode ser demais!
		
- Pensando na quantidade de bits necessária…
    
    - 1024 = 210, então precisamos pelo menos 10 bits por componente de cor
    - 3 componentes (R, G, B) x 10 bits = 30 bits
        - Red: bits 0 a 9
        - Green: bits 10 a 19
        - Blue: bits 20 a 29
        
    - Tudo caberia em um único _int_ (e ainda teríamos 2 bits sem uso!)
    
- C oferece um recurso chamado **campos de bit**
    
    ```c
    typedef struct {
      int red : 10;
      int green : 10;
      int blue: 10;
    } RGBbit;
    ```
    
- Com isso, é possível agora alterar ou acessar diretamente apenas os bits necessários:
    
    ```c
    RGBbit cor;
    cor.red = 511;
    ```

- Solução é simples e eficiente, porém nem sempre pode ser utilizada
    
- Não se sabe como o compilador irá armazenar os 3 campos na memória
    - Não sabemos a **ordem de armazenamento**
    - Não sabemos o **espaço total ocupado** pela struct
    
- Exemplo: aumentando o tamanho dos campos para 12 bits, quanto espaço ocupa a _struct_?
    ```c
    typedef struct {
     int red : 12;
     int green : 12;
     int blue: 12;
    } RGBbit;
    RGBbit cor;
    cor.red = 1000;
    printf("%d\n", sizeof(cor));
    ```
### Possível solução: manipular os campos de bits usando operadores *bitwise*
------------
#### Armazenando um valor em um campo de bits

- Exemplo: supondo que desejamos armazenar o valor 500 no campo de bits da componente verde
    - 500 é 0x1F4 (hex)
        ```c
        unsigned int colour = ...; // algum valor inicial
        unsigned int newgreen = 0x1F4; // novo valor para armazenar no verde
        ```

- Primeiro, precisamos **limpar** os 10 bits “verdes”
#### Zerando um campo de bits

- Um **AND bitwise** pode ser usado
- Precisamos de uma **máscara**, onde os bits desejados devem ser zeros
    - 00111111111100000000001111111111
    
- Primeiro criamos uma máscara com 10 bits setados:
    - 00000000000000000000001111111111
    
- Agora deslocamos para a esquerda por 10 bits:
    - 00000000000011111111110000000000
        
        ```c
        unsigned int mask = 0x3FF << 10;
        ```
    
- Finalmente, precisamos **inverter** a máscara, pois os bits do meio precisam ser ressetados
    - 00111111111100000000001111111111
    
- Para isso, usamos o operador NOT _bitwise_:
    ```c
    unsigned int mask = ~mask;
    ```

- Agora precisamos apenas deslocar o valor desejado à posição correta
    
- Isto significa que devemos deslocar _newgreen_ à esquerda em 10 bits:
    - 00111111111100000000000111110100
        
        ```c
        newgreen = newgreen << 10;
        ```
        
    - 00000000000001111101000000000000
	
- E finalmente, para combinar com o valor atual precisamos:
    
    - Zerar os bits “verdes” com a máscara:
        ```c
        colour = colour & mask;
        ```
        
    - Modificar os bits “verdes” com o _newgreen_ deslocado:
        ```c
        colour = colour | newgreen;
        ```
        
- Obs: se você souber **exatamente** o que está fazendo, é possível fazer tudo de uma vez só!
    ```c
    colour = colour & ~(0x3FF << 10) | (newgreen << 10);
    ```
