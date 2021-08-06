CXXFLAGS := -g -Wall
LINK.o := $(CXX)

.PHONY: clean handin

Driver : Driver.o Josephus.o

handin : handin.tar

handin.tar : Josephus.cpp Driver.cpp
	tar cvf $@ $^

clean :
	-$(RM) -f $(wildcard *.o) Driver handin.tar
