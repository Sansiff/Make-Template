SRCS=$(shell find tex/)

build/main.pdf: $(SRCS) Makefile scl.yaml clean update
	mkdir -p src/
	mkdir -p build/
	python2 gen.py > build/code.tex
	cp tex/* build/
	cd build && xelatex main.tex
	cd build && xelatex main.tex


.PHONY: clean check
check:
	true # code valid check

clean:
	rm -rf src/
	rm -rf build/

update:
	mkdir -p src/
	cd src/ && rm * -rf
	#git submodule init && git submodule update
	git submodule init && git submodule update && git submodule update --remote
	cp Code-Library src/ -rf
	cd src/Code-Library/ && rm -rf .idea/ cmake-build-debug/ .git/ && rm -f .gitignore README.md
	cd src/ && mv Code-Library/* ./ && rm -rf Code-Library
