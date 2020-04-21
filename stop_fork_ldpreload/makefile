inject:
	gcc test.c -o test
	gcc -Wall -fPIC -shared -o inject.so inject.c
	LD_PRELOAD=./inject.so ./test


mac:
	gcc -shared -fPIC -o inject.dylib inject.c
	gcc test.c -o test
	DYLD_INSERT_LIBRARIES=$PWD/inject.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./test

clean:
	rm -f test
	rm -f inject.dylib
	rm -f inject.so