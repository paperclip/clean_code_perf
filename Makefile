
sources := $(wildcard *.cpp) $(wildcard */*.cpp)
headers := $(wildcard *.h) $(wildcard */*.h)
objects := $(patsubst %.cpp,%.o,$(sources))

test : $(objects)
	g++ -g -O3 $^ -o "$@" -ltbb

FLAGS := -march=native -DSFMT_MEXP=19937 -g -O3

%.o : %.cpp
	g++ $(FLAGS) -c $< -o $@ -std=c++20

main.o : main.cpp $(headers)

%.o : %.c
	gcc $(FLAGS) -O3 -c $< -o $@

clean :
	rm -f test *.o */*.o

.PHONY : clean e
