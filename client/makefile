#make file for test

SUBDIRS = ../include tcpClient obj ../bin

OBJECTS = tcpClient.o my_log.o my_socket.o

BIN_DIR = ../bin

BIN = client

OBJ_DIR = obj

CC=gcc
CFLAGS= -I.:../include 

export SUBDIRS OBJECTS BIN CC CFLAGS BIN_DIR OBJ_DIR

all : CHECK_DIR
CHECK_DIR:ECHO
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	
	make -C tcpClient
	make -C $(OBJ_DIR)

	@echo tcpClient compile completed

ECHO :
	#@echo $(SUBDIRS)
	@echo begin compile tcpClient

.PHONY : clean
clean:
	-rm -rf $(OBJ_DIR)/*.o
	-rm -rf $(BIN_DIR)/$(BIN)
