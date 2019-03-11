#include "water.h"
#include "main.h"
using namespace std;

water::water(float x,float y,float z){
    this->position=glm::vec3(x,y,z);
    float l=10000 ;
    GLfloat data[]={
     l,0,l,
     l,0,-l,
     -l,0,l,
    l,0,-l,
     -l,0,l,
     -l,0,-l,
    };
    this->object = create3DObject(GL_TRIANGLES,6,data, {28,163,236}, GL_FILL);
}
void water::draw(glm::mat4 VP){
     Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
        Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object);
    translate = glm::translate (glm::vec3(0,1000,0));
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  //  draw3DObject(this->object);
}
camera::camera(glm::vec3 P1,double theta,double phi,double radius){    
    m_radius=radius;
    m_phi=phi;
    m_theta=theta;
    target=P1;
}
void camera::Rotate(float dTheta, float dPhi) {
    m_theta += dTheta;
    m_phi += dPhi;
}

void camera::Zoom(float distance) {
    m_radius -= distance;
}
glm::vec3 camera::eye() {
    float yaw=-aeroplane_yaw;
    float x = m_radius * sinf(m_phi) * sinf(m_theta);
    float y = m_radius * cosf(m_phi);
    float z = m_radius * sinf(m_phi) * cosf(m_theta);
  // float yaw=-aeroplane_yaw;
    //float ax=x*cos(yaw*M_PI/180)+z*sin(yaw*M_PI/180),ay=y,az=x*sin(yaw*M_PI/180)+z*cos(yaw*M_PI/180);
    return target+glm::vec3(x, y, z);
}