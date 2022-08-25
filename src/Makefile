IDIR=../include
CC=gcc
CFLAGS=-I.
ODIR=../object

_DEPS = kalman.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = kalman-main.o kalman.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
# $(info OBJ = $(OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kalman: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

	# rm -f kalman ../results/* core $(INCDIR)/*~
clean:
	rm -f kalman $(ODIR)/*.o ../results/* core $(INCDIR)/*~