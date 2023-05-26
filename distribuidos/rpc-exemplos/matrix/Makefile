CC = gcc
RPCGEN = rpcgen

CLIENT_SRCS = client.c matrix_clnt.c matrix_xdr.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT_EXEC = client

SERVER_SRCS = server.c matrix_svc.c matrix_xdr.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER_EXEC = server

CFLAGS = -Wall
OBJFLAGS = -lnsl
LDFLAGS = -lrpcsvc

all: rpcgen_compile compile_client compile_server

rpcgen_compile:
	$(RPCGEN) -C matrix.x

compile_client: $(CLIENT_OBJS)
	$(CC) -o $(CLIENT_EXEC) $(CLIENT_OBJS) $(OBJFLAGS)

compile_server: $(SERVER_OBJS)
	$(CC) -o $(SERVER_EXEC) $(SERVER_OBJS) $(OBJFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_EXEC) $(SERVER_EXEC) matrix_xdr.c matrix.h matrix_svc.c matrix_clnt.c
