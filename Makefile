CC = g++

OUT_FILE = lgs

all:	main.o statistics.o persistent_statistics.o IOAdapter.o FDIOAdapter.o lgs_constants.o
	$(CC) -o $(OUT_FILE) $^

clean:	
	rm *.h.gch
	rm *.o

lgs_constants.o: lgs_constants.h lgs_constants.cpp
	$(CC) -o lgs_constants.o -c lgs_constants.cpp

main.o:	main.cpp
	$(CC) -o main.o -c main.cpp
	
statistics.o:	statistics.cpp statistics.h
	$(CC) -o statistics.o -c statistics.cpp
	
persistent_statistics.o: persistent_statistics.cpp
	$(CC) -o persistent_statistics.o -c persistent_statistics.cpp
	
IOAdapter.o: IOAdapter.cpp IOAdapter.h
	$(CC) -o IOAdapter.o -c IOAdapter.cpp

FDIOAdapter.o: FDIOAdapter.cpp FDIOAdapter.h
	$(CC) -o FDIOAdapter.o -c FDIOAdapter.cpp