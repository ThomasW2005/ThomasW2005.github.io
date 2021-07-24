all: wasm exe

wasm main.wasm main.js main.html: main.cpp
	em++ -g main.cpp -o main.html -O3 -s WASM=1 -s FORCE_FILESYSTEM=1 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 --shell-file shell_minimal.html -s "EXPORTED_RUNTIME_METHODS=['ccall']" -s NO_EXIT_RUNTIME=1

exe main.exe: main.cpp
	g++ -g main.cpp -o main.exe -IC:/LIBS/SDL2-2.0.14/include -LC:/LIBS/SDL2-2.0.14/lib/x64 -lSDL2main -lSDL2

clean:
	rm .\main.wasm .\main.js .\main.html .\main.exe