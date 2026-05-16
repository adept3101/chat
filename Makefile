all: server client

server:
	cc src/server.c src/msg.c -o build/server

client:
	cc src/client.c src/msg.c -o build/client
