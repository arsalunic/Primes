all: primes.o 
	gcc -pthread -o primes primes.c

first.o : primes.c
	gcc -c primes.c

clean:
	rm -f *.o primes
