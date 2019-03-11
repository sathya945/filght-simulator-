#include "main.h"

#ifndef water_H
#define water_H


class water {
public:
    water() {}
    water(float x, float y,float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;

};
class camera{
    public:
    camera(){}  
    camera(glm::vec3 P1,double theta,double phi,double radius);
    float m_theta;
    float m_phi;
    float aeroplane_yaw;
    float m_radius;
    glm::vec3 target;
    void Rotate(float dTheta, float dPhi);
    void Zoom(float distance);
    glm::vec3 eye();
};
#endif // water_H
