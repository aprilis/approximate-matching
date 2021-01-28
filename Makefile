CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow

SRC = $(wildcard lib/*.cpp)
HD = $(wildcard lib/*.h)

STRING_TEST_SRC = $(SRC) string_test.cpp
MAIN_SRC = $(SRC) main.cpp
MAIN_OLD_SRC = $(SRC) main_old.cpp

main: $(MAIN_SRC) $(HD)
	g++ $(CXXFLAGS) -O2 $(MAIN_SRC) -o main

main-debug: $(MAIN_SRC) $(HD)
	g++ $(CXXFLAGS) $(MAIN_SRC) -g -fsanitize=address -fsanitize=undefined -o main-debug

main-old: $(MAIN_OLD_SRC) $(HD) lib/match_old.h
	g++ $(CXXFLAGS) -O2 $(MAIN_OLD_SRC) -o main-old

string-test: $(STRING_TEST_SRC) $(HD)
	g++ $(CXXFLAGS) -O2 $(STRING_TEST_SRC) -o string-test

string-test-debug: $(STRING_TEST_SRC) $(HD)
	g++ $(CXXFLAGS) $(STRING_TEST_SRC) -g -fsanitize=address -fsanitize=undefined -o string-test-debug

TESTS = tests/cyclic tests/cyclic_binomial tests/random_binary tests/repeat_3_big_k tests/repeat_3_mid_k tests/repeat_3_small_k tests/repeat_3_big_sigma

tests: $(TESTS)

run_tests: main naive tests test-output.sh
	for gen in $(TESTS); do \
		./test-output.sh $$gen 200 10;  \
		./test-output.sh $$gen 100 1000; \
	done

all: main main-debug main-old string-test string-test-debug naive tests

clean:
	rm main main-debug main-old string-test string-test-debug naive tests/*[^.cpp]