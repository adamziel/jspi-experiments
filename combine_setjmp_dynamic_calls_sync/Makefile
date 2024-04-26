
run_node:
	node --experimental-wasm-jspi output.node.js

run_web:
	open http://localhost:9125/output.web.html
	python3 -m http.server 9125


build_all: build_node build_web

build_node: ENV = node
build_node: TYPE = js
build_node: build

build_web: ENV = web
build_web: TYPE = html
build_web: build
build:
	emcc -O0 -g2 \
		-sENVIRONMENT=$(ENV) \
		-sSIDE_MODULE=1 \
		-sEXPORTED_FUNCTIONS='["_add"]' \
		-o library \
		library.c

	emcc -O0 -g2 \
		-sENVIRONMENT=$(ENV) \
		-sMAIN_MODULE=2 \
		-sEXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
		-sEXPORTED_FUNCTIONS='["_main"]' \
		-o output.$(ENV).$(TYPE) \
		library main.c