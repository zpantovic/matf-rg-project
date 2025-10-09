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

class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
public:
    void on_mouse_move(engine::platform::MousePosition position) override;
};

static glm::vec3 islandPosition = glm::vec3(0.0f, -30.0f, 0.0f);
static glm::vec3 yodaPosition = glm::vec3(500.0f, 250.0f, 0.0f);
static glm::vec3 shipPosition = glm::vec3(2100.0f, 700.0f, 0.0f);

void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    camera->rotate_camera(position.dx, position.dy);
}


void MainController::initialize() {
    spdlog::info("MainController initialized");
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
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
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();

    auto babyoda = resources->model("babyoda3");
    auto shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, islandPosition + glm::vec3(80.0f, 15.6f, 0.0f));
    model = glm::scale(model, glm::vec3(5));
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    float rotating = 1.5f * platform->frame_time().current;
    model = glm::rotate(model, rotating, glm::vec3(0.0f, 1.0f, 0.0f));

    shader->set_mat4("model", model);

    babyoda->draw(shader);
}
void MainController::draw_island() {

    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();

    auto island = resources->model("island1");
    auto shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, islandPosition);
    model = glm::scale(model, glm::vec3(0.04f));
    shader->set_mat4("model", model);

    island->draw(shader);
}

void MainController::draw_svbrod() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();

    auto svbrod = resources->model("svbrod1");
    auto shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, shipPosition);
    model = glm::scale(model, glm::vec3(100.0f));
    shader->set_mat4("model", model);

    svbrod->draw(shader);
}

void MainController::draw_skybox() {
    auto shader = engine::core::Controller::get<engine::resources::ResourcesController>()->shader("skybox");
    auto skybox_cube = engine::core::Controller::get<engine::resources::ResourcesController>()->skybox("skybox");
    engine::core::Controller::get<engine::graphics::GraphicsController>()->draw_skybox(shader, skybox_cube);
}

void MainController::draw() {
    //clear buffers color buffer i depth buffer
    draw_babyoda();
    draw_island();
    draw_svbrod();
    draw_skybox();
    //swapBuffers, kako bi sve sto smo nacrtali poslali na ekran.
}
void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
void MainController::update_camera() {

    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    float dt = platform->dt();
    if (platform->key(engine::platform::KEY_W)
                .state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt+0.5);
    }
    if (platform->key(engine::platform::KEY_S)
                .state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt+0.5);
    }
    if (platform->key(engine::platform::KEY_A)
                .state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt+0.5);
    }
    if (platform->key(engine::platform::KEY_D)
                .state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt+0.5);
    }
    auto mouse = platform->mouse();
    camera->rotate_camera(mouse.dx, mouse.dy);
    camera->zoom(mouse.scroll);
}

void MainController::update() {
    update_camera();
}


}// namespace app
