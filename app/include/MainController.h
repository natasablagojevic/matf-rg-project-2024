//
// Created by natasa on 2/22/26.
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_H
#define MATF_RG_PROJECT_MAINCONTROLLER_H
#include "engine/core/Controller.hpp"

namespace app {

class MainController : public engine::core::Controller {
private:
    void initialize() override;
    bool loop() override;
    void update() override;
    void begin_draw() override;
    void draw() override;
    void end_draw() override;
    void draw_moon();
    void draw_island();
    void draw_ship();
    void draw_agent();
    void update_camera();

public:
    std::string_view name() const override;

};

}// namespace app

#endif//MATF_RG_PROJECT_MAINCONTROLLER_H
