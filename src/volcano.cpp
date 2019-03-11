#include "volcano.h"
#include "main.h"
using namespace std;
volcano::volcano(float x,float y,float z,float height){
    position=glm::vec3(x,y,z);
    h=height;
    r1=1*height;
    r2=h*1/2;
    GLfloat data[360*18];
    create_cone_cyl(data,r1,r2,h);
    GLfloat data2[360*18];
    create_cone_cyl(data2,r2,r2,h);
    this->object=create3DObject(GL_TRIANGLES,360*6,data, {139,69,19}, GL_FILL);
    this->object2=create3DObject(GL_TRIANGLES,360*6,data2, {255,165,0}, GL_FILL);
}
void volcano::draw(glm::mat4 VP){
  Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}
missile::missile(float x,float y,float z,glm::vec3 vector,bool mis){
        position=glm::vec3(x,y,z);
        angle=vector;
        time=100;
        float v=50;
        speed=v*normalize(vector);  
        GLfloat data[360*18];
        r=3,h=4;
        create_cone_cyl(data,r,r,h);
        GLfloat data2[360*18];
        create_cone_cyl(data2,r+0.3,0,h/2);
        if(mis){
        this->object=create3DObject(GL_TRIANGLES,360*6,data, {256,256,256}, GL_FILL);
        this->object2=create3DObject(GL_TRIANGLES,360*6,data2, {250,128,114}, GL_FILL);
        }
        else
        {
             this->object=create3DObject(GL_TRIANGLES,360*6,data, {0,0,0}, GL_FILL);
        this->object2=create3DObject(GL_TRIANGLES,360*6,data2, {0,0,0}, GL_FILL);
        
        }
}
void missile::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f); 
    time--;
    position+=speed;
    speed.y-=0.1; 
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate1   = glm::rotate((float) (acos(dot(normalize(glm::vec3(0,0,1)),normalize(angle)))), cross(glm::vec3(0,0,1),angle));
    Matrices.model *= (translate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    translate = glm::translate (glm::vec3(0,0,4));
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);   
}
  smoke_rings::smoke_rings(glm::vec3 pos,float rr,float star,float en){
      position=pos;
      r=rr;
      start=star;
      end=en;
      h=5;
      rot=1;
      ring_radius=100;
      GLfloat data[360*18];
      create_cone_cyl(data,ring_radius,ring_radius,h);
      this->object=create3DObject(GL_TRIANGLES,360*6,data, {256,256,256}, GL_FILL);
  }
void smoke_rings::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f); 
    glm::mat4 translate = glm::translate (position);
    glm::mat4 translate1=glm::translate(glm::vec3(0,0,r));
    glm::mat4 rotate=glm::rotate((float) (rot* M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2=glm::rotate((float)(M_PI/2),glm::vec3(0,1,0));
    Matrices.model *= (translate);
    float angle=start;
    while(angle<end){
    angle+=rot;
    Matrices.model *= (rotate*translate1);
    auto MVP = VP * Matrices.model*rotate2;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model *=(glm::inverse(translate1));
    }
}

