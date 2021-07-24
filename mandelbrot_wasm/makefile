all: main.wasm main.js main.html

main.wasm main.js main.html: main.c
	em++ .\main.c -s WASM=1 -s FORCE_FILESYSTEM=1 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -O3 -o main.html

clean:
	rm .\main.wasm .\main.js .\main.html