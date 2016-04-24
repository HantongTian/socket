#make file for test

all : CHECK_DIR
CHECK_DIR:ECHO
	mkdir -p bin
	make -C client
	make -C server

	@echo all compile completed

ECHO :
	@echo let\'s go

.PHONY : clean
clean:
	-rm -rf bin/*
