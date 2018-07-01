
INCLUDES=$$(pkg-config --cflags-only-I benchmark)
LIBS=$$(pkg-config --libs benchmark)
OPENEXR_INCLUDES=$$(pkg-config --cflags-only-I IlmBase)
OPENEXR_LIBS=$$(pkg-config --libs IlmBase)

bench: bench.o half_intrin.o
	g++ bench.o half_intrin.o $(OPENEXR_LIBS) $(LIBS) -lrt -o bench

bench.o: bench.cpp openexr/*.h
	g++ -std=c++11 -O2 -c $(OPENEXR_INCLUDES) $(INCLUDES) bench.cpp

half.o: openexr/half.cpp openexr/*.h
	g++ -std=c++11 -O2 -c openexr/half.cpp -o half.o

half_intrin.o: half_intrin.cpp openexr/*.h
	g++ -std=c++11 -mf16c -O2 -c half_intrin.cpp -o half_intrin.o

clean:
	rm *.o bench
