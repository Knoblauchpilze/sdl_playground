debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf build

cleanSandbox:
	rm -rf sandbox

copyRelease:
	cp build/Release/bin/* sandbox/bin

copyDebug:
	cp build/Debug/bin/* sandbox/bin

copy:
	mkdir -p sandbox/
	mkdir -p sandbox/bin
	rsync -avH data sandbox/
	mv sandbox/data/*.sh sandbox/

sandbox: release copy copyRelease

sandboxDebug: debug copy copyDebug

r: sandbox
	cd sandbox && ./run.sh local

d: sandboxDebug
	cd sandbox && ./debug.sh local

v: sandboxDebug
	cd sandbox && ./valgrind.sh local

