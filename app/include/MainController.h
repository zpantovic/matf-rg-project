//
// Created by ndobrosavljevic on 7.10.25..
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_H
#define MATF_RG_PROJECT_MAINCONTROLLER_H
#include "engine/core/Controller.hpp"

namespace app {

    class MainController : public engine::core::Controller {
        void initialize() override;
        bool loop() override;
        void begin_draw() override;
        void draw_babyoda();
        void draw_skybox();
        void draw() override;
        void end_draw() override;
        void update_camera();
        void update() override;
    };
}


#endif//MATF_RG_PROJECT_MAINCONTROLLER_H
