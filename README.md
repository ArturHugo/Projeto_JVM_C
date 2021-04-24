# Diagrama Lógico
![Comunicação entre os módulos](documents/images/jvm_projeto_logico.png)

# Contribuidores

- Artur Filgueiras Scheiba Zorron - 180013696
- Artur Hugo Cunha Pereira - 180030400
- Brenno Pereira Cordeiro - 190127465
- Felipe Oliveira Magno Neves - 180016396
- Guilherme Oliveira Loiola - 170050335

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

10. [x] strings

11. [x] desvios com cat 1 

12. [x] operacoes logicas com cat 1  

13. [x] operacoes de deslocamento com cat 1 

14. [x] operacoes aritmeticas de cat 2 

15. [x] operacoes de deslocamento de longs

16. [x] system.out.println (int, float, string e booleano)

17. [x] conversao de e para cat 2

18. [x] iteracao

19. [x] switches

20. [x] fields

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
gcc -Wall -Wextra -g -std=c99 -Iinclude src/*.c -o jvm
```

## Uso

```
./jvm <Arquivo.class>
```
