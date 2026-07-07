# Linux build for the SDL2 game

CXX = g++
CXXFLAGS = -Wall -I./inc
LDLIBS = -lSDL2main -lSDL2 -lSDL2_image
EXEC = game.out

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
SRC_FILES = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: folders $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean folders

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/$(EXEC)

folders:
	mkdir -p $(SRC_DIR) $(OBJ_DIR) $(BUILD_DIR)
