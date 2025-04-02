
compilador = g++

flags = -std=c++17 -Wall -Wextra -Werror

archivo_main = main.cpp
out = main

all: $(out)

$(out): $(archivo_main)
	$(compilador) $(flags) $(archivo_main) -o $(out)

clean:
	rm -f $(out)
