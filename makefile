# GROVOLUTION COMMUNICATION MAKEFILE
# AUTHOR            Dave Martinez
# DATE CREATED      May 29, 2015
# LAST MOD.         Aug. 18, 2015

# Compiler
CXX = g++-4.9

# Flags
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
CXXFLAGS += -lm

# All objects
OBJS = objs/main.o objs/rs232.o objs/relay.o objs/comms.o objs/bank.o

# All sources
SRCS = RS-232/rs232.c main.cpp sources/relay.cpp sources/comms.cpp sources/bank.cpp

#All headers
HEADERS = RS-232/rs232.h headers/relay.h headers/comms.h headers/bank.h


# Make Flags
# Everything
default: $(SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o gv

# Everything and clean
allandclean: default clean

# Main interface
objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c

objs/rs232.o: RS-232/rs232.c
	$(CXX) $(CXXFLAGS) RS-232/rs232.c -c

objs/relay.o: sources/relay.cpp headers/relay.h
	$(CXX) $(CXXFLAGS) sources/relay.cpp -c

objs/comms.o: sources/comms.cpp headers/comms.h
	$(CXX) $(CXXFLAGS) sources/comms.cpp -c

objs/bank.o: sources/bank.cpp headers/bank.h
	$(CXX) $(CXXFLAGS) sources/bank.cpp -c

#tests
relay-test: relay.o comms.o rs232.o
	$(CXX) $(CXXFLAGS) comms.o rs232.o relay.o tests/relay-test-1.cpp -o relay-test

bank-test: comms.o bank.o rs232.o relay.o sources/bank.cpp headers/bankcpp.h tests/bank-test-1.cpp
	$(CXX) $(CXXFLAGS) bank.o comms.o rs232.o relay.o tests/bank-test-1.cpp -o bank-test

regex-test: tests/regex-test.cpp
	$(CXX) $(CXXFLAGS) tests/regex-test.cpp -o regex-test


#utility

clean:
	rm -rf *.o
