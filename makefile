# Makefile for SYNAPSIS

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Object files
OBJECTS = welcome.o main.o profile.o menu.o formatting.o files.o chat.o

# Executable name
EXECUTABLE = SYNAPSIS

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Compile source files into object files
%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $<

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Installation target
install: $(EXECUTABLE)
	@echo "Installing SYNAPSIS..."
	@cp $(EXECUTABLE) /usr/local/bin/
	@echo "SYNAPSIS installed successfully. You can run it using 'SYNAPSIS'."

# Uninstall target
uninstall:
	@echo "Uninstalling SYNAPSIS..."
	@rm -f /usr/local/bin/$(EXECUTABLE)
	@echo "SYNAPSIS uninstalled successfully."

# Help target
help:
	@echo "Makefile Commands:"
	@echo "  make            Build the executable"
	@echo "  make clean      Remove object files and executable"
	@echo "  make install    Install SYNAPSIS to /usr/local/bin/"
	@echo "  make uninstall  Remove SYNAPSIS from /usr/local/bin/"
	@echo "  make help       Display this help message"

# Default target
all: $(EXECUTABLE)