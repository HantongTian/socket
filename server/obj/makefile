#make file for test


../$(BIN_DIR)/$(BIN) : $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY : clean
clean:
	-rm -f *.o .*.swp
