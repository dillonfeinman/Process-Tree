CFLAGS = -Wall
P = prog2tree
O = simplefork
N = extra

all: $(P).o $(P)

tree: $(P)
	$(P): $(P).o
		gcc $(CFLAGS) $(P).o -o $(P)
	$(P).o: $(P).c $(N).c
		gcc $(CFLAGS) -c $(N).c $(P).c -o $(P).o
fork: $(O)
	$(O): $(O).o
		gcc $(CFLAGS) $(O).o -o $(O)
	$(O).o: $(O).c $(N).c
		gcc $(CFLAGS) -c $(N).c $(O).c -o $(O).o
extra: $(N)
	$(N): $(N).o
		gcc $(CFLAGS) $(N).o -o $(N)
	$(N).o: $(N).c $(N).c
		gcc $(CFLAGS) -c $(N).c $(N).c -o $(N).o
clean:
	rm -rf *.o $(P) $(O) *.txt
run: all
	./$(P)
checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)
