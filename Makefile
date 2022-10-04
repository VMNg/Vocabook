MAIN = voca_book_main
FUNCTIONS = voca_book
LLFUNCTIONS = list
COMPILER = g++
COMPILERFLAGS = -c -s
DEBUG = -DDEBUG

all: $(MAIN)

$(MAIN): $(FUNCTIONS).o $(LLFUNCTIONS).o $(MAIN).o
	$(COMPILER) $(FUNCTIONS).o $(LLFUNCTIONS).o $(MAIN).o -o cpp_voca_book

$(MAIN).o: $(MAIN).cpp
	$(COMPILER) $(COMPILERFLAGS) $(MAIN).cpp

$(FUNCTIONS).o: $(FUNCTIONS).cpp $(FUNCTIONS).h
	$(COMPILER) $(COMPILERFLAGS) $(FUNCTIONS).cpp

$(LLFUNCTIONS).o: $(LLFUNCTIONS).cpp $(LLFUNCTIONS).h record.h
	$(COMPILER) $(COMPILERFLAGS) $(LLFUNCTIONS).cpp

clean:
	rm -f *.o cpp_voca_book*