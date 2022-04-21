CPP = clang++
CPPFLAGS = -Wall -Werror -std=c++17 -I./metal-cpp -framework Metal -framework Foundation -framework QuartzCore -framework MetalKit

.PHONY: all
all: metal-cpp
	$(CPP) $(CPPFLAGS) main.cc

metal-cpp_macOS12_iOS15.zip:
	curl -o metal-cpp_macOS12_iOS15.zip https://developer.apple.com/metal/cpp/files/metal-cpp_macOS12_iOS15.zip

metal-cpp: metal-cpp_macOS12_iOS15.zip
	unzip metal-cpp_macOS12_iOS15.zip

.PHONY: clean
clean:
	$(RM) -rf a.out metal-cpp metal-cpp_macOS12_iOS15.zip __MACOSX
