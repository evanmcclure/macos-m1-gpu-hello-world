#include <iostream>
#include <string>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <sysexits.h>

#include <iostream>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

int main(int argc, char *argv[]) {
  // Allow different modes: GPU, Single Core, Multiple Cores

  // M1 GPU Mode

  MTL::Device *device = MTL::CreateSystemDefaultDevice();

  std::cout << "Running on " << device->name()->utf8String() << std::endl;

  MTL::Library *default_library = device->newDefaultLibrary();

  if (default_library == nullptr) {
    std::cerr << "Failed to create the default Metal library." << std::endl
      << " Did you forget to compile it? See"
      << " https://developer.apple.com/documentation/metal/mtldevice/1433380-newdefaultlibrary" << std::endl
      << " Try running the following commands first:" << std::endl
      << "     xcrun -sdk macosx metal -c add.metal -o templib.air" << std::endl
      << "     xcrun -sdk macosx metallib templib.air -o default.metallib" << std::endl;
    ::exit(EX_CONFIG);
  }

  MTL::Function *add_arrays = default_library->newFunction(NS::String::string("add_arrays", NS::ASCIIStringEncoding));

  if (add_arrays == nullptr) {
    std::cerr << "Failed to create add_arrays function." << std::endl;
    ::exit(EX_CONFIG);
  }

  NS::Error *error = nullptr;
  MTL::ComputePipelineState *add_arrays_pipeline_state = device->newComputePipelineState(add_arrays, &error);

  if (add_arrays_pipeline_state == nullptr) {
    std::cerr << "Failed to create compute pipeline state for add_arrays: error=" << error << std::endl;
    ::exit(EX_CONFIG);
  }

  MTL::CommandQueue *command_queue = device->newCommandQueue();

  if (command_queue == nullptr) {
    std::cerr << "Failed to create a CommandQueue." << std::endl;
    ::exit(EX_UNAVAILABLE);
  }

  const unsigned int array_size = 10;

  MTL::Buffer *a = device->newBuffer(array_size * sizeof(float), MTL::ResourceStorageModeShared);
  float *data = (float *)a->contents();
  for (unsigned long i = 0; i < array_size; i++) {
    data[i] = float(i);
  }

  MTL::Buffer *b = device->newBuffer(array_size * sizeof(float), MTL::ResourceStorageModeShared);
  data = (float *)b->contents();
  for (unsigned long i = 0; i < array_size; i++) {
    data[i] = float(i);
  }

  MTL::Buffer *result = device->newBuffer(array_size * sizeof(float), MTL::ResourceStorageModeShared);
  data = (float *)result->contents();
  for (unsigned long i = 0; i < array_size; i++) {
    data[i] = float(0);
  }

  MTL::CommandBuffer *command_buffer = command_queue->commandBuffer();

  MTL::ComputeCommandEncoder *encoder = command_buffer->computeCommandEncoder();
  encoder->setComputePipelineState(add_arrays_pipeline_state);
  encoder->setBuffer(a, 0, 0);
  encoder->setBuffer(b, 0, 1);
  encoder->setBuffer(result, 0, 2);

  MTL::Size grid_size = MTL::Size::Make(array_size, 1, 1);
  NS::UInteger max_total_threads_per_group = add_arrays_pipeline_state->maxTotalThreadsPerThreadgroup();
  if (max_total_threads_per_group > array_size) {
    max_total_threads_per_group = array_size;
  }
  MTL::Size thread_group_size = MTL::Size::Make(max_total_threads_per_group, 1, 1);

  encoder->dispatchThreads(grid_size, thread_group_size);
  encoder->endEncoding();

  command_buffer->commit();
  command_buffer->waitUntilCompleted();

  std::cout << "[";
  data = (float *) result->contents();
  for (unsigned long i = 0; i < array_size; i++) {
    if (i == 0) {
      std::cout << " " << data[i];
    } else {
      std::cout << ", " << data[i];
    }
  }
  std::cout << "]" << std::endl;
}
