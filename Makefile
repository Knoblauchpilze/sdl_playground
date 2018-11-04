debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf build

cleanSandbox:
	rm -rf sandbox


copy:
	mkdir -p sandbox/
	rsync -avH data sandbox/
	mv sandbox/data/*.sh sandbox/

sandbox: release copy

distDebug: debug copy

r: sandbox
	cd sandbox && ./run.sh local

d: distDebug
	cd sandbox && ./debug.sh local

