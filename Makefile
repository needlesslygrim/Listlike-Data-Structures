# Define the compiler flags
CFLAGS = -Wall -Wextra -pedantic

# Define the optimization level
OPTIMISE = -O2

# Define the source directory
VPATH = src

# Define the build directory
BUILD_DIR = build

# Define the source files and object files
SRC = main.c list.c node.c
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

# Define the default target to build
all: $(BUILD_DIR)/list

# Define the target to build the executable
$(BUILD_DIR)/list: $(OBJ)
	$(CC) $(CFLAGS) $(OPTIMISE) $^ -o $@

# Define the build rule for object files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OPTIMISE) -c $< -o $@

# Define the build rule for the build directory
$(BUILD_DIR):
	mkdir -p $@

# Define the target to clean the build directory
clean:
	rm -rf $(BUILD_DIR)/*.o list

run: $(BUILD_DIR)/list
	./$(BUILD_DIR)/list