//
// Created by natasa on 2/22/26.
//

#include "../include/MainController.h"

#include "engine/graphics/GraphicsController.hpp"
#include "engine/graphics/OpenGL.hpp"
#include "engine/platform/PlatformController.hpp"
#include "engine/resources/ResourcesController.hpp"
#include "imgui_impl_opengl3_loader.h"

#include <spdlog/spdlog.h>
namespace app {

class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
    void on_mouse_move(engine::platform::MousePosition position) override;
    void on_scroll(engine::platform::MousePosition position) override;
};

void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    camera->rotate_camera(position.dx, position.dy);
}

void MainPlatformEventObserver::on_scroll(engine::platform::MousePosition position) {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = graphics->camera();
    auto mouse = engine::core::Controller::get<engine::platform::PlatformController>()->mouse();

    camera->zoom(mouse.scroll);
    graphics->perspective_params().FOV = glm::radians(camera->Zoom);
}

void app::MainController::initialize() {
    spdlog::info("MainController initialized....");

    // auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    // platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());

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
    if (platform->key(engine::platform::KeyId::KEY_UP).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::UP, dt);
    }

    // dole
    if (platform->key(engine::platform::KeyId::KEY_DOWN).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt);
    }
}

void MainController::update() {
    update_camera();
}

void app::MainController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

// void MainController::draw_zeus() {
//     auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
//     auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
//
//     engine::resources::Model *zeus = resources->model("zevs");
//
//     engine::resources::Shader *shader = resources->shader("basic");
//     shader->use();
//
//     shader->set_mat4("P", graphics->projection_matrix());
//     shader->set_mat4("V", graphics->camera()->view_matrix());
//
//     float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;
//
//     glm::mat4 M = glm::mat4(1.0f);
//     M = glm::translate(M, glm::vec3(0.0f, 0.0f, -3.0f));
//     M = glm::scale(M, glm::vec3(0.65f));
//     M = glm::rotate(M, 1.5f * t, glm::vec3(0.0f, 1.0f, 0.0f));
//
//     shader->set_mat4("M", M);
//
//     shader->set_vec3("pointLight.pos", glm::vec3(2.0f, 3.0f, 2.0f));
//     shader->set_vec3("pointLight.ambient", glm::vec3(0.05f));
//     shader->set_vec3("pointLight.diffuse", glm::vec3(0.8f));
//     shader->set_vec3("pointLight.specular", glm::vec3(1.0f));
//     shader->set_vec3("pointLight.clq", glm::vec3(0.36f, 0.0003f, 0.000005f));
//     shader->set_float("material.shi", 32.0f);
//
//     shader->set_vec3("dirLight.dir", glm::vec3(-0.2f, -1.0f, -0.3f));
//     shader->set_vec3("dirLight.ambient", glm::vec3(0.2f));
//     shader->set_vec3("dirLight.diffuse", glm::vec3(0.5f));
//     shader->set_vec3("dirLight.specular", glm::vec3(1.0f));
//
//     shader->set_float("material.shi", 32.0f);
//
//     // shader->set_int("material.diffuse", 0);
//     // glActiveTexture(GL_TEXTURE0);
//
//
//     shader->set_float("blin", false);
//
//
//
//     zeus->draw(shader);
// }

// void MainController::draw_styria() {
//     auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
//     auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
//
//     engine::resources::Model *styria = resources->model("styria");
//
//     engine::resources::Shader *shader = resources->shader("basic");
//     shader->use();
//
//     shader->set_mat4("P", graphics->projection_matrix());
//     shader->set_mat4("V", graphics->camera()->view_matrix());
//
//     float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;
//
//     glm::mat4 M = glm::mat4(1.0f);
//     M = glm::translate(M, glm::vec3(-2.5f, -1.0f, -3.0f));
//     M = glm::scale(M, glm::vec3(0.25f));
//     M = glm::rotate(M, 1.5f * t, glm::vec3(0.0f, 1.0f, 0.0f));
//     shader->set_mat4("M", M);
//
//     styria->draw(shader);
// }

void MainController::draw_moon() {

}
void MainController::draw_island() {
}
void MainController::draw_ship() {
}
void MainController::draw_agent() {
}

void app::MainController::draw() {
    draw_moon();
    draw_island();
    draw_ship();
    draw_agent();
}

void app::MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}

std::string_view app::MainController::name() const {
    return "app::MainController";
}

}// namespace app