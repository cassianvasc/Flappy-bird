# Flappy bird
Trabalho da cadeira de Programação Imperativa e Funcional do 2 período do curso de Ciências da computação da Cesar School

=======
# 🐦 Flappy Bird Clone

Clone do Flappy Bird desenvolvido em C com Raylib para a disciplina de Programação Imperativa e Funcional.

## 🎮 Controles

- **Espaço**: Voar
- **Enter**: Iniciar e voltar ao menu

## 🛠️ Estrutura do Projeto

O código está organizado da seguinte forma:

- `main.c` - Loop principal do jogo
- `bird.c/h` - Lógica do pássaro
- `pipe.c/h` - Lógica dos canos (obstáculos)
- `game.c/h` - Jogo propriamente dito
- `common.h/h` - Variáveis globais do codigo
- `menu.c/h` - Tela de menu inicial
- `Linked_list.c/h` - Lista encadeada de canos

## 📚 Conceitos Aplicados

- Structs para organização de dados
- Listas encadeadas para gerenciar os obstáculos
- Funções em C e funções da Raylib
- Ponteiros e alocação dinâmica
- Raylib para gráficos, colisões e dinâmica de jogo

# 🔧 Instalação e Compilação
Execute os seguintes comandos em sequência:

## 1. Atualizar o sistema
sudo apt update

## 2. Instalar ferramentas básicas de compilação
sudo apt install -y build-essential git cmake pkg-config make

## 3. Instalar dependências da Raylib
sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libxxf86vm-dev libasound2-dev

## 4. Baixar e compilar a Raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
cd ../..

## 5. Compilar e executar o jogo
make clean && make run

---

Desenvolvido por [Cassian Vasconcelos Ferrari] - [2025.2]

