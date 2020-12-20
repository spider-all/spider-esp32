all: debug

release debug:
	if [ ! -d src/$@ ]; then mkdir src/$@; fi
	cd src/$@ && cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
	-DCMAKE_BUILD_TYPE=$@ .. && cmake --build .
