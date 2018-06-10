
INCLUDES=$$(pkg-config --cflags-only-I benchmark)
LIBS=$$(pkg-config --libs benchmark)

bench: bench.o half.o
	g++ bench.o half.o $(LIBS) -lrt -o bench

bench.o: bench.cpp openexr/*.h
	g++ -std=c++11 -O2 -c $(INCLUDES) bench.cpp

half.o: openexr/half.cpp openexr/*.h
	g++ -std=c++11 -O2 -c openexr/half.cpp -o half.o

clean:
	rm *.o bench
