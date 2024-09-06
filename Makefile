CC = g++
CFLAGS = -g -Wall

# Target to build the final executable
all: proxy

# Link object files to create the final executable
proxy: proxy_parse.o main.o utils/connection.o utils/error_msgs.o utils/thread.o utils/cache_element.o
	$(CC) $(CFLAGS) -o proxy proxy_parse.o main.o utils/connection.o utils/error_msgs.o utils/thread.o utils/cache_element.o -lpthread

# Compile Libraries/proxy_parse.c into proxy_parse.o
proxy_parse.o: Libraries/proxy_parse.c Libraries/proxy_parse.h
	$(CC) $(CFLAGS) -c Libraries/proxy_parse.c -o proxy_parse.o

# Compile main.c into main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compile utils/connection.c into utils/connection.o
utils/connection.o: utils/connection.c utils/connection.h
	$(CC) $(CFLAGS) -c utils/connection.c -o utils/connection.o

# Compile utils/error_msgs.c into utils/error_msgs.o
utils/error_msgs.o: utils/error_msgs.c utils/error_msgs.h
	$(CC) $(CFLAGS) -c utils/error_msgs.c -o utils/error_msgs.o

# Compile utils/thread.c into utils/thread.o
utils/thread.o: utils/thread.c utils/thread.h
	$(CC) $(CFLAGS) -c utils/thread.c -o utils/thread.o

# Compile Structures/cache_element.c into utils/cache_element.o
utils/cache_element.o: Structures/cache_element.c Structures/cache_element.h
	$(CC) $(CFLAGS) -c Structures/cache_element.c -o utils/cache_element.o

# Clean up build files
clean:
	rm -f proxy *.o utils/*.o

# Create a tarball of the source files
tar:
	tar -cvzf ass1.tgz main.c README Makefile Libraries/*.c Libraries/*.h utils/*.c utils/*.h Structures/*.c Structures/*.h

