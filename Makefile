
SRCS := \
	main.o \
	listing23.o \
	listing24.o \
	nanobench.o \
	random.o \
	raw_virtual.o \
	ShapeCollection/ShapeCollection.o \
	CachedShapeCollection/CachedShapeCollection.o \
	Switch/listing25.o \
	SwitchPtr/SwitchPtr.o \
	Union/raw_union.o \
	UnionTable/listing27.o \
	UniqueVector/UniqueVector.o \
	VariantCollection/VariantCollection.o \
	RawVectorShapes/VectorShapes.o \
	MultiCollection/MultiCollection.o \
	SortedCollection/SortedCollection.o \
	HeterogeneousCollection/HeterogeneousCollection.o \
	HeterogeneousCollection/HetRunner.o \
	PolyCollection/PolyCollectionRunner.o

test : $(SRCS)
	g++ -g -O3 $^ -o "$@" -ltbb

FLAGS := -march=native -DSFMT_MEXP=19937 -g -O3

%.o : %.cpp
	g++ $(FLAGS) -c $< -o $@ -std=c++20

%.o : %.c
	gcc $(FLAGS) -O3 -c $< -o $@

clean :
	rm -f test *.o */*.o

.PHONY : clean
