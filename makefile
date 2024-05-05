all: integrate

integrate: integrate.cpp
	g++ -std=c++11 -pthread integrate.cpp -o integrate

clean:
	rm -f integrate