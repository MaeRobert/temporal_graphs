EXEC = mini_executable
FICHIERS_C = $(wildcard *.c)
FICHIERS_H = $(wildcard *.h)	 
LINK = -lm

all: $(EXEC)
	./$(EXEC)
	
$(EXEC): $(FICHIERS_C) $(FICHIERS_H)
	$(CC) -g -o $(EXEC) $(FICHIERS_C) $(LINK)

clean:
	$(RM) $(EXEC)
