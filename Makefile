# Variables de compilación
CC = g++
CFLAGS = -std=c++14
LDFLAGS =
DEBUGFLAGS = -g

# Nombre del ejecutable
TARGET = automata
DEBUG_TARGET = automata_debug

# Directorios
SRCDIR = src
INCDIR = include
BINDIR = bin

# Archivos fuente
SRCS = $(wildcard $(SRCDIR)/*.cpp) main.cpp

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Incluir directorio de encabezados
INCFLAGS = -I$(INCDIR)

# Directorio para los ejecutables
ifeq ($(DEBUG),1)
    TARGET_DIR = $(BINDIR)/debug
else
    TARGET_DIR = $(BINDIR)
endif

# Reglas de compilación
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET_DIR)/$@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

# Regla para limpiar archivos objeto y ejecutable
clean:
	$(RM) $(TARGET_DIR)/$(TARGET) $(OBJS)

# Regla para compilar en modo debug
debug: clean
debug: CFLAGS += $(DEBUGFLAGS)
debug: DEBUG_TARGET = $(DEBUG_TARGET)
debug: all

$(DEBUG_TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET_DIR)/$@
