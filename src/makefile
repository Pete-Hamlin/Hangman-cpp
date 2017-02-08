CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=

SRC=main.cpp game.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=game

RM=rm -f

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGET) $(OBJ)
