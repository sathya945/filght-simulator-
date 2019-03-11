#include "enemies.h"
#include "main.h"
using namespace std;

cannon::cannon(glm::vec3 P,float ve){
    position=P;
    this->vel=ve;
    r=40;
    cutoff_time=100;
    time=0;
    float h=100;
    stand_height=200;
    GLfloat data[108];
    Cuboid(data,200,200,400);
     GLfloat data2[360*18];
    create_cone_cyl(data2,r,r/2,h);
    this->object = create3DObject(GL_TRIANGLES,36,data, {160,82,45}, GL_FILL);
    this->object2=create3DObject(GL_TRIANGLES,360*6,data2, {0,0,0}, GL_FILL);
}
void cannon::tick(glm::vec3 P){
    angle=P-position;
    position.x+=(vel*normalize(angle).x);
    position.z+=(vel*normalize(angle).z);
    if(time==0)time=cutoff_time;
    time--;
}
void cannon::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 trans=glm::translate(glm::vec3(0,-stand_height,0));
    Matrices.model *= (trans);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
     trans=glm::translate(glm::vec3(0,stand_height,0));
        Matrices.model *= (trans);
    glm::mat4 rotate1   = glm::rotate((float) (acos(dot(normalize(glm::vec3(0,0,1)),normalize(angle)))), cross(glm::vec3(0,0,1),normalize(angle)));
    Matrices.model*=rotate1;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
 draw3DObject(this->object2);   
}
bullets::bullets(glm::vec3 P1,glm::vec3 P2,float r){
    position=P1;
    v=30;
    time=200;
    angle=normalize(P2);
    GLfloat data[1980];   
    create_sphere(data,r);
    this->object=create3DObject(GL_TRIANGLES,1980/3,data, {0,0,0}, GL_FILL);
}
void bullets::draw(glm::mat4 VP){
    position+=v*angle;
    time--;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


para::para(glm::vec3 p){
position=p;
v=3;
    GLfloat data[1980];
    float r=100;
    create_sphere(data,r);
    GLfloat data2[360*18];
    create_cone_cyl(data2,r,0,r/2);
    GLfloat data3[108];
    Cuboid(data3,r/2,r/2,r/2);
    this->object=create3DObject(GL_TRIANGLES,1980/6,data, {255,69,0}, GL_FILL);
    this->object2=create3DObject(GL_TRIANGLES,360*6,data2, {124,252,0}, GL_FILL);
    this->object3=  create3DObject(GL_TRIANGLES,36,data3, {124,252,0}, GL_FILL);
}
void para::draw(glm::mat4 VP){
position-=v*glm::vec3(0,1,0);
   Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model *= glm::translate(glm::vec3(0,-75,0));
     MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
        Matrices.model *= glm::inverse(glm::translate(glm::vec3(0,-75,0)));

    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model*=rotate;
     MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}