all: loadParameters.out  time.out pid_shm.out pid_mmap.out rwFile.out

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



