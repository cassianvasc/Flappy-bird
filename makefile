CC = gcc
LDFLAGS = -lopengl32 -lgdi32 -lwinmm -lraylib -Isrc
CFLAGS  = -Wall -O2 

# Compila todos os arquivos .c da src/ e subpastas game, render e utils
SRC_MAIN = $(wildcard src/*.c *.c)

EXEC_MAIN = game.exe

# Compila o jogo principal com Raylib
$(EXEC_MAIN):
	$(CC) $(SRC_MAIN) -o $(EXEC_MAIN) $(CFLAGS) $(LDFLAGS)


# Alvos de conveniência
run: $(EXEC_MAIN)
	./$(EXEC_MAIN)

clean:
	del /Q $(EXEC_MAIN) $(EXEC_TEST) 2>nul || true

# mingw32-make clean; mingw32-make run 
#comando para rodar o codigo ^