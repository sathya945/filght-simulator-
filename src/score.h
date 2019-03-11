#include "main.h"

#ifndef SCORE_H
#define SCORE_H

class Score
{
  public:
    Score() {}
    Score(float x, float y);
    glm::vec3 position;
    float length;
    float width;
    float rotation;
    void draw(glm::mat4 VP,int dig);
    void tick();
  private:
    VAO* hor_1;
    VAO* hor_2;
    VAO* hor_3;
    VAO* vert_1;
    VAO* vert_2;
    VAO* vert_3;
    VAO* vert_4;
};

#endif