CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TEST := test

LIBRARIES	:=

ifeq ($(OS),Linux)
EXECUTABLE	:= main.exe
TEST_EXECUTABLE := test.exe
else
EXECUTABLE	:= main
TEST_EXECUTABLE := test
endif

all: $(BIN)/$(EXECUTABLE)

teste: 
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(TEST_EXECUTABLE) $(LIBRARIES) $(TEST)/test.cpp $(SRC)/Team9.cpp
	./$(BIN)/$(TEST_EXECUTABLE)


clean:
	$(RM) $(BIN)/$(EXECUTABLE)
	$(RM) $(BIN)/$(TEST_EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)


$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)