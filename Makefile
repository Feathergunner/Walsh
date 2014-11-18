CC=g++
CFLAGS=-std=c++0x
OUT=jonasundangosinddoof

default:
	$(CC) $(CFLAGS) main.cpp -o $(OUT)

clean:
	rm -rf *.o $(OUT)