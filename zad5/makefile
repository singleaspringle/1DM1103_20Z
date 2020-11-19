DEPS = main.o dziekanat.o studenci.o

zad5:$(DEPS)
	cc $^ -o $@ -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@
#najpierw to zostanie wykonane bo potrzebna jest zamiana kazdego pliku.c na plik.o zeby uzyc DEPS w kompilacji

clean:
	rm zad5
	rm *.o
