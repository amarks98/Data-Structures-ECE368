array15: pa1
	./pa1 -a ./examples/15.b ./output
	diff ./output ./examples/15sa.b

array1K: pa1
	./pa1 -a ./examples/1K.b ./output
	diff ./output ./examples/1Ksa.b

testarray: pa1
	./pa1 -a ./examples/15.b ./output
	diff ./output ./examples/15sa.b
	./pa1 -a ./examples/1K.b ./output
	diff ./output ./examples/1Ksa.b
	./pa1 -a ./examples/10K.b ./output
	./pa1 -a ./examples/100K.b ./output
	./pa1 -a ./examples/1M.b ./output

arraymem: pa1
	valgrind ./pa1 -a ./examples/15.b ./output
	valgrind ./pa1 -a ./examples/1K.b ./output
	valgrind ./pa1 -a ./examples/10K.b ./output
	valgrind ./pa1 -a ./examples/100K.b ./output
	valgrind ./pa1 -a ./examples/1M.b ./output

list15: pa1
	./pa1 -l ./examples/15.b ./output
	diff ./output ./examples/15sa.b

list1K: pa1
	./pa1 -l ./examples/1K.b ./output
	diff ./output ./examples/1Ksa.b

testlist: pa1
	./pa1 -l ./examples/15.b ./output
	diff ./output ./examples/15sa.b
	./pa1 -l ./examples/1K.b ./output
	diff ./output ./examples/1Ksa.b
	./pa1 -l ./examples/10K.b ./output
	./pa1 -l ./examples/100K.b ./output
	./pa1 -l ./examples/1M.b ./output

listmem: pa1
	valgrind ./pa1 -l ./examples/15.b ./output
	valgrind ./pa1 -l ./examples/1K.b ./output
	valgrind ./pa1 -l ./examples/10K.b ./output
	valgrind ./pa1 -l ./examples/100K.b ./output
	valgrind ./pa1 -l ./examples/1M.b ./output
