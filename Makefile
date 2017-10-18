CCFLAGS=--std=c99 -g -pg
all:
	gcc $(CCFLAGS) main.c -o resow && ./resow
	gprof -p resow gmon.out > flatprofile
	gprof -p -l resow gmon.out > flatprofile_linebyline
	gprof -q resow gmon.out > callgraph
	gprof -l -A -x resow gmon.out > annotate_listing
clean:
	rm resow gmon.out flatprofile_linebyline outputFile flatprofile callgraph annotate_listing
