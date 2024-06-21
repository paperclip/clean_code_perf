
SRCS := \
	main.o \
	listing23.o \
	listing24.o \
	nanobench.o \
	random.o \
	raw_virtual.o \
	mt/SFMT.o \
	Switch/listing25.o \
	SwitchPtr/SwitchPtr.o \
	Union/raw_union.o \
	UnionTable/listing27.o \
	UniqueVector/UniqueVector.o \
	RawVectorShapes/VectorShapes.o

test : $(SRCS)
	g++ -g -O3 $^ -o "$@"

%.o : %.cpp
	g++ -DSFMT_MEXP=19937 -g -O3 -c $< -o $@

clean :
	rm -f test *.o

.PHONY : clean
