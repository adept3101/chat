all: main

main:
	cc src/main.c src/msg.c src/sercli.c -pthread -o build/main
# server:
# 	cc src/server.c src/msg.c -pthread -o build/server
#
# client:
# 	cc src/client.c src/msg.c -pthread -o build/client
