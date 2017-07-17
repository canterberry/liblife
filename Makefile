all: lib/liblife.so

.PHONY: clean all

lib:
	mkdir -p lib

lib/liblife.so: lib src/**/*.c include/**/*.h
	cc -shared -o lib/liblife.so -Iinclude src/**/*.c

clean:
	rm -vfR lib
