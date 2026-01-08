# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -lcurl

# Target executable
TARGET = weather_system

# Source files
SRC = weather_system.c

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	@echo "Compiling Weather Forecasting System..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(TARGET) .weather_cache.txt
	@echo "Clean complete!"

# Install (optional - copy to /usr/local/bin)
install: $(TARGET)
	@echo "Installing to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation complete! Run from anywhere with: $(TARGET)"

# Uninstall
uninstall:
	@echo "Uninstalling..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstall complete!"

# Help
help:
	@echo "Weather Forecasting System - Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build the weather system"
	@echo "  make clean    - Remove build artifacts and cache"
	@echo "  make install  - Install to /usr/local/bin (requires sudo)"
	@echo "  make uninstall- Remove from /usr/local/bin (requires sudo)"
	@echo "  make help     - Show this help message"

.PHONY: all clean install uninstall help
