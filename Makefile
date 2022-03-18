CXX=g++
INCDIR=.
LDIR=.
LIBS=-lpthread #-lm
CFLAGS=-std=c++11 -I$(INCDIR) -L$(LDIR) $(LIBS)

DEPS = classSatellite.hpp  classTask.hpp  ./include/json.hpp  taskManager.hpp  utilities.hpp 

OBJ = classSatellite.o  classTask.o  taskManager.o  utilities.o 

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

taskManager: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

test:
	./taskManager input/tasks.json input/satellites.json output/tasks.json 

clean:
	rm *.o 
