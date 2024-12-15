 
# Jogo de Golfe <br/>
## Introdução

Esse jogo de golfe foi desenvolvido como requisito para a disciplina Programação e Desenvolvimento de Software II.
 O projeto foi desenvolvido na linguagem C++, com o objetivo de aplicar os conteudos vistos ao longo de toda a disciplina durante o semestre. 
 <br/>
O jogo consiste em completar uma fase de golfe, ou seja, deve-se colocar a bola de golfe no buraco (só temos um de cada em cada fase). Além disso, a cada fase aumenta a quantidade de obstáculos. Todos os movimentos são feitos a partir do mouse (botão esquerdo), o movimento é feito pressionando o botão esquerdo e arrastando sobre a tela, quanto mais arrastar (distância percorrida do cursor) mais forte irá sair a bola. A direção da bola é a mesma que você percorre ao soltar o botão esquerdo do arraste, porém com direção oposta.  
 ## Ferramentas
 
No desenvolvimento do projeto foram utilizadas as seguintes ferramentas, biblioteca e linguagem:<br/>

- Linguagem: C++ <br/>
- Documentação: Doxygen <br/>
- Testes Unitários: Doctest <br/>
- Biblioteca: SDL <br/>

<br/>

## Requisitos

-Possuir um compilador para C++ <br/>
-Estar em um ambiente Linux <br/>
-Possuir a biblioteca SDL <br/>

### Como Rodar
- Instalação libs => `sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev cmake`
- Posteriormente dentro do projeto  => `cmake CMakeLists.txt &&  cmake --build . && ./golf `
- Para rodar o menu => ` cd menu  && cmake CMakeLists.txt &&  cmake --build . && ./menu `

## Documentação

É necessário ter na raiz do projeto um arquivo Doxyfile. Um arquivo padrão pode ser gerado pelo comando:
```
$ doxygen -g
```
Para gerar a documentação, utilizar:

```
$ doxygen Doxyfile

```
ou

```
$ make documentation

```
