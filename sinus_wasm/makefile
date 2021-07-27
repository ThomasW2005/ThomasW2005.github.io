all: main.js main.wasm

main.js main.wasm: main.c
	emcc -g .\main.c -o main.js -s USE_SDL=2 -O3

clean:
	rm .\main.wasm .\main.js