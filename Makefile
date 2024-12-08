CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRCS = fact.cpp basic_block.cpp graph.cpp
EXE = fact.out

all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRCS)

run_factorial_test: $(EXE)
	./$(EXE)

valgrind_check: $(EXE)
	valgrind --leak-check=full ./$(EXE)

clean:
	rm -f $(EXE)