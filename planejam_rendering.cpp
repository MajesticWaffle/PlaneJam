//
// Created by MajesticWaffle on 8/22/21.
//

#include "planejam.h"

GLFWwindow* rendering_init_opengl(uint window_x, uint window_y, uint scale){

    //Init GLFW
    if(glfwInit() != GLFW_TRUE){
        return nullptr;
    }

    //Create window and set context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* windowptr = glfwCreateWindow(window_x * scale, window_y * scale, "Planejam", nullptr, nullptr);
    glfwMakeContextCurrent(windowptr);
    glewInit();

    //Set up ortho projection
    glLoadIdentity();
    glOrtho(0, window_x, window_y, 0, 1, -1);
    glMatrixMode(GL_PROJECTION);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return windowptr;
}

void rendering_draw_player(Player* p, Texture* t){
    glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    texture_bind(t, 0);

    glBegin(GL_QUADS);{
        glTexCoord2i(0, 0); glVertex2d(p -> position,      480 - 80);
        glTexCoord2i(1, 0); glVertex2d(p -> position + 48, 480 - 80);
        glTexCoord2i(1, 1); glVertex2d(p -> position + 48, 480 - 80 + 48);
        glTexCoord2i(0, 1); glVertex2d(p -> position,      480 - 80 + 48);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3ub(255, 255, 255);
}

void rendering_draw_plan(Player* p){


    for(int i = (p -> world / 64); i < ((p -> world / 64) + (480 / 64)) + 1; ++i) {
        glColor3ub(255, 64, 64);
        glLineWidth(16);
        glBegin(GL_LINES);{
            glVertex2d(flight_plan_points[i],       480 - i * 64 + p -> world);
            glVertex2d(flight_plan_points[i + 1],   480 - (i + 1) * 64 + p -> world);
        }
        glEnd();

        glColor3ub(255, 200, 200);
        glLineWidth(10);
        glBegin(GL_LINES);{
            glVertex2d(flight_plan_points[i],       480 - i * 64 + p -> world);
            glVertex2d(flight_plan_points[i + 1],   480 - (i + 1) * 64 + p -> world);
        }
        glEnd();
    }
}