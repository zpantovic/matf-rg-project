//
// Created by ndobrosavljevic on 7.10.25..
//

#include "MainController.h"

#include "engine/core/Controller.hpp"
#include "engine/platform/PlatformController.hpp"
#include "engine/resources/ResourcesController.hpp"
#include "spdlog/spdlog.h"

namespace app {

    void MainController::initialize() {
        spdlog::info("MainController initialized");
    }

    bool MainController::loop() {
            auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
            if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
                return false;
            }
            return true;
        }

    void MainController::begin_draw() {

    }
    void MainController::draw_babyoda() {
        // model
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        engine::resources::Model * model = resources->model("babyoda3");

        // shader
        engine::resources::Shader* shader = resources->shader("basic");

        model->draw(shader);
    }
    void MainController::draw() {
        draw_babyoda();
    }
    void MainController::end_draw() {

    }


    }// namespace app
