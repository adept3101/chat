all: main

main:
	cc src/main.c src/msg.c src/sercli.c -pthread -o build/main
