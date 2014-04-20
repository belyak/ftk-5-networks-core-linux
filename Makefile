CC = g++

OUT_FILE = lgs

all:	main.o statistics.o persistent_statistics.o
	$(CC) -o $(OUT_FILE) $^

clean:	
	rm *.h.gch
	rm *.o

main.o:	main.cpp
	$(CC) -o main.o -c main.cpp
	
statistics.o:	statistics.cpp
	$(CC) -o statistics.o -c statistics.cpp
	
persistent_statistics.o: persistent_statistics.cpp
	$(CC) -o persistent_statistics.o -c persistent_statistics.cpp
