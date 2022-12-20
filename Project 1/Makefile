all: naive aware oblivious optimized

naive:
	gcc a1.c -O0 -D_N -o naive

aware:
	gcc a1.c -O0 -D_A -o aware

oblivious:
	gcc a1.c -O0 -D_O -o oblivious

optimized:
	gcc a1.c -O0 -D_OPTIMIZED -o optimized

clean:
	rm naive
	rm aware
	rm oblivious
	rm optimized