../bin/vfs_group08: ../bin/narray_tree.o ../bin/bst.o ../bin/vfs.o ../bin/write_data_block.o ../bin/file_system.o ../bin/hash.o ../bin/vfs_errorcodes.o ../bin/vfsdriver.o
	gcc -g ../bin/narray_tree.o ../bin/bst.o ../bin/vfs.o ../bin/write_data_block.o ../bin/file_system.o ../bin/hash.o ../bin/vfs_errorcodes.o ../bin/vfsdriver.o -o ../bin/vfs_group08
../bin/vfsdriver.o: ../src/vfsdriver.c ../include/main.h
	gcc -g -I ../include/ -c ../src/vfsdriver.c -o ../bin/vfsdriver.o
../bin/vfs_errorcodes.o: ../src/vfs_errorcodes.c ../include/main.h
	gcc -g -I ../include/ -c ../src/vfs_errorcodes.c -o ../bin/vfs_errorcodes.o
../bin/hash.o: ../src/hash.c ../include/main.h
	gcc -g -I ../include/ -c ../src/hash.c -o ../bin/hash.o
../bin/file_system.o: ../src/file_system.c ../include/main.h
	gcc -g -I ../include/ -c ../src/file_system.c -o ../bin/file_system.o
../bin/write_data_block.o: ../src/write_data_block.c ../include/main.h
	gcc -g -I ../include/ -c ../src/write_data_block.c -o ../bin/write_data_block.o
../bin/vfs.o: ../src/vfs.c ../include/main.h
	gcc -g -o ../bin/vfs.o -I ../include/  -c ../src/vfs.c
../bin/bst.o: ../src/bst.c ../include/main.h
	gcc -g -I ../include/ -c ../src/bst.c -o ../bin/bst.o	
../bin/narray_tree.o: ../src/narray_tree.c ../include/main.h
	gcc -g -o ../bin/narray_tree.o -I ../include/  -c ../src/narray_tree.c
