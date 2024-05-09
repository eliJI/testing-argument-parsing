main: main.c
	gcc -O0 -g  main.c -o out -I/usr/include/x86_64-linux-gnu -L/usr/lib/x86_64-linux-gnu -lunwind
	gcc -O0 -g  main.c -S -I/usr/include/x86_64-linux-gnu -L/usr/lib/x86_64-linux-gnu -lunwind
