## Requirements

* g++
* cmake
* ninja
* libsdl2-dev
* libsdl2-image-dev

## Instructions (for Ubuntu / Debian)

### Build & Compile

```shell
# Inside projects root directory (where main CMakeLists.txt is located)
sudo apt update
sudo apt install g++ cmake libsdl2-dev libsdl2-image-dev

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build
cmake --build build --target arkanoid-like
```

### Run

```shell
./build/arkanoid-like
```
