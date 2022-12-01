all: questions

questions: qtree.o main.o file.o
	g++ -o $@ $^

%.o: %.cpp qtree.h
	g++ -c -Wall -o $@ $<

.PHONY: clean
clean:
	rm -f questions *.o 
	
