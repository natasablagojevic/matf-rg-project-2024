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

static glm::vec3 ship_position = glm::vec3(3.0f, 4.0f, -10.0f);
static glm::vec3 island_position = glm::vec3(0.0f, 0.0f, -10.0f);
static glm::vec3 agent_position = glm::vec3(0.0f, 0.0f, -10.0f);
static glm::vec3 moon_position = glm::vec3(-2.5f, 2.5f, -10.f);

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
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *moon = resources->model("moon");

    engine::resources::Shader *shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("V", graphics->camera()->view_matrix());
    shader->set_mat4("P", graphics->projection_matrix());

    float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, moon_position);
    M = glm::scale(M, glm::vec3(0.085f));
    // M = glm::translate(M, glm::vec3(glm::cos(t)*50.0f, 0.0f, glm::sin(t)*50.f));
    // M = glm::rotate(M, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, glm::sign(t*0.5f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->set_mat4("M", M);

    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();

    shader->set_vec3("spotLight.pos", camera->Position);
    shader->set_vec3("spotLight.ambient", glm::vec3(0.0f));
    shader->set_vec3("spotLight.diffuse", glm::vec3(1.2f, 1.2f, 1.3f));
    shader->set_vec3("spotLight.specular", glm::vec3(1.0f));
    shader->set_vec3("spotLight.clq", glm::vec3(1.0f, 0.09f, 0.032f));

    shader->set_vec3("spotLight.direction", camera->Front);
    shader->set_float("spotLight.cutOff", glm::cos(glm::radians(12.0f)));
    shader->set_float("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

    shader->set_float("material.shi", 32.0f);

    shader->set_vec3("dirLight.dir", glm::normalize(moon_position - island_position));
    shader->set_vec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.5f));
    shader->set_vec3("dirLight.diffuse", glm::vec3(1.2f));
    shader->set_vec3("dirLight.specular", glm::vec3(0.3f));
    shader->set_bool("blin", false);

    moon->draw(shader);
}
void MainController::draw_island() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *island = resources->model("space_island");

    engine::resources::Shader *shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("V", graphics->camera()->view_matrix());
    shader->set_mat4("P", graphics->projection_matrix());

    float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, island_position);
    M = glm::scale(M, glm::vec3(0.25f));
    M = glm::rotate(M, glm::abs(glm::sign(t*0.5f)*0.2f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->set_mat4("M", M);

    island->draw(shader);
}
void MainController::draw_ship() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *ship = resources->model("space_ship");

    engine::resources::Shader *shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("V", graphics->camera()->view_matrix());
    shader->set_mat4("P", graphics->projection_matrix());

    float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, ship_position);
    M = glm::scale(M, glm::vec3(0.085f));
    M = glm::rotate(M, glm::sign(t)*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

    shader->set_mat4("M", M);

    ship->draw(shader);
}
void MainController::draw_agent() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *agent = resources->model("agent");

    engine::resources::Shader *shader = resources->shader("basic");
    shader->use();

    shader->set_mat4("V", graphics->camera()->view_matrix());
    shader->set_mat4("P", graphics->projection_matrix());

    float t = engine::core::Controller::get<engine::platform::PlatformController>()->frame_time().current;

    agent_position.y = glm::sin(t)*0.1f;

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, agent_position);
    M = glm::scale(M, glm::vec3(0.2f));

    shader->set_mat4("M", M);

    agent->draw(shader);
}

void app::MainController::draw() {
    draw_ship();
    draw_island();
    draw_agent();
    draw_moon();
}

void app::MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}

std::string_view app::MainController::name() const {
    return "app::MainController";
}

}// namespace app