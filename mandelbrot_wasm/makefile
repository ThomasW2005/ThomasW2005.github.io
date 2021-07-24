all: wasm exe

wasm main.wasm main.js main.html: main.cpp
	em++ .\main.cpp -s WASM=1 -s FORCE_FILESYSTEM=1 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -O3 -o main.html

exe main.exe: main.cpp
	g++ -g main.cpp -o main.exe -IC:/LIBS/SDL2-2.0.14/include -LC:/LIBS/SDL2-2.0.14/lib/x64 -lSDL2main -lSDL2

clean:
	rm .\main.wasm .\main.js .\main.html .\main.exe