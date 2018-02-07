CPPFLAGS = -I. 
CFLAGS   = -Wall -Wextra -std=c99 
LDFLAGS  = -lm

BIN      = inshiNoHeya

.PHONY: all clean cleanall

all: $(BIN)

clean:
	@(rm -f *.o *~)

cleanall: clean
	@(rm -f *.grid $(BIN))
