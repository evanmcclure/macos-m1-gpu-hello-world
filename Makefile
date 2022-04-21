CPP = c++
CPPFLAGS = -Wall -Werror -std=c++17 -I$(METAL_CPP) -framework Metal -framework Foundation -framework MetalKit
METAL_CPP = ./metal-cpp
METAL_CPP_ZIP = metal-cpp_macOS13_iOS16.zip

.PHONY: all
all: a.out metallib

a.out: main.cc $(METAL_CPP)
	$(CPP) $(CPPFLAGS) main.cc

$(METAL_CPP_ZIP):
	curl -o $(METAL_CPP_ZIP) https://developer.apple.com/metal/cpp/files/$(METAL_CPP_ZIP)

$(METAL_CPP): $(METAL_CPP_ZIP)
	unzip $(METAL_CPP_ZIP)

.PHONY: metallib
metallib: default.metallib

default.metallib: templib.air
	xcrun -sdk macosx metallib templib.air -o default.metallib

templib.air:
	xcrun -sdk macosx metal -c add.metal -o templib.air

.PHONY: clean
clean:
	$(RM) -rf templib.air default.metallib a.out $(METAL_CPP) $(METAL_CPP_ZIP) __MACOSX
