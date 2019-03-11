#include "main.h"

#ifndef volcano_H
#define volcano_H

class volcano{
    public:
    volcano(float x,float y,float z,float height);
    glm::vec3 position;
    float r2;
    float r1;
    float h;
    void draw(glm::mat4 VP);
    private:
        VAO *object;
        VAO *object2;
};
class missile{
    public:
    missile(float x,float y,float z,glm::vec3 vector,bool mis);
    glm::vec3 position;
    glm::vec3 angle;
      glm::vec3 speed;
    float time;
    float yaw;
    float r;
    float h;
    void draw(glm::mat4 VP);
    private:
        VAO *object;
        VAO *object2;
};
class smoke_rings{
  public:
  smoke_rings(){};
  smoke_rings(glm::vec3 pos,float r,float star,float en);
  glm::vec3 position;
  float ring_radius;
  float r;
  float start;
  float end;
  float h;
  float rot;
void draw(glm::mat4 VP);
  private:
      VAO *object;
};

#endif // volcano_H