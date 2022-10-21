#include "../libs/Framework/inc/Framework.h"
#include "../include/Game.h"
#include "../include/SpriteLoader.h"
#include <cxxopts.hpp>
#include <iostream>


/* Test Framework realization */
class ArkanoidLike : public Framework {
public:
    explicit ArkanoidLike(int windowWidth = 600, int windowHeight = 800, bool windowFullscreen = false) : windowWidth(
            windowWidth), windowHeight(windowHeight), windowFullscreen(windowFullscreen) {}

    static const char *GetDescription() {
        return "This is a game where you have to overcome the wall using a ball to reach victory!";
    }

    const std::string &getExecPath() const {
        return execPath;
    }

    void setExecPath(const std::string &path) {
        execPath = path;
    }

    void SetWindowSettings(int width, int height, bool fullscreen) {
        windowWidth = width;
        windowHeight = height;
        windowFullscreen = fullscreen;
    }

private:
    int windowWidth;
    int windowHeight;
    bool windowFullscreen;

    std::string execPath;
    std::shared_ptr<Game> game;

    void PreInit(int &width, int &height, bool &fullscreen) override {
        width = windowWidth;
        height = windowHeight;
        fullscreen = windowFullscreen;
    }

    bool Init() override {
        SpriteLoader::init(getExecPath());
        game = std::make_shared<Game>();
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

    void onMouseMove(int x, int y, int xRelative, int yRelative) override {
        game->currentState->onMouseMove(x, y, xRelative, yRelative);
    }

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override {
        game->currentState->onMouseButtonClick(button, isReleased);
    }

    void onKeyPressed(FRKey k) override {
        game->currentState->onKeyPressed(k, true);
    }

    void onKeyReleased(FRKey k) override {
        game->currentState->onKeyPressed(k, false);
    }

    const char *GetTitle() override {
        return "Arkanoid Like";
    }
};


int main(int argc, const char *argv[]) {
    auto arkanoidLike = std::make_unique<ArkanoidLike>();
    try {
        std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(argv[0], arkanoidLike->GetDescription()));
        auto &options = *allocated;

        arkanoidLike->setExecPath(options.program());

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
                std::cout << "Provide two arguments [w,h] eg. 800,600" << std::endl;
                return -1;
            }
            arkanoidLike->SetWindowSettings(values[0], values[1], false);
        } else {
            arkanoidLike->SetWindowSettings(0, 0, true);
        }
    }
    catch (const cxxopts::exceptions::exception &e) {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        return -1;
    }
    return run(arkanoidLike.get());
}
