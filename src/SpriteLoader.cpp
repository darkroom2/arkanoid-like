//
// Created by darkroom2 on 17/10/22.
//

#include <filesystem>
#include <iostream>
#include <algorithm>
#include <vector>
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


void SpriteLoader::init(const std::string &execPath) {
    std::filesystem::path execFile{execPath};
    dataDir = execFile.parent_path() / "data";
    for (const auto &entry: std::filesystem::recursive_directory_iterator(dataDir)) {
        auto s = createSprite(entry.path().c_str());
        sprites.emplace(entry.path().stem(), s);
    }
    typeMapping = {
            {EntityState::NORMAL,   "normal"},
            {EntityState::DAMAGED,  "damaged"},
            {EntityState::POSITIVE, "positive"},
            {EntityState::NEGATIVE, "negative"}
    };
    colorMapping = {
            {EntityColor::GREEN, "green"},
            {EntityColor::RED,   "red"}
    };
}

Sprite *SpriteLoader::getSprite(const std::string &name, EntityState state) {
    auto stateStr = typeMapping.at(state);
    std::string filename = _prepareFilename(std::vector<std::string>{name, stateStr});
    return sprites.at(filename);
}

Sprite *SpriteLoader::getSprite(const std::string &name, EntityState state, EntityColor color) {
    auto stateStr = typeMapping.at(state);
    auto colorStr = colorMapping.at(color);
    std::string filename = _prepareFilename(std::vector<std::string>{name, colorStr, stateStr});
    return sprites.at(filename);
}

std::string SpriteLoader::_prepareFilename(std::vector<std::string> vec) {
    std::string result;
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        result.append(*i);
        if (i != vec.end() - 1)
            result.append("-");
    }
    return result;
}
