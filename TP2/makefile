C=gcc
CFLAGS=-c  -I ./inc
LDFLAGS=-lcrypto
vpath %.h ./inc
vpath %.c ./src
SOURCES=main.c  memory_utils.c bitmap.c bit_wise.c mod251_operations.c share_secret_utils.c share_secret.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=./bin/tp2

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	@echo "Clearing" $(OUTPUT_DIR) "directory..."
	@rm -f *.o
	@rm -f ./bin/*
	@echo "Done."

