all: loadParameters.out  time.out pid_shm.out pid_mmap.out rwFile.out proto.out json.out

proto.out: ./proto/test.cpp ./proto/msg.pb.cc
	g++  ./proto/msg.pb.cc ./proto/test.cpp -o ./proto/$@  `pkg-config --cflags --libs protobuf`

json.out: json.cpp
	g++ -o $@ $< -ljson

rwFile.out: rwFile.cpp
	g++ $< -o $@

loadParameters.out: loadParameters.cpp
	g++ $< -o $@

time.out: time.cpp
	g++ $< -o $@ 

pid_shm.out: pid_shm.cpp
	g++ $< -o $@

pid_mmap.out: pid_mmap.cpp
	g++ $< -o $@ -lrt

clean:
	rm *.out
	rm ./proto/*.out


