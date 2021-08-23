//
// Created by MajesticWaffle on 8/22/21.
//

#include "planejam.h"

Time* g_time = new Time;

void time_update_time(double glfw_time){
    g_time -> delta = glfw_time - g_time -> global;
    g_time -> global = glfw_time;
}

int time_get_framerate(){
    return (int)(1.0 / g_time -> delta);
}
