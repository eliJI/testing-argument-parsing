main: main.c
	nvcc main.c -o out -I/usr/include/x86_64-linux-gnu -L/usr/lib/x86_64-linux-gnu -lunwind
