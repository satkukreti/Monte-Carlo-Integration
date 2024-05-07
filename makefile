all: integrate

integrate: integrate.cpp
	g++ -Wall -Wextra -pedantic integrate.cpp -o integrate

clean:
	rm -f integrate