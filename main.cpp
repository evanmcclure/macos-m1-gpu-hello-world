#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

int main(int argc, char *argv[]) {
    MTL::Device *device = MTL::CreateSystemDefaultDevice();

    MetalAdder *adder = new MetalAdder(device);

    adder->sendComputeCommand();
    adder->verifyResults();
}

