CC = gcc
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -Wall -O2 -Isrc

# Compila todos os arquivos .c da src/ e subpastas game, render e utils
SRC_MAIN = $(wildcard src/*.c *.c)
EXEC_MAIN = game

# Compila o jogo principal com Raylib
$(EXEC_MAIN): $(SRC_MAIN)
	$(CC) $(SRC_MAIN) -o $(EXEC_MAIN) $(CFLAGS) $(LDFLAGS)

# Alvos de conveniência
run: $(EXEC_MAIN)
	./$(EXEC_MAIN)

clean:
	rm -f $(EXEC_MAIN)

.PHONY: run clean

# make clean && make run