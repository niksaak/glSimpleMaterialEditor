NAME := glsme

BIN_DIR := bin
PROJ_DIR := proj.win32
PRECOMPILED_DIR := $(PROJ_DIR)/Precompiled
SOURCE_DIR := src

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
SOURCES += $(wildcard $(PRECOMPILED_DIR)/*.cpp)

OBJECTS := $(SOURCES:.cpp=.o)

EXE := $(BIN_DIR)/$(NAME)

CXX := clang++
CXXFLAGS := -c -Wall -O2 -std=c++11 -I$(PROJ_DIR) -I$(PRECOMPILED_DIR) -I$(SOURCE_DIR)
LDFLAGS := -Wall -lglfw -lGL

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $+ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

.PHONY: clean
clean:
	@$(RM) $(EXE) $(OBJECTS)
