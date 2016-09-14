all: decode encode
	rm encode.o decode.o t1.*

decode: decode.o
	g++ -std=c++11 -o decode decode.o

encode:	encode.o
	g++ -std=c++11 -o encode encode.o

encode.o: encode.cpp
	g++ -std=c++11 -c encode.cpp

decode.o: decode.cpp
	g++ -std=c++11 -c decode.cpp

clean:
	rm encode.o encode decode.o decode t1.*
   
