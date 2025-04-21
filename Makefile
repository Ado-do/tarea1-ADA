## Variables
# Compiler
CXX = g++

# Default build type (release)
DEBUG ?= 0

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(SRC_DIR)
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -DDEBUG
else
	CXXFLAGS += -O2
endif

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) # All source files in src/

# Exclude points.cpp from programs (it's a library)
PROGRAM_SRCS = $(filter-out $(SRC_DIR)/points.cpp, $(SRCS))
LIB_SRCS = $(filter $(SRC_DIR)/points.cpp, $(SRCS))

# Object files
PROGRAM_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(PROGRAM_SRCS))
LIB_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SRCS))

# Programs name
PROGRAMS = $(basename $(notdir $(PROGRAM_SRCS))) # src/<name>.cpp -> <name>
EXECUTABLES = $(addprefix $(BUILD_DIR)/,$(PROGRAMS)) # <name> -> build/<name>


## Targets
# Default target
all: $(EXECUTABLES)

# Prevent make from deleting object files
.SECONDARY: $(PROGRAM_OBJS) $(LIB_OBJ)

# Rule to build executables (link with points.o)
$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(LIB_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up builded files
clean:
	rm -rf $(BUILD_DIR)/
	rm *.png *.txt *.csv

.PHONY: all clean
