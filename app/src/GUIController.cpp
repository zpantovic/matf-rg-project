#include "GUIController.hpp"

#include "engine/graphics/BloomController.h"

#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <imgui.h>

namespace app {
void GUIController::initialize() {
    set_enable(false);
}

void GUIController::poll_events() {
    const auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KeyId::KEY_F2)
                .state() == engine::platform::Key::State::JustPressed) {
        set_enable(!is_enabled());
                }
}

void GUIController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    const auto bloom_controller = get<engine::graphics::BloomController>();
    graphics->begin_gui();

    ImGui::Begin("Debug Controls");

    if (ImGui::CollapsingHeader("Bloom Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::DragFloat("Bloom Intensity", &bloom_controller->bloom_strength, 0.1f, 0.0f, 5.0f);
        ImGui::DragFloat("Exposure", &bloom_controller->exposure, 0.1f, 0.1f, 3.0f);
        ImGui::DragInt("Bloom Passes", &bloom_controller->bloom_passes, 1, 0, 5);
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Camera Info", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto &c = *camera;
        ImGui::Text("Camera position: (%.2f, %.2f, %.2f)", c.Position.x, c.Position.y, c.Position.z);
        ImGui::Text("(Yaw, Pitch): (%.2f, %.2f)", c.Yaw, c.Pitch);
        ImGui::Text("Camera front: (%.2f, %.2f, %.2f)", c.Front.x, c.Front.y, c.Front.z);
    }

    ImGui::End();

    graphics->end_gui();
}

}
