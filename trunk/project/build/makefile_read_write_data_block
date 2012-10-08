../bin/test_read_write: ../test/test_read_write_data_block.c ../bin/write_data_block.o
	gcc -g  ../bin/write_data_block.o ../test/test_read_write_data_block.c -o ../bin/test_read_write

../bin/write_data_block.o: ../src/write_data_block.c ../incude/main.h
	gcc -o ../bin/write_data_block.o  -c ../src/write_data_block.c
