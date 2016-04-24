#make file for test

SUBDIRS = ../include tcp-server obj ../bin

OBJECTS = tcp_server.o my_log.o my_socket.o

BIN_DIR = ../bin

BIN = tcpServer

OBJ_DIR = obj

CC=gcc
CFLAGS= -I.:../include -lpthread

export SUBDIRS OBJECTS BIN CC CFLAGS BIN_DIR OBJ_DIR

all : CHECK_DIR
CHECK_DIR:ECHO
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	
	make -C tcp-server
	make -C $(OBJ_DIR)

	@echo tcpserver compile completed

ECHO :
	#@echo $(SUBDIRS)
	@echo begin compile tcpserver

.PHONY : clean
clean:
	-rm -rf $(OBJ_DIR)/*.o
	-rm -rf $(BIN_DIR)/$(BIN)
