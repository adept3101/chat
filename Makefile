all: server client

server:
	cc src/server.c -o build/server

client:
	cc src/client.c -o build/client
