#include <iostream>
#include "planejam.h"

int flight_plan_points[0xFFFF]{};
void create_points(Player* p);

std::string g_game_path;

bool failed = false;

int main(int argc, char* argv[]) {
    g_game_path = argv[0];

    GLFWwindow* windowptr = rendering_init_opengl(480,480, 2);
    Player*     playerptr = new Player {
            (480 / 2) - (48 / 2),   //Horizontal Position
            0,                      //World position
            128.0                     //World scroll speed
    };

    Image* plane_img = texture_load_bmp(get_resource_path(g_game_path, "resources/plane.bmp").c_str());
    Texture* plane = texture_generate(plane_img, TEXTURE_SINGLE, 32);

    flight_plan_points[0] = (480 / 2);

    //Disable Vsync
    glfwSwapInterval(0);
    input_register_callbacks(windowptr);
    create_points(playerptr);

    while(!glfwWindowShouldClose(windowptr)){
        input_poll_input();
        time_update_time(glfwGetTime());

        double moveS = 128.0 + (16.0 * playerptr -> world / 1024.0);

        playerptr -> position +=
                ((moveS / 2) * g_time -> delta) * ((input_get_key(GLFW_KEY_A) ? 0 : 1) - (input_get_key(GLFW_KEY_D) ? 0 : 1));

        playerptr -> world += (playerptr -> world_speed * g_time -> delta);
        playerptr -> world_speed = moveS;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor3ub(128, 168, 255);
        glBegin(GL_QUADS);{
            glVertex2i(0,    0);
            glVertex2i(480,  0);
            glVertex2i(480,  480);
            glVertex2i(0,    480);
        }glEnd();
        rendering_draw_plan(playerptr);
        rendering_draw_player(playerptr, plane);

        double desired_pos = interp(
                flight_plan_points[(int)(playerptr -> world / 64) + 1],
                flight_plan_points[(int)(playerptr -> world / 64) + 2],
                64,
                (int)(playerptr -> world) - (((int)playerptr -> world / 64) * 64)
                );

        std::cout << playerptr -> world << std::endl;

        if(std::abs(desired_pos - playerptr -> position) >= 64){
            failed = true;
        }


        if(failed){
            glColor3ub(255, 20, 20);
            glBegin(GL_QUADS);{
                glVertex2i(0,    0);
                glVertex2i(480,  0);
                glVertex2i(480,  480);
                glVertex2i(0,    480);
            }glEnd();
        }
        glfwSwapBuffers(windowptr);
    }

    glfwDestroyWindow(windowptr);
    return 0;
}

void create_points(Player* p){
    for(int i = 1; i < 0xFFFF; ++i){
        flight_plan_points[i] = flight_plan_points[i - 1];

        int maxd = 64 + (16 * i / 1024);
        flight_plan_points[i] += (maxd / 2) - (rand() / (RAND_MAX / maxd));

        if(flight_plan_points[i] < 16)
            flight_plan_points[i] = 16;

        if(flight_plan_points[i] > 464)
            flight_plan_points[i] = 464;
    }
}
