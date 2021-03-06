CC = clang++
CFLAGS = -std=c++17 -O3 -Wall -Wextra
LDFLAGS = -std=c++17 -O3 -Wall -Wextra
NAME = ecs_prototype
BIN_FILE_PATH = ./bin/

CPP = main.cpp e.cpp
OBJ = $(CPP:%.cpp=%.o)
OBJ_DEST = $(CPP:%.cpp=$(BIN_FILE_PATH)%.o)

all: $(OBJ)
	$(CC) -o $(BIN_FILE_PATH)$(NAME) $(OBJ_DEST) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(BIN_FILE_PATH)$@

test: all
	$(BIN_FILE_PATH)$(NAME) && $(BIN_FILE_PATH)$(NAME) > test.log

clean:
	rm $(OBJ_DEST) $(BIN_FILE_PATH)$(NAME)
