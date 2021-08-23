//
// Created by MajesticWaffle on 8/22/21.
// Made in 2 Hours, 44 minutes on flight DAL890 KMSP -> KSEA
//

#ifndef PLANEJAM_PLANEJAM_H
#define PLANEJAM_PLANEJAM_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"

#define TEXTURE_MULTIPLE 0x01
#define TEXTURE_SINGLE   0x02

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct{
    double x, y;
} Coord2d;

typedef struct{
    int x, y;
} Coord2i;

typedef struct{
    double position;
    double world;
    double world_speed;
} Player;

typedef struct Time{
    double delta;   //The time past between the previous and current frames
    double global;  //Absolute time since game was started
} Time;
//OpenGL texture id with dimensions and texture uv information
typedef struct Texture{
    GLuint id;          //OpenGL texture id
    uint width;         //Size of texture in pixels
    uint height;        //------------------------
    uint tile_size;     //Size of tiles
    Coord2d atlas_uvs;  //Difference in UV coordinates per texture
} Texture;

//Raw image data loaded from a BMP image
typedef struct Image{
    uint width;     //Size of image in pixels
    uint height;    //----------------------
    uchar* imageData; //Raw image data in RGB bmp format
} Image;

//playerjam_time.cpp
extern Time* g_time; //Global time object

//playerjam_input.cpp
extern bool g_k_keys[];   //Keyboard press booleans
extern bool g_m_keys[];   //Mouse button press booleans
extern int g_k_actions[]; //GLFW keyboard actions
extern int g_m_actions[]; //GLFW mouse button actions
extern Coord2d g_m_pos;   //Mouse position

extern int flight_plan_points[0xFFFF];

GLFWwindow* rendering_init_opengl(uint window_x, uint window_y, uint scale);
void rendering_draw_player(Player* p, Texture* t);
void rendering_draw_plan(Player* p);

Texture*    texture_generate(Image* img, uchar texture_load_options, uint tile_size);   //Generate Texture Object
Image*      texture_load_bmp(const char* path);                                         //Load a 24-bit BMP
void        texture_bind(Texture* t, GLuint sampler);                                   //Bind texture to GL_TEXTURE_2D

void input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);   //Keyboard callback
void input_mouse_button_callback(GLFWwindow* window, int button, int actions, int mods);    //Mouse button callback
void input_mouse_position_callback(GLFWwindow* window, double xpos, double ypos);           //Mouse position callback
void input_register_callbacks(GLFWwindow* window);                                          //Register all callbacks with GLFW

bool input_get_key(int keycode);        //Get key status
bool input_get_button(int keycode);     //Get button status
bool input_get_key_down(int keycode);   //Get new keystroke
bool input_get_mouse_down(int keycode); //Get new mouse stroke
void input_poll_input();                //Input poll

void time_update_time(double glfw_time);    //Update time
int  time_get_framerate();                  //Get FPS

inline std::string get_resource_path(const std::string& executable_path, const std::string& resource_name){
    uint substri = executable_path.find_last_of('/');
    return executable_path.substr(0, substri) + "/" + resource_name;
}

inline double interp(int min, int max, int steps, int i){
    double d = (double)(max - min) / (double)steps;

    if(i > steps)
        std::cout << "OOPP" << std::endl;
    return min + (d * i);
}
#endif //PLANEJAM_PLANEJAM_H
