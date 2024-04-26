# JSPI experiments

This repo explores building C programs using specific features to WASM using Emscripten, Asyncify, and JSPI.

Explorations related to JSPI support for WordPress Playground:

https://github.com/WordPress/wordpress-playground/issues/134

Explore specific directories and read the code to learn more. Each directory has a Makefile and a few build targets. Most examples can be build and ran as below.

## For Node.js

Remember to install Node.js v22 as JSPI is only supported there as of April 26th, 2024

```shell
make build_node
make run_node
```

## For Web

Try in Chrome with #enable-experimental-webassembly-jspi flag turned on chrome://flags

```shell
make build_web
make run_web
```
