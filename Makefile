CCFLAGS=--std=c99 -g -pg
all:
	gcc $(CCFLAGS) main.c -o resow
	gcc --std=c99 createdataset.c -o createdataset
clean:
	rm resow gmon.out outputFile flatprofile createdataset dataset
