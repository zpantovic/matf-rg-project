#include <engine/core/Engine.hpp>

/**
 * Start here...
 */

#include <spdlog/spdlog.h>
#include "Main.h"

int main(int argc, char** argv) {
    auto app = std::make_unique<app::Main>();
    return app->run(argc, argv);
}
void app::Main::app_setup() {
        spdlog::info("app setup completed");
}