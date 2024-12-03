.PHONY: setup build
setup:
	@mkdir -p build
	cmake -S . -B build

build:
	cmake --build build

test: build
	./build/tests/TestRunner


