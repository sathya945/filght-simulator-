#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    pitch=yaw=roll=0;
    yaw=90;
    v=10;
    fuel=10000;
    GLfloat data[360*18];
    create_cone_cyl(data,7,5,28);
    GLfloat data2[360*18];
    create_cone_cyl(data2,5,0,8);
    float l=50,b=10,h=-0.1; 
    GLfloat rect_data[108];
    Cuboid(rect_data,l,b,h);
    this->object = create3DObject(GL_TRIANGLES,360*6,data, {105,105,105}, GL_FILL);
    this->d1=create3DObject(GL_TRIANGLES,360*6,data2, {105,105,105}, GL_FILL);
    this->d2=create3DObject(GL_TRIANGLES,36,rect_data,{105,105,105},GL_FILL);
}
void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1   = glm::rotate((float) (yaw* M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate((float) (pitch* M_PI / 180.0f), glm::vec3(1, 0,0 ));
    glm::mat4 rotate3 = glm::rotate((float) (roll* M_PI / 180.0f), glm::vec3(0, 0,1 ));
    roll_axis =(rotate1*rotate2*rotate3*glm::vec4(0,0,1,0));
    yaw_axis=(rotate1*rotate2*rotate3*glm::vec4(0,1,0,0));  
    pitch_axis=(rotate1*rotate2*rotate3*glm::vec4(1,0,0,0));
    Matrices.model *= (translate*rotate1*rotate2*rotate3);
    auto temp=Matrices.model;
    Matrices.model*=glm::translate (glm::vec3(0,0,-10));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
     Matrices.model*=glm::translate (glm::vec3(0,0,28));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->d1);
    Matrices.model=temp;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);         
    draw3DObject(this->d2);
    glm::vec3 move(v*roll_axis.x,v*roll_axis.y,v*roll_axis.z);
    position+=move;
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int up,int left) {
    fuel-=v/3;
    roll-=left;
    if(roll>45)roll=45;
    if(roll<-45)roll=-45;
     yaw-=roll/70;
     pitch-=up;
     if(pitch>30)pitch=30;
     if(pitch<-30)pitch=-30;
     if(left==0){
     if(roll>0)roll--;
     if(roll<0) roll++;
     }
     if(up==0){
      if(pitch>0)pitch--;
     if(pitch<0) pitch++;
     }
     glm::mat4 rotate1   = glm::rotate((float) (yaw* M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate((float) (pitch* M_PI / 180.0f), glm::vec3(1, 0,0 ));
    glm::mat4 rotate3 = glm::rotate((float) (roll* M_PI / 180.0f), glm::vec3(0, 0,1 ));
    roll_axis =(rotate1*rotate2*rotate3*glm::vec4(0,0,1,0));
    yaw_axis=(rotate1*rotate2*rotate3*glm::vec4(0,1,0,0));  
    pitch_axis=(rotate1*rotate2*rotate3*glm::vec4(1,0,0,0));
}

