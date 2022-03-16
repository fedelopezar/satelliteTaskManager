CC=g++
INCDIR=.
LDIR=.
LIBS=-lpthread #-lm
CFLAGS=-I$(INCDIR) -L$(LDIR) $(LIBS)

DEPS = classSatellite.hpp  classTask.hpp  ./include/json.hpp  taskManager.hpp  utilities.hpp 

OBJ = classSatellite.o  classTask.o  taskManager.o  utilities.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

taskManager: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test:
	./taskManager input/tasks.json input/satellites.json 

clean:
	rm *.o 
