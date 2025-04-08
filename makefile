# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executables
EXECUTABLES = $(BUILD_DIR)/brute_force $(BUILD_DIR)/get_random_points

# Default target
all: $(EXECUTABLES)

# Rule to build each executable
$(BUILD_DIR)/brute_force: $(BUILD_DIR)/brute_force.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/get_random_points: $(BUILD_DIR)/get_random_points.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLES)

.PHONY: all clean
