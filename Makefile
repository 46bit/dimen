CC=clang
CFLAGS=-O3 -Wall -Wextra -lgd -lpng -lz -ljpeg -lfreetype -lm

all:
	mkdir -p bin
	$(CC) $(CFLAGS) burning_ship.c -o bin/burning_ship
	$(CC) $(CFLAGS) chelonian.c -o bin/chelonian
	$(CC) $(CFLAGS) dragon_curve.c -o bin/dragon_curve
	$(CC) $(CFLAGS) gosper_curve.c -o bin/gosper_curve
	$(CC) $(CFLAGS) mandelbrot.c -o bin/mandelbrot
	$(CC) $(CFLAGS) barnsley_fern.c -o bin/barnsley_fern

clean:
	rm -rf bin
