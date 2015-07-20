# GROVOLUTION COMMUNICATION MAKEFILE
# AUTHOR            Dave Martinez
# DATE CREATED      May 29, 2015
# LAST MOD.         May 29, 2015

# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
CXXFLAGS += -lm

# All objects
OBJS = main.o rs232.o relay.o comms.o bank.o fileops.o

# All sources
SRCS = RS-232/rs232.c main.c sources/relay.c sources/comms.c sources/bank.c sources/fileops.c

#All headers
HEADERS = RS-232/rs232.h headers/relay.h headers/comms.h headers/bank.h headers/fileops.h


# Make Flags
# Everything
default: $(SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o gv

# Everything and clean
allandclean: default clean

# Main interface
main.o: main.c
	$(CXX) $(CXXFLAGS) main.c -c

rs232.o: RS-232/rs232.c
	$(CXX) $(CXXFLAGS) RS-232/rs232.c -c

relay.o: sources/relay.c
	$(CXX) $(CXXFLAGS) sources/relay.c -c

comms.o: sources/comms.c
	$(CXX) $(CXXFLAGS) sources/comms.c -c

bank.o: sources/bank.c
	$(CXX) $(CXXFLAGS) sources/bank.c -c

fileops.o: sources/fileops.c
	$(CXX) $(CXXFLAGS) sources/fileops.c -c


#tests

relay-test-1: $(OBJS) tests/relay-test-1.c
	$(CXX) $(CXXFLAGS) rs232.o relay.o comms.o tests/relay-test-1.c -o relay-test-1

bank-test-1: $(OBJS) tests/bank-test-1.c
	$(CXX) $(CXXFLAGS) rs232.o relay.o comms.o bank.o tests/bank-test-1.c -o bank-test-1


#utility

clean:
	rm -rf *.o


#refactor
relaycpp.o: sources/relay.cpp
	$(CXX) $(CXXFLAGS) rs232.o comms.o sources/relay.cpp -c
