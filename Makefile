CC = g++

OUT_FILE = lgs
OBJ_DIR = temp/

vpath %.o $(OBJ_DIR)

all:	main.o statistics.o persistent_statistics.o
	$(CC) -o $(OUT_FILE) $^

clean:	
	rm $(OBJ_DIR)*.o

main.o:	main.cpp
	$(CC) -o $(OBJ_DIR)main.o -c main.cpp
	
statistics.o:	statistics.cpp
	$(CC) -o $(OBJ_DIR)statistics.o -c statistics.cpp
	
persistent_statistics.o: persistent_statistics.cpp
	$(CC) -o $(OBJ_DIR)persistent_statistics.o -c persistent_statistics.cpp
