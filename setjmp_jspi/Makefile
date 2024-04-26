
run_node:
	node --experimental-wasm-jspi output.node.js

run_web:
	open http://localhost:9125/output.web.html
	python3 -m http.server 9125



ENV = node
TYPE = js

FLAGS = 

# This fails:
# make build_emscripten_exceptions && make run_node
build_emscripten_exceptions: FLAGS += -sSUPPORT_LONGJMP=emscripten -fexceptions 
build_emscripten_exceptions: build

# This succeeds:
# make build_wasm_exceptions && make run_node
build_wasm_exceptions: FLAGS += -sSUPPORT_LONGJMP=wasm -fwasm-exceptions 
build_wasm_exceptions: build

# This fails:
# make build && make run_node
build:
	emcc -O0 -g2 \
		-sASYNCIFY=2\
		$(FLAGS) \
		-sENVIRONMENT=$(ENV) \
		-sEXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
		-sEXPORTED_FUNCTIONS='["_main"]' \
		-o output.$(ENV).$(TYPE) \
		main.c
	python patch_output.py output.$(ENV).$(TYPE)


