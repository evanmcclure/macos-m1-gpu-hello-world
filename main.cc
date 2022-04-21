#include <iostream>
#include <string>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

int main(int argc, char *argv[]) {
  MTL::Device *device = MTL::CreateSystemDefaultDevice();

  std::cout << "Running on " << device->name()->utf8String() << std::endl;

  MTL::Library *default_library = device->newDefaultLibrary();

  if (default_library == nullptr) {
    std::cerr << "Failed to find the app's default Metal library."
      << " Did you forget to compile it? See"
      << " https://developer.apple.com/documentation/metal/mtldevice/1433380-newdefaultlibrary"
      << std::endl;
    ::exit(1);
  }
}

