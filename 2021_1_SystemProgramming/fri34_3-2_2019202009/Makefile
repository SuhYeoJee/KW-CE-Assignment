OBJS = *.c *.h
EXEC = proxy_cache
all: $(OBJS)
	gcc -pthread -g -o $(EXEC) $^ -lcrypto
