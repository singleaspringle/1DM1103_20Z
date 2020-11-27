DEPS = main.o mat.o wczyt.o

zad6:$(DEPS)
	cc $^ -o $@ -Wall --pedantic -lm

%.o:%.c
	cc -c $^ -o $@
#najpierw to zostanie wykonane bo potrzebna jest zamiana kazdego pliku.c na plik.o zeby uzyc DEPS w kompilacji

clean:
	rm zad6
	rm *.o
