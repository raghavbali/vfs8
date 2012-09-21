../bin/test3:../test/test_vfs.c ../bin/narray_tree.o ../bin/vfs.o
	gcc -I ../include/ ../bin/narray_tree.o ../bin/vfs.o ../test/test_vfs.c  -o ../bin/test3
../bin/vfs.o: ../src/vfs.c ../include/main.h
	gcc -o ../bin/vfs.o -I ../include/  -c ../src/vfs.c
../bin/narray_tree.o: ../src/narray_tree.c ../include/main.h
	gcc -o ../bin/narray_tree.o -I ../include/  -c ../src/narray_tree.c




