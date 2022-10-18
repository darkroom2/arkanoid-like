//
// Created by darkroom2 on 17/10/22.
//

#ifndef ARKANOID_LIKE_SPRITELOADER_H
#define ARKANOID_LIKE_SPRITELOADER_H


#include <string>
#include <filesystem>
#include <vector>
#include "Entity.h"

class SpriteLoader {
    inline static std::filesystem::path dataDir;

    inline static std::map<std::string, Sprite *> sprites;

    inline static std::map<EntityState, std::string> typeMapping;
    inline static std::map<EntityColor, std::string> colorMapping;

    static std::string _prepareFilename(std::vector<std::string> vec);

public:

    static Sprite *getSprite(const std::string &name, EntityState state);

    static Sprite *getSprite(const std::string &name, EntityState state, EntityColor color);

    static void init(const std::string &execPath);
};


#endif //ARKANOID_LIKE_SPRITELOADER_H
