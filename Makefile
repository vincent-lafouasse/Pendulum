.PHONY: all
all: build

.PHONY: build
build:
	cmake -B build -G Ninja
	cmake --build build --target Pendulum

.PHONY: build
run: build
	./build/Pendulum

.PHONY: test
test:
	cmake -B build -G Ninja
	cmake --build build
	GTEST_COLOR=1 ctest --test-dir build -V

.PHONY: format
format:
	clang-format -i $(shell find src -name '*.cpp' -or -name '*.hpp' -or -name '*.h')
	clang-format -i $(shell find test -name '*.cpp' -or -name '*.hpp' -or -name '*.h')


.PHONY: b r t fmt
b: build
r: run
t: test
fmt: format
