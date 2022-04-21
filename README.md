# macos-m1-gpu-hello-world
A "Hello World" program for the M1 GPU on MacOS using Metal, written in C++

## Environment

This projects builds and runs on my personal MacBook Air M1, 2020, running macOS Ventura 13.1. It requires XCode and XCode Command Line Tools. The required Metal libraries will be downloaded when the program gets built.

**System information:**

```console
% uname -a
Darwin Evans-MacBook-Air-2.local 22.2.0 Darwin Kernel Version 22.2.0: Fri Nov 11 02:04:44 PST 2022; root:xnu-8792.61.2~4/RELEASE_ARM64_T8103 arm64
```

**Install XCode and XCode command line tools:**

https://github.com/gfx-rs/gfx/issues/2309#issuecomment-506130902

**Compiler information:**

```console
% which c++
/usr/bin/c++
%% c++ --version
Apple clang version 14.0.0 (clang-1400.0.29.202)
Target: arm64-apple-darwin22.2.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

```console
% xcode-select --version
xcode-select version 2396.
% xcode-select --print-path
/Applications/Xcode.app/Contents/Developer
```

```console
% xcrun --version
xcrun version 61
```

## Getting started

```console
make clean all
./a.out
```

## References

* https://developer.apple.com/metal/cpp/
* https://developer.apple.com/documentation/metal/gpu_devices_and_work_submission
* https://larsgeb.github.io/2022/04/20/m1-gpu.html
