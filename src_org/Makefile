# Verwende ?= damit Yocto seine eigenen Compiler-Definitionen setzen kann
CXX ?= g++
# Füge deine Flags hinzu, ohne die von Yocto zu löschen
CXXFLAGS += -O2 -Wall -Wextra -std=c++17
LDFLAGS += -pthread

TARGET = ventilator-simulator
SOURCES = ventilator.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

# Den 'install' Teil im Makefile können wir ignorieren, 
# da wir das direkt in der ventilator.bb (do_install) machen.
