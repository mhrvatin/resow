make clean
make

./createdataset $1
./resow $1 $2
gprof -p resow gmon.out > flatprofile
