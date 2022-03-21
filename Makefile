CXX=g++
INCDIR=.
LDIR=.
LIBS=-lpthread #-lm
CXXFLAGS=-std=c++11 -I$(INCDIR) -L$(LDIR) $(LIBS)

DEPS = classSatellite.hpp  classTask.hpp  ./include/json.hpp  taskManager.hpp  utilities.hpp 

OBJ = classSatellite.o  classTask.o  taskManager.o  utilities.o 

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

taskManager: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

test:
	./taskManager input/tasks.json input/satellites.json output/tasks.json 

clean:
	rm *.o 
