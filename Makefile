# Matheus Barcellos de Castro Cunha   		NUSP: 11208238
# Maria Eduarda Kawakami Moreira   			NUSP: 11218751

FLAGS = -pthread -Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
OBJS = Estrutura.o RedeSocial.o
EXEC = RedeSocial

.PHONY: clean

all: RedeSocial

RedeSocial: $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~ RedeSocial

run: 
	./$(EXEC)