//
// Created by ndobrosavljevic on 7.10.25..
//

#include "MainController.h"

#include "engine/core/Controller.hpp"
#include "engine/graphics/GraphicsController.hpp"
#include "engine/graphics/OpenGL.hpp"
#include "engine/platform/PlatformController.hpp"
#include "engine/resources/ResourcesController.hpp"
#include "spdlog/spdlog.h"

namespace app {

    void MainController::initialize() {
        spdlog::info("MainController initialized");
        engine::graphics::OpenGL::enable_depth_testing();
    }

    bool MainController::loop() {
            auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
            if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
                return false;
            }
            return true;
        }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }
    void MainController::draw_babyoda() {
        // model
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        engine::resources::Model * babyoda = resources->model("babyoda3");

        // shader
        engine::resources::Shader* shader = resources->shader("basic");


        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);

        babyoda->draw(shader);
    }
    void MainController::draw() {
        //clear buffers color buffer i depth buffer
        draw_babyoda();
        //swapBuffers, kako bi sve sto smo nacrtali poslali na ekran.
    }
    void MainController::end_draw() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }


    }// namespace app
