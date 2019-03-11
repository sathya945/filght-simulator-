#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float z, color_t color);
    glm::vec3 position;
    double pitch,roll,yaw;
    double v;
    float fuel;
    float rotation;
    void draw(glm::mat4 VP);
    glm::vec3 roll_axis;
    glm::vec3 yaw_axis;
    glm::vec3 pitch_axis;
    void set_position(float x, float y);
    void tick();
    double speed;
    void tick(int up,int left);
private:
    VAO *object;
    VAO *d1;
    VAO *d2;
};

#endif // BALL_H
