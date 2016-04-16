#make file for test

ALL : ../$(OBJ_DIR)/my_socket.o ../$(OBJ_DIR)/my_log.o

.PHONY : ALL
../$(OBJ_DIR)/my_socket.o : my_socket.c
	$(CC) -c -o $@ $< $(CFLAGS)

../$(OBJ_DIR)/my_log.o : my_log.c
	$(CC) -c -o $@ $< $(CFLAGS)


.PHONY : clean
clean:
	-rm -f  *.o .*.swp
