#include <engine/core/Engine.hpp>

/**
 * Start here...
 */

#include <spdlog/spdlog.h>
#include "Main.h"

#include "GUIController.hpp"
#include "MainController.h"
#include "engine/graphics/BloomController.h"

int main(int argc, char** argv) {
    auto app = std::make_unique<app::Main>();
    return app->run(argc, argv);
}
void app::Main::app_setup() {
        spdlog::info("app setup completed");
        auto main_controller = register_controller<MainController>();
        auto gui_controller = register_controller<GUIController>();
        auto bloom_controller = register_controller<engine::graphics::BloomController>();
        main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
        bloom_controller->after(main_controller);
        gui_controller->after(main_controller);
        bloom_controller->after(gui_controller);

}