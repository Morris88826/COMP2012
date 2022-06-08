CPPFLAGS = -std=c++11


SRC_DIR    := src
HEADER_DIR := include
BIN_DIR    := bin
OBJ_DIR 	:= $(BIN_DIR)/obj

EXECUTABLE := $(BIN_DIR)/main

OBJECTS = $(addprefix $(OBJ_DIR)/,main.o admin.o number.o SHA256.o signatures.o user.o)
HEADER_FILES = $(addprefix $(HEADER_DIR)/,signatures.h number.h SHA256.h user.h admin.h)


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	g++ -o $@ $(CPPFLAGS) $(OBJECTS) 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp   $(HEADER_FILES)
	g++ $(CPPFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean: 
	del $(OBJ_DIR)/*.o $(EXECUTABLE)