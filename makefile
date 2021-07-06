main: src/main.cpp src/LogDatum.h src/LogDatum.cpp
	c++ -std=c++11 src/main.cpp src/LogDatum.cpp -o main
LD_test: test/test.cpp src/LogDatum.h src/LogDatum.cpp
	c++ -std=c++11 test/test.cpp src/LogDatum.cpp -o LD_test -lgtest -lgtest_main
