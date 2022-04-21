.PHONY: all
all: metal-cpp
	clang++ -std=c++17 -I./metal-cpp -framework Metal -framework Foundation -framework MetalKit main.cpp

metal-cpp_macOS12_iOS15.zip:
	curl -o metal-cpp_macOS12_iOS15.zip https://developer.apple.com/metal/cpp/files/metal-cpp_macOS12_iOS15.zip

metal-cpp: metal-cpp_macOS12_iOS15.zip
	unzip metal-cpp_macOS12_iOS15.zip

.PHONY: clean
clean:
	$(RM) -rf a.out metal-cpp metal-cpp_macOS12_iOS15.zip __MACOSX
