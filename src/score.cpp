#include "main.h"
#include "score.h"

using namespace std;

Score::Score(float x, float y) {
    this-> position = glm::vec3(x,y,0);
    this->length = 1;
    this->width = 0.25;
    float width = this->width;
    this->rotation = 0.0;
    GLfloat vertex_buffer_data_1[]={
      -length/2,width,0.0f,
      length/2,-width,0.0f,
      -length/2,-width,0.0f,  
    
      -length/2,width,0.0f,
       length/2,width,0.0f,
      length/2,-width,0.0f,        
    };

    GLfloat vertex_buffer_data_2[]={
        -length/2,(length/2)+3*width,0.0f,
        length/2,length/2+width, 0.0f,
        -length/2,length/2+width, 0.0f,
    
        -length/2,(length/2)+3*width,0.0f,
        length/2,(length/2)+3*width,0.0f,
        length/2,length/2+width, 0.0f,
        
    };

    GLfloat vertex_buffer_data_3[]={
        -length/2, (-length/2)-width,0.0f,
        length/2,(-length/2)-3*width,0.0f,
        -length/2, (-length/2)-3*width,0.0f,

        -length/2, (-length/2)-width,0.0f,
        length/2,  (-length/2)-width, 0.0f,
        length/2,(-length/2)-3*width,0.0f,

    };

    GLfloat vertex_buffer_data_4[]={
        (-length/2)-2*width, -width,0.0f,
        -length/2,(length/2)+3*width,0.0f,
        -length/2, -width, 0.0f,

        (-length/2)-2*width, -width,0.0f,
        (-length/2)-2*width, (length/2)+3*width,0.0f,
        -length/2, (length/2)+3*width, 0.0f, 
    };

    GLfloat vertex_buffer_data_5 [] ={
        length/2,-width,0.0f,
        (length/2) + 2*width, (length/2) + 3*width, 0.0f,
        (length/2) + 2*width, -width, 0.0f,

        length/2,-width,0.0f,
        length/2, (length/2) + 3*width, 0.0f,
        (length/2) + 2*width, (length/2) + 3*width, 0.0f,
    };

    GLfloat vertex_buffer_data_6 []= {
        (-length/2)-2*width, (-length/2)-3*width,0.0f,
        -length/2, -width, 0.0f,
        -length/2, (-length/2)-3*width, 0.0f,

        (-length/2)-2*width, (-length/2)-3*width,0.0f,
        (-length/2)-2*width, -width,0.0f,
        -length/2, -width, 0.0f,                
    };

    GLfloat vertex_buffer_data_7 []= {
         length/2,(-length/2)-3*width,0.0f,
        (length/2) + 2*width, -width, 0.0f,
        (length/2) + 2*width, (-length/2)-3*width, 0.0f,
        
         length/2,(-length/2)-3*width,0.0f,
        length/2,-width, 0.0f,
        (length/2) + 2*width, -width, 0.0f,
    };

    this->hor_1 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_1, {128,128,128}, GL_FILL);
    this->hor_2 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_2, {128,128,128}, GL_FILL);
    this->hor_3 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_3, {128,128,128}, GL_FILL);
    
    this->vert_1 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_4, {128,128,128}, GL_FILL);
    this->vert_2 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_5, {128,128,128}, GL_FILL);
    this->vert_3 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_6, {128,128,128}, GL_FILL);
    this->vert_4 = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_7, {128,128,128}, GL_FILL);

};


void Score::draw(glm::mat4 VP,int dig){
    int digit = dig;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); 
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(digit==2 || digit==3 || digit==4 || digit==5 || digit==6 || digit==8 ||digit==9 )
    draw3DObject(this->hor_1);
    
    if(digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9 || digit ==0 )
    draw3DObject(this->hor_2);
    if(digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8  || digit ==0)
    draw3DObject(this->hor_3);
    if(digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
    draw3DObject(this->vert_1);
    if(digit == 0 || digit == 2 || digit == 3 || digit == 7 || digit == 8 || digit == 1)
    draw3DObject(this->vert_2);
    if(digit == 0 || digit == 2 || digit == 6 || digit == 8 )
    draw3DObject(this->vert_3);
    if(digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7|| digit == 8 || digit == 9)
    draw3DObject(this->vert_4);

};
