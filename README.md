## Requirements

* `g++`
* `cmake`
* `ninja`
* `libsdl2-dev`
* `libsdl2-image-dev`
* [`cxxopts`](https://github.com/jarro2783/cxxopts)
* [`dragonslake-framework`](https://github.com/darkroom2/dragonslake-framework)

## Instructions (for Ubuntu / Debian)

### Build & Compile

#### Install libraries / dependencies

Download submodule
libraries ([`cxxopts`](https://github.com/jarro2783/cxxopts) [`dragonslake-framework`](https://github.com/darkroom2/dragonslake-framework)):

```shell
git submodule update --init
```

or just download the code from repositories and place it inside the [`libs/`](./libs) directory.

Install system libraries (`libsdl2-dev` `libsdl2-image-dev`) and build tools (`g++` `cmake` `ninja`):

```shell
sudo apt update && \
sudo apt install g++ cmake ninja-build libsdl2-dev libsdl2-image-dev
```

Prepare build configuration files and build the executable:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build && \
cmake --build build --target arkanoid-like
```

### Run

The program supports the following command-line parameters:

`--window, -w WIDTH,HEIGHT` - windowed mode with specified resolution

To run the executable:

```shell
./build/arkanoid-like --window 1024,1024
```

## TODO

* Game as shared_ptr<Game>
* magic numbers to namespace globals
* implement onCollision (think how to check against other entities... how to access them)
