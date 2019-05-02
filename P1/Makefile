#   Makefile P1
CPPFLAGS = -DP1 -I../Tests-auto -I.
VPATH = ../Tests-auto:.
CXX = g++
STD = c++11
CXXFLAGS = -std=${STD} -Wall -pedantic -g 
OBJECTS = fecha.o cadena.o 

all: test-P1-auto test-P1-consola 

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

test-P1-consola: $(OBJECTS) test-P1-consola.o
	$(CXX)  $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp  test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P1-consola.o: test-P1-consola.cpp fecha.cpp cadena.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@

cadena.o: cadena.cpp cadena.hpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@

fecha.o: fecha.cpp fecha.hpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@

cadena_check fecha_check: cadena_check.cpp fecha_check.cpp
	make -f Make_check.mk

####################

checks: fecha_check cadena_check
	./cadena_check cadena.cpp -- -std=c++11
	./fecha_check fecha.cpp -- -std=c++11

####################

#   Regla de limpieza:
clean:
	rm -f $(OBJECTS) test-P1-auto test-P1-consola \
                         test-P1-auto.o test-P1-consola.o \
                         fecha_check.o cadena_check.o \
                         fecha_check cadena_check
