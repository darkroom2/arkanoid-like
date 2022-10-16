//
// Created by darkroom2 on 16/10/22.
//

#include <vector>
#include <stdexcept>
#include "../include/ArgParse.h"
#include <getopt.h>

void ArgParse::parse(int argc, char **argv) {
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    for (const auto &arg : args) {
        if (arg == "-w" || arg == "--window") {
            if (!_window_resolution.empty()) {
                throw std::runtime_error("arkanoid-like: Cannot use -w / --window parameter twice!");
            }
            _window_resolution = std::string("800x600");
        }
    }
}
