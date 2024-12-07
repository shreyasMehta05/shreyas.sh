# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Output executable
TARGET = a.out

# Directories
SRC_DIR = .
DISPLAY_DIR = display
INTERFACE_DIR = interface
COMMAND_DIR = command
HOP_DIR = hop
REVEAL_DIR = reveal
LOG_DIR = log
PROCLORE_DIR = proclore
SEEK_DIR = seek
REDIRECTION_DIR = redirection
PROCESS_DIR = process
PING_DIR = ping
ALIAS_DIR = alias
NEONATE_DIR = neonate
IMAN_DIR = iMan
SIG_DIR = command
# Source files
SRCS = $(SRC_DIR)/main.c \
       $(DISPLAY_DIR)/display.c \
       $(DISPLAY_DIR)/systemDisplay.c \
       $(INTERFACE_DIR)/interface.c \
       $(COMMAND_DIR)/command.c \
       $(HOP_DIR)/hop.c \
       $(REVEAL_DIR)/reveal.c \
       $(LOG_DIR)/log.c \
       $(PROCLORE_DIR)/proclore.c \
       $(SEEK_DIR)/seek.c \
       $(REDIRECTION_DIR)/redirection.c \
       $(PROCESS_DIR)/process.c \
       $(PING_DIR)/ping.c \
       $(ALIAS_DIR)/alias.c \
       $(NEONATE_DIR)/neonate.c \
       $(IMAN_DIR)/iMan.c \
       $(SIG_DIR)/signals.c \
       $(SIG_DIR)/globals.c \
       $(ALIAS_DIR)/functions.c
# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build (remove object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not real files)
.PHONY: all clean
