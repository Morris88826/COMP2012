CPPFLAGS = -std=c++11
MEMLEAKFLAGS = -fsanitize=address,leak,undefined # check if has memory leak

SRC_DIR    := src
HEADER_DIR := include
BIN_DIR    := bin
OBJ_DIR 	:= $(BIN_DIR)/obj

EXECUTABLE := $(BIN_DIR)/main

OBJECTS = $(addprefix $(OBJ_DIR)/,main.o admin.o number.o SHA256.o signatures.o user.o)
HEADER_FILES = $(addprefix $(HEADER_DIR)/,signatures.h number.h SHA256.h user.h admin.h)

all: directories $(EXECUTABLE)

directories:
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJECTS)
	g++ -o $@ $(CPPFLAGS) $(MEMLEAKFLAGS) $(OBJECTS) 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp   $(HEADER_FILES)
	g++ $(CPPFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean: 
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)