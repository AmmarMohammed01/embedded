SRC = src/server.c src/helper.c
CPPFLAGS = -Iinclude

all: main

main: $(SRC)
	gcc $(SRC) $(CPPFLAGS) -o out

debug: $(SRC)
	gcc $(SRC) $(CPPFLAGS) -o out -g

clean:
	rm out

clean_debug:
	rm out
	rm -rf out.dSYM
