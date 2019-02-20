all: a.out 
	./a.out 

a.out: *.cpp *.hpp
	g++-8 -std=c++17 *.cpp -fopenmp -O3 \
		-I"/usr/local/Cellar/boost/1.68.0_1/include/"

compile: a.out 

dylib: libcheckers.a

libcheckers.a: *.cpp *.hpp
	g++ -std=c++17 *.cpp -O3 \
		-I"/usr/local/Cellar/boost/1.68.0_1/include/" \
		-shared -o libcheckers.a