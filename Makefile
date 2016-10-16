# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
llisttest: llisttest.cpp lliststring.cpp lliststring.h 
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

stackstring: stackstring.cpp lliststring.cpp stackstring.h lliststring.h
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

stringparser: stringparser.cpp lliststring.cpp stackstring.cpp lliststring.h stackstring.h
	$(CC) $(CPPFLAGS) stringparser.cpp stackstring.cpp lliststring.cpp -o stringparser

clean:
	rm llisttest
	rm stackstring
	rm stringparser
