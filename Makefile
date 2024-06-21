
SRCS := \
	main.o \
	listing23.o \
	listing24.o \
	nanobench.o \
	random.o \
	raw_virtual.o \
	mt/SFMT.o \
	Switch/listing25.o \
	Union/raw_union.o \
	UnionTable/listing27.o

test : $(SRCS)
	g++ -g -O3 $^ -o "$@"

%.o : %.cpp
	g++ -g -O3 -c $< -o $@

clean :
	rm -f test *.o

.PHONY : clean
