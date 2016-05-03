CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=

SRCS=grosz.c 
OBJS=$(subst .c,.o,$(SRCS))

.PHONY: all

all: szilardkaland

szilardkaland: $(OBJS)
	echo $(OBJS)
	$(CXX) $(LDFLAGS) -o szilardkaland.out $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
