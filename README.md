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

* There is an enemy turret, which randomly moves and shoots a player. Bullets spawned by a turret should pass through
  blocks and not destroy them. Game ends if the player is hit by a bullet.
* The first ability (positive) increases the size of the platform and the second one (negative) decreases it by 40%.
  Ability stays active for 20 seconds. Abilities are “stackable”, it means that it is possible to have multiple active
  instances of the same ability. Minimum size is 50%, maximum is 200% of a default size.
* fix perks and ~~sprites resizing~~
* ~~ball reflects from block horizontal and vertical edges~~
* ball reflects from paddle depending on hitbox
* make level switching
* own command-line parameters parser
* Game as shared_ptr<Game>
* magic numbers to namespace globals
