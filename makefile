# GROVOLUTION COMMUNICATION MAKEFILE
# AUTHOR            Dave Martinez
# DATE CREATED      May 29, 2015
# LAST MOD.         May 29, 2015

# Compiler
CXX = g++-4.9

# Flags
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
CXXFLAGS += -lm

# All objects
OBJS = main.o rs232.o relay.o comms.o bank.o fileops.o

# All sources
SRCS = RS-232/rs232.c main.c sources/relay.cpp sources/comms.cpp sources/bank.cpp sources/fileops.c

#All headers
HEADERS = RS-232/rs232.h headers/relay.h headers/comms.h headers/bankcpp.h headers/fileops.h


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

relay.o: sources/relay.cpp headers/relay.h
	$(CXX) $(CXXFLAGS) sources/relay.cpp -c

comms.o: sources/comms.cpp headers/comms.h
	$(CXX) $(CXXFLAGS) sources/comms.cpp -c

bank.o: sources/bank.cpp headers/bankcpp.h
	$(CXX) $(CXXFLAGS) sources/bank.cpp -c

fileops.o: sources/fileops.c
	$(CXX) $(CXXFLAGS) sources/fileops.c -c


#tests
relay-test: relay.o comms.o rs232.o
	$(CXX) $(CXXFLAGS) comms.o rs232.o relay.o tests/relay-test-1.cpp -o relay-test

bank-test: bank.o sources/bank.cpp headers/bankcpp.h tests/bank-test-1.cpp
	$(CXX) $(CXXFLAGS) bank.o comms.o rs232.o relay.o tests/bank-test-1.cpp -o bank-test
	
regex-test: tests/regex-test.cpp
	$(CXX) $(CXXFLAGS) tests/regex-test.cpp -o regex-test
	

#utility

clean:
	rm -rf *.o
