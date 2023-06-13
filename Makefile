CC = gcc
CFLAGS = -std=c99 -s -O2 -Iinc -Wall -Werror -pedantic

INCDIR = inc
SRCDIR = src
BINDIR = bin
OBJDIR = $(BINDIR)/obj
LIBDIR = lib

INCS = $(wildcard $(INCDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
LIB  = $(BINDIR)/libacutils.a

all: makedir $(LIB)

makedir:
	$(shell mkdir -p $(OBJDIR))

$(LIB): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf bin