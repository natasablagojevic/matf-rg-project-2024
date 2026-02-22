//
// Created by natasa on 2/22/26.
//

#include "../include/MainController.h"

#include "engine/graphics/GraphicsController.hpp"
#include "engine/graphics/OpenGL.hpp"
#include "engine/platform/PlatformController.hpp"
#include "engine/resources/ResourcesController.hpp"

#include <spdlog/spdlog.h>
namespace app {

void app::MainController::initialize() {
    spdlog::info("MainController initialized....");
    engine::graphics::OpenGL::enable_depth_testing();
}

bool app::MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
        return false;
    }

    return true;
}

void MainController::update_camera() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto *camera = graphics->camera();

    float dt = platform->dt();

    if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
    }

    if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
    }

    if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
    }

    if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
    }

    // gore
    if (platform->key(engine::platform::KeyId::KEY_U).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::UP, dt);
    }

    // dole
    if (platform->key(engine::platform::KeyId::KEY_H).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt);
    }
}

void MainController::update() {
    update_camera();
}

void app::MainController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

void MainController::draw_zeus() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *zeus = resources->model("zevs");

    engine::resources::Shader *shader = resources->shader("zeus");
    shader->use();

    shader->set_mat4("P", graphics->projection_matrix());
    shader->set_mat4("V", graphics->camera()->view_matrix());

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(0.0f, 0.0f, -3.0f));
    M = glm::scale(M, glm::vec3(0.5f));

    shader->set_mat4("M", M);

    zeus->draw(shader);
}

void app::MainController::draw() {
    draw_zeus();
}

void app::MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}

std::string_view app::MainController::name() const {
    return "app::MainController";
}

}// namespace app