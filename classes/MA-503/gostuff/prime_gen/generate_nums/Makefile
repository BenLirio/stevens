run : main.o big.o
	clang -o run main.o big.o
main.o : main.c big.h
	clang -c main.c

big_test : big.o big_test.o
	clang -o big_test big.o big_test.o
big_test.o : big_test.c big.h
	clang -c big_test.c
big.o : big.c big.h
	clang -c big.c

clean :
	rm main.o big.o run big_test
