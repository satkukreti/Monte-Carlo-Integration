all: integrate

integrate: integrate.cpp
	g++ integrate.cpp -o integrate

clean:
	rm -f integrate