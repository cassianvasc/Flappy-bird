CC = gcc
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -Wall -O2 -Isrc

SRC_MAIN = $(wildcard src/*.c *.c)
EXEC_MAIN = game

$(EXEC_MAIN): $(SRC_MAIN)
	$(CC) $(SRC_MAIN) -o $(EXEC_MAIN) $(CFLAGS) $(LDFLAGS)

run: $(EXEC_MAIN)
	./$(EXEC_MAIN)

clean:
	rm -f $(EXEC_MAIN)

.PHONY: run clean
#----------------------------------------------------------------------------------------------------
#                                  INSTRUÇÕES DE COMPILAÇÃO
# 1. Atualize com o comando: sudo apt update
# 2. Instale as ferramentas basicas com o comando: sudo apt install -y build-essential git cmake pkg-config make
# 3. Instale as dependencias para a Raylib com o comando sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libxxf86vm-dev libasound2-dev
# 4. Baixe o codigo fonte da Raylib: git clone https://github.com/raysan5/raylib.git
# 5. Compile a raylib dentro da pasta: cd raylib/src
#                         depois rode: make PLATFORM=PLATFORM_DESKTOP
# 6. Instale a Raylib no sistema: sudo make install
# 7. Volte para a pasta do jogo "flappy-bird" (pode usar o comando cd ../..)
# 8. Rode o jogo com o comando: make clean && make run