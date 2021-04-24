# Diagrama Lógico
![Comunicação entre os módulos](documents/images/jvm_projeto_logico.png)

# Contribuidores

- Artur Filgueiras Scheiba Zorron - 180013696  
  Nota média da avaliação pelo grupo: 10  
  Contribuição:
  * Read Methods
  * Print Methods
  * Math Instructions (de 0x60 a 0x84)

- Artur Hugo Cunha Pereira - 180030400  
  Nota média da avaliação pelo grupo: 10  
  Contribuição:
  * Estruturas da constant pool
  * Leitura e impressão da constant pool
  * Instruções de loads (opcodes de 0x15 a 0x35)
  * Instruções extended (opcodes de 0xc4 a 0xc9)
  * Instrução invokevirtual
  * Resolução de referências na constant pool
  * Impressão de mnemônicos no leitor-exbidor

- Brenno Pereira Cordeiro - 190127465  
  Nota média da avaliação pelo grupo: 10
  * Estruturas de atributos
  * Leitura e impressão de atributos
  * Estrutura de map
  * Instruções de stores (opcodes de 0x36 a 0x56)
  * Instruções de conversions (opcodes de 0x85 a 0x93)
  * Instruções getstatic, putstatic, getfield e putfield
  * Instruções invokespecial e invokeinterface
  * Inicialização de classe

- Felipe Oliveira Magno Neves - 180016296   
  Nota média da avaliação pelo grupo: 10  
  Contribuição:
  * Estrutura de Stack
  * Leitura e exibição de instruções no leitor e exibidor
  * Instruções de constants (opcodes de 0x00 a 0x14)
  * Instruções de stack (opcodes de 0x57 a 0x5f)
  * Algumas instruções de references (invokestatic e new até arraylength opcodes 0xb8, 0xbb, 0xbc, 0xbd, 0xbe)
  
- Guilherme Oliveira Loiola - 170050335  
  Nota média da avaliação pelo grupo: 10
  Contribuição:
  * Read Fields
  * Print Fields
  * Comparisons Instructions (de 0x94 a 0xa6)
  * Control Instructions (de 0xa7 a 0xb1)

- Contribuições coletivas:
  * Estrutura da method area
  * Código da execution engine

# Interpretador

1. [x] array simples

2. [x] arrays.length

3. [x] arrays multidimensionais

4. [x] arrays de referencia

5. [x] doubles

6. [x] floats

7. [x] longs

8. [x] inteiros  

9. [x] shorts

10. [-] strings

11. [x] desvios com cat 1 

12. [x] operacoes logicas com cat 1  

13. [x] operacoes de deslocamento com cat 1 

14. [x] operacoes aritmeticas de cat 2 

15. [x] operacoes de deslocamento de longs

16. [x] system.out.println (int, float, string e booleano)

17. [x] conversao de e para cat 2

18. [x] iteracao

19. [x] switches

20. [-] fields

21. [x] interfaces

22. [x] recursao

23. [x] metodos estaticos  

24. [x] metodos nao estaticos

25. [x] objetos 

26. [x] operacoes de retorno

27. [x] operacoes de manipulacao de pilha

28. [x] consistencia

29. [ ] exceptions

30. [x] invokes

31. [x] polimorfismo

32. [x] reescrita

33. [x] herança

#  Opcionais 
1. [ ] todas as demais instruções.
2. [ ] threads
3. [ ] debug
4. [ ] checagem dinâmica de tipos
5. [ ] coletor de lixo.

# Leitor e Exibitor

Leitor e exibidor de arquivos no formato `.class` do Java.

## Compilação

```
gcc -Wall -Wextra -g -std=c99 -Iinclude src/*.c src/handlers/*.c -o jvm
```

## Uso
Para o leitor-exibidor:
```
./jvm -l <Arquivo.class>
```
Para o imterpretador:
```
./jvm -i <Arquivo.class>
```
