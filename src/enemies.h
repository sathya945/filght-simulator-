#include "main.h"

#ifndef enemies_H
#define enemies_H
class cannon{
    public:
        cannon(glm::vec3 P,float vel);
        glm::vec3 position;
        int time;
        float stand_height;
        float cutoff_time;
        float vel;
        float r;
        glm::vec3 angle;
        void tick(glm::vec3 P);
        void draw(glm::mat4 VP);
    private:
        VAO *object;
        VAO *object2;
};
class bullets{
    public:
        bullets(glm::vec3 P1,glm::vec3 P2,float r);
        glm::vec3 position;
        float r;
        float time;
        float v;
        glm::vec3 angle;
        void draw(glm::mat4 VP);
    private:
          VAO *object;
};
class para{
    public:
        para(glm::vec3 P);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float v;
    private:
        VAO *object;
        VAO *object2;
        VAO *object3;
};
#endif // water_H
