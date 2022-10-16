//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_ARGPARSE_H
#define ARKANOID_LIKE_ARGPARSE_H


#include <string_view>

class ArgParse {
private:
    std::string _window_resolution;

public:
    void parse(int argc, char *argv[]);
};


#endif //ARKANOID_LIKE_ARGPARSE_H
