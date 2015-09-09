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
OBJS = obj/main.o obj/rs232.o obj/relay.o obj/comms.o obj/bank.o obj/error.o

# All sources
SRCS = RS-232/rs232.c main.cpp sources/relay.cpp sources/comms.cpp sources/bank.cpp sources/error.cpp

#All headers
HEADERS = RS-232/rs232.h headers/relay.h headers/comms.h headers/bank.h headers/error.h


# Make Flags
# Everything
default: $(SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o gv

# Everything and clean
allandclean: default clean

# Main interface
obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o obj/main.o

obj/rs232.o: RS-232/rs232.c
	$(CXX) $(CXXFLAGS) -c RS-232/rs232.c -o obj/rs232.o

obj/relay.o: sources/relay.cpp headers/relay.h
	$(CXX) $(CXXFLAGS) -c sources/relay.cpp -o obj/relay.o

obj/comms.o: sources/comms.cpp headers/comms.h
	$(CXX) $(CXXFLAGS) -c sources/comms.cpp -o obj/comms.o

obj/bank.o: sources/bank.cpp headers/bank.h
	$(CXX) $(CXXFLAGS) -c sources/bank.cpp -o obj/bank.o

obj/error.o: sources/error.cpp headers/error.h
	$(CXX) $(CXXFLAGS) -c sources/error.cpp -o obj/error.o

#tests
relay-test: relay.o comms.o rs232.o
	$(CXX) $(CXXFLAGS) comms.o rs232.o relay.o tests/relay-test-1.cpp -o relay-test

bank-test: comms.o bank.o rs232.o relay.o sources/bank.cpp headers/bankcpp.h tests/bank-test-1.cpp
	$(CXX) $(CXXFLAGS) bank.o comms.o rs232.o relay.o tests/bank-test-1.cpp -o bank-test

regex-test: tests/regex-test.cpp
	$(CXX) $(CXXFLAGS) tests/regex-test.cpp -o regex-test

#refactor.error testing
error: obj/error.o obj/relay.o obj/comms.o obj/bank.o obj/rs232.o
	$(CXX) $(CXXFLAGS) obj/error.o obj/comms.o obj/bank.o obj/rs232.o obj/relay.o tests/error-test.cpp -o error-test


#utility

clean:
	rm -rf *.o
