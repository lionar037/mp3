# Nombre del ejecutable
TARGET = mp3_player

# Directorios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
ASSETS_INCLUDE_DIR = $(INCLUDE_DIR)/assets

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(ASSETS_INCLUDE_DIR)
LDFLAGS = -lmpg123 -lao -lpthread

# Reglas
all: $(BIN_DIR)/$(TARGET)

# Regla para crear el ejecutable
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# PHONY evita conflictos con archivos llamados 'clean' o 'all'
.PHONY: all clean
