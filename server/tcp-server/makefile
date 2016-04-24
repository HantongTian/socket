#make file for test

Targets =  ../$(OBJ_DIR)/tcp_server.o \
		   ../$(OBJ_DIR)/my_log.o \
		   ../$(OBJ_DIR)/my_socket.o

all : $(Targets)
.PHONY : all

../$(OBJ_DIR)/tcp_server.o : tcp_server.c
	$(CC) -c -o $@ $< $(CFLAGS)

../$(OBJ_DIR)/my_log.o : ../../include/my_log.c
	$(CC) -c -o $@ $< $(CFLAGS)

../$(OBJ_DIR)/my_socket.o : ../../include/my_socket.c
	$(CC) -c $(CFLAGS) -o $@ $<


.PHONY : clean
clean:
	-rm -f *.o .*.swp
