all: encode preprocess

encode: encode.cpp
	g++ -o encode encode.cpp

preprocess: preprocess.cpp
	g++ -o preprocess preprocess.cpp

