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

    virtual void PreInit(int &width, int &height, bool &fullscreen) {
        width = windowWidth;
        height = windowHeight;
        fullscreen = windowFullscreen;
    }

    virtual bool Init() {
        SpriteLoader::init(execPath);
        game = std::make_unique<Game>();
        return true;
    }

    virtual void Close() {

    }

    virtual bool Tick() {
        auto ticks = getTickCount();
        game->update(ticks);
        return false;
    }

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
        game->currentState->handleMouseMove(x, y, xrelative, yrelative);
    }

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
        game->currentState->handleMouseKey(button, isReleased);
    }

    virtual void onKeyPressed(FRKey k) {
        game->currentState->handleKey(k, true);
    }

    virtual void onKeyReleased(FRKey k) {
        game->currentState->handleKey(k, false);
    }

    virtual const char *GetTitle() override {
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
