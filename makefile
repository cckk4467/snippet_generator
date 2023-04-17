.PHONY: make run

script: ./script_src/main.cpp ./script_src/excep.cpp
	g++ ./script_src/main.cpp -std=c++20 -o script

make: script

run: script
	./script -root_path ./script_src