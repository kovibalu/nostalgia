CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=-lncurses

SRCS=amoba.c bifa.c menu.c MI.c sconiol.c sconiow.c
OBJS=$(subst .c,.o,$(SRCS))

.PHONY: all

all: amoba

amoba: $(OBJS)
	echo $(OBJS)
	$(CXX) $(LDFLAGS) -o amoba.out $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
