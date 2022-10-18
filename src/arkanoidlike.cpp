#include "../libs/Framework/inc/Framework.h"
#include "../include/Game.h"
#include "../include/SpriteLoader.h"
#include <cxxopts.hpp>
#include <iostream>


/* Test Framework realization */
class ArkanoidLike : public Framework {
private:
    int windowWidth;
    int windowHeight;
    bool windowFullscreen;

public:
    explicit ArkanoidLike(
            uint16_t windowWidth = 600,
            uint16_t windowHeight = 800,
            bool windowFullscreen = false
    ) : windowWidth(windowWidth),
        windowHeight(windowHeight),
        windowFullscreen(windowFullscreen) {
    }

    std::string execPath;
    std::unique_ptr<Game> game;

    void PreInit(int &width, int &height, bool &fullscreen) override {
        width = windowWidth;
        height = windowHeight;
        fullscreen = windowFullscreen;
    }

    bool Init() override {
        SpriteLoader::init(execPath);
        game = std::make_unique<Game>();
        return true;
    }

    void Close() override {
        SpriteLoader::clearSprites();
    }

    bool Tick() override {
        auto ticks = getTickCount();
        game->update(ticks);
        return false;
    }

    void onMouseMove(int x, int y, int xrelative, int yrelative) override {
        game->currentState->handleMouseMove(x, y, xrelative, yrelative);
    }

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override {
        game->currentState->handleMouseKey(button, isReleased);
    }

    void onKeyPressed(FRKey k) override {
        game->currentState->handleKey(k, true);
    }

    void onKeyReleased(FRKey k) override {
        game->currentState->handleKey(k, false);
    }

    const char *GetTitle() override {
        return "Arcanoid Like";
    }

    virtual const char *GetDescription() {
        return "This is a game where you have to overcome the wall using a ball to reach victory!";
    }

    virtual void SetWindowSettings(int w, int h, bool fullscreen) {
        windowWidth = w;
        windowHeight = h;
        windowFullscreen = fullscreen;
    }
};


int main(int argc, const char *argv[]) {
    auto arkanoidlike = std::make_unique<ArkanoidLike>();
    try {
        std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(argv[0], arkanoidlike->GetDescription()));
        auto &options = *allocated;

        arkanoidlike->execPath = options.program();

        options.add_options()
                ("h,help", "Print help")
                ("w,window", "Window resolution [W,H] eg. -w 800,600", cxxopts::value<std::vector<int>>());

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        if (result.count("window")) {
            const auto values = result["window"].as<std::vector<int>>();
            if (values.size() != 2) {
                std::cout << "provide two arguments [w,h] eg. 800,600" << std::endl;
                return -1;
            }
            arkanoidlike->SetWindowSettings(values[0], values[1], false);
        } else {
            arkanoidlike->SetWindowSettings(0, 0, true);
        }
    }
    catch (const cxxopts::exceptions::exception &e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        return -1;
    }
    return run(arkanoidlike.get());
}
