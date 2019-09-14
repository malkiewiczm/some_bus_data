TARGETS := remove_blank.elf

.PHONY: all clean
MAKEFLAGS += Rr

all: $(TARGETS)

%.elf: %.cpp
	g++ -std=gnu++11 -Wall -Wextra -Wpedantic -Wshadow -Ofast -march=native $< -o $@

clean:
	rm -f *.elf
