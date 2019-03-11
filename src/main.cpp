#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "volcano.h"
#include "map.h"
#include "enemies.h"
#include "score.h"
using namespace std;


GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int mini_cam=0;
int cam=4,camera_timeout=0;
int test=0;
int score=0;
Ball ball1;
smoke_rings rings;
int missile_timeout=0;
water water_base;
camera m_camera;
vector <volcano> map_volcano;
vector <missile> missiles;
vector <cannon> ene;
vector <para> parachu;
vector <bullets> cannon_bullets;
float screen_zoom = 0.1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
glm::vec3 eye(0,0,0);
Timer t60(1.0 / 120);
double mouselastx,mouselasty;
void cursor_position_callback(GLFWwindow *window, double x, double y) ;
void check_volcano();
void missiles_enem();
void Print_screen();
VAO * aim;
VAO * show_direction;
void init_arrow();
void bullets_aero();
bool volcano_collision(float x,float z,float h1,float r,float x1,float z1,float h2,float l,float yaw);
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    glm::vec3 target;
    glm::vec3 up ;
    if(cam%5 == 1) {
        eye = glm::vec3(ball1.position.x + 25.0f * ball1.roll_axis.x+ball1.yaw_axis.x,ball1.position.y + 25.0f * ball1.roll_axis.y+ball1.yaw_axis.y,ball1.position.z + 25.0f * ball1.roll_axis.z+ball1.yaw_axis.z); 
        target = glm::vec3(ball1.position.x + 60.0f * ball1.roll_axis.x+ball1.yaw_axis.x,ball1.position.y + 60.0f * ball1.roll_axis.y+ball1.yaw_axis.y,ball1.position.z + 60.0f * ball1.roll_axis.z+ball1.yaw_axis.z);
        up = ball1.yaw_axis;
    } if(cam%5 == 0) {
        eye = ball1.position - 90.0f * ball1.roll_axis  +20.0f*ball1.yaw_axis;
        // eye = plane.position - 15.0f * plane.roll_axis  + glm::vec3(0, 5, 0);
        target = ball1.position+20.0f*ball1.yaw_axis;
        up = ball1.yaw_axis;
    } if(cam%5 == 2) {
        eye = ball1.position + glm::vec3(0, 50, 0);
        target = ball1.position;
        up = glm::vec3(1, 0, 0);
    }
     if(cam%5 == 3) {
        eye = ball1.position + glm::vec3(0, 40, 0) + glm::vec3(0, 0, 30);
        target = ball1.position;
        up = glm::vec3(0, 1, 0);
    }
    if(cam%5==4){
        eye=m_camera.eye();
        target=ball1.position;
        up = glm::vec3(0, 1, 0);
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye,target,up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
        //map_volcano[0].draw(glm::mat4(1.0f));
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view; 
        // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part) 
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    ball1.draw(VP);
    for(int i=0;i<map_volcano.size();i++){
        map_volcano[i].draw(VP);
    }
    for(int i=0;i<missiles.size();i++){
        missiles[i].draw(VP);
    }
    for(int i=0;i<ene.size();i++){
        ene[i].draw(VP);
    }
      for(int i=0;i<parachu.size();i++){
        parachu[i].draw(VP);
    }
     for(int i=0;i<cannon_bullets.size();i++){
        cannon_bullets[i].draw(VP);
        if(cannon_bullets[i].time<1){
            cannon_bullets.erase(cannon_bullets.begin()+i);
            i--;
        }
    }
    rings.draw(VP);
   water_base.draw(VP);
    draw_aim(VP);
    draw_arrow(VP);
}
void draw_2d(){

      int windowheight,windowwidth;
    glfwGetWindowSize( window,&windowwidth, &windowheight );
     float top    = screen_center_y + (4.0*windowheight/windowwidth) / screen_zoom;
    float bottom = screen_center_y - (4.0*windowheight/windowwidth)/ screen_zoom;
    float left   = screen_center_x - (4.0) / screen_zoom;
    float right  = screen_center_x + (4.0) / screen_zoom;
    glm::mat4   view = glm::lookAt(ball1.position+900.0f*ball1.yaw_axis, ball1.position, glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::ortho(left, right, bottom, top, 0.1f, 1000.0f);
    glm::mat4 VP = projection * view;
    ball1.draw(VP);
    for(int i=0;i<map_volcano.size();i++){
        map_volcano[i].draw(VP);
    }
    for(int i=0;i<missiles.size();i++){
        missiles[i].draw(VP);
    }
    for(int i=0;i<ene.size();i++){
        ene[i].draw(VP);
    }
      for(int i=0;i<parachu.size();i++){
        parachu[i].draw(VP);
    }
     for(int i=0;i<cannon_bullets.size();i++){
        cannon_bullets[i].draw(VP);
        if(cannon_bullets[i].time<1){
            cannon_bullets.erase(cannon_bullets.begin()+i);
            i--;
        }
    }
    rings.draw(VP);
   water_base.draw(VP);
    draw_aim(VP);
    draw_arrow(VP);
}
void rand_parachut(){
    if(rand()%100==0){
        parachu.push_back(para(glm::vec3(rand()%10000-5000,3000,rand()%10000-5000)));
    }
}
void para_coll(){
    for(int i=0;i<missiles.size();i++){
        glm::vec3 P=missiles[i].position;
        float r1=missiles[i].r;
        for(int j=0;j<parachu.size();j++){
         glm::vec3 P1=parachu[j].position;
         float r2=100;
         if(glm::distance(P,P1)<r2+r1){
             missiles.erase(missiles.begin()+i);
             parachu.erase(parachu.begin()+j);
             j--;
             i--;
         }
        }   
    }
}

void tick_input(GLFWwindow *window) {
    glfwSetScrollCallback(window, scroll_callback);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up=glfwGetKey(window,GLFW_KEY_UP);
    int down=glfwGetKey(window,GLFW_KEY_DOWN);
    int M=glfwGetKey(window,GLFW_KEY_M);
    int W=glfwGetKey(window,GLFW_KEY_W);
    int B=glfwGetKey(window,GLFW_KEY_B);
    if(W)ball1.v+=0.02;
    int change_camera=glfwGetKey(window,GLFW_KEY_C);
    if(change_camera && camera_timeout==0 ){cam++;camera_timeout=60;}
    if(M){
        if(missile_timeout==0){
            missile_timeout=60;
            missiles.push_back(missile(ball1.position.x,ball1.position.y,ball1.position.z,ball1.roll_axis,true));
        }
    }
    if(B){
        if(missile_timeout==0){
            missile_timeout=60;
            missiles.push_back(missile(ball1.position.x,ball1.position.y,ball1.position.z,-ball1.yaw_axis,false));
        }
    }
    if(camera_timeout>0)camera_timeout--;
    if(missile_timeout>0)
        missile_timeout--;
    ball1.tick(up-down,left-right);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    int c=glfwGetKey(window,GLFW_KEY_C);
    test=(test+1)%4;
}

void tick_elements() {
    rand_parachut();
    para_coll();
   if(ball1.position.y<7 || ball1.fuel<0 )exit(0);
m_camera.target=ball1.position;
m_camera.aeroplane_yaw=ball1.yaw;
check_volcano();
   for(int i=0;i<ene.size();i++){
        ene[i].tick(ball1.position);
        if(ene[i].time==ene[i].cutoff_time-1){
            cannon_bullets.push_back(bullets(ene[i].position,ene[i].angle+float(ball1.v)*ball1.roll_axis,30));
        }
    }
 bullets_aero();
 missiles_enem();
}
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1       = Ball(0, 300,0,COLOR_RED);
    water_base =water(0,0,0);
    init_volcano(map_volcano);
    rings=smoke_rings(glm::vec3(0,60,0),8000,0,360);
    init_cannon(ene);
     GLfloat data[1980];   
    create_sphere(data,3);
    aim=create3DObject(GL_TRIANGLES,1980/3,data, {255,0,0}, GL_FILL);
    m_camera=camera(glm::vec3(0,0,0),-90,45,100);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    init_arrow();
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor ( 	62/256.0, 142/256.0, 173/256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
glfwGetCursorPos(window, &mouselastx, &mouselasty);
    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands

            draw();
                                    Print_screen();
            int wh,ww;
            glfwGetWindowSize( window,&ww, &wh );
            glViewport (3.0/4.0*wh, 3.0/4.0*wh,  ww/4, wh/4);
            draw_2d();              
            glViewport (0,0,  ww, wh);
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_input(window);
            tick_elements();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    int windowheight,windowwidth;
    glfwGetWindowSize( window,&windowwidth, &windowheight );
    Matrices.projection = glm::perspective( 45.0f,
    (windowwidth / float(windowheight)),      
    0.1f,
    100000.0f );
}
void create_cone_cyl(GLfloat *data,float radius1,float radius2,float height){
    float radians=0;
 for(int i=0;i<360*18;i+=18){
        data[i]=radius1*cos(radians+M_PI/180);
        data[i+1]=radius1*sin(radians+M_PI/180);
        data[i+2]=0;
        data[i+3]=radius1*cos(radians);
        data[i+4]=radius1*sin(radians);
        data[i+5]=0;
         data[i+6]=radius2*cos(radians);
        data[i+7]=radius2*sin(radians);
        data[i+8]=height;
        data[i+9]=radius2*cos(radians);
        data[i+10]=radius2*sin(radians);
        data[i+11]=height;
        data[i+12]=radius1*cos(radians+M_PI/180);
        data[i+13]=radius1*sin(radians+M_PI/180);
        data[i+14]=0;
        data[i+15]=radius2*cos(radians+M_PI/180);
        data[i+16]=radius2*sin(radians+M_PI/180);
        data[i+17]=height;
        radians+=(M_PI)/180;
    }
}
void create_circle(GLfloat *data,float radius){
        float radians=0;
         for(int i=0;i<360*9;i+=9){
          data[i]=radius*cos(radians+M_PI/180);
        data[i+1]=radius*sin(radians+M_PI/180);
        data[i+2]=0;
        data[i+3]=radius*cos(radians);
        data[i+4]=radius*sin(radians);
        data[i+5]=0;
         data[i+6]=0;
        data[i+7]=0;
        data[i+8]=0;
        radians+=(M_PI)/180;
    }
}
void create_sphere(GLfloat *data,float Radius){
    int Stacks=10;
    int Slices=10;
    vector<glm::vec3> vertices;
    for (int i = 0; i <= Stacks; ++i){

    float V   = i / (float) Stacks;
    float phi = V * glm::pi <float> ();

    // Loop Through Slices
    for (int j = 0; j <= Slices; ++j){

        float U = j / (float) Slices;
        float theta = U * (glm::pi <float> () * 2);

        // Calc The Vertex Positions
        float x = cosf (theta) * sinf (phi);
        float y = cosf (phi);
        float z = sinf (theta) * sinf (phi);

        // Push Back Vertex Data
        vertices.push_back (glm::vec3(x*Radius,y*Radius,z*Radius));

    }

}
vector<int> indices;
for (int i = 0; i < Slices * Stacks + Slices; ++i){

    indices.push_back (i);
    indices.push_back (i + Slices + 1);
    indices.push_back (i + Slices);

    indices.push_back (i + Slices + 1);
    indices.push_back (i);
    indices.push_back (i + 1);
}
int j=0;
for(int i=0;i<indices.size();i++){
    int k=indices[i];
    data[j++]=vertices[k].x;
    data[j++]=vertices[k].y;
    data[j++]=vertices[k].z;
}   
}
void cursor_position_callback(GLFWwindow *window, double x, double  y) {
    
        if(cam%5!=4)return;
            // Calculate the new phi and theta based on mouse position relative to where the user clicked
            float dPhi = ((float)(mouselasty - y) / 600);
            float dTheta = ((float)(mouselastx - x) / 600); 
            m_camera.Rotate(-dTheta, dPhi);
            mouselastx=x;
            mouselasty=y;
}
void Cuboid(GLfloat *data,float length, float breadth, float height) {
    length = length;
    breadth = breadth;
    height = height;
    GLfloat vertex_buffer_data[] = {
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2, // triangle 1 : begin
        -1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2, // triangle 1 : end
        1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2, // triangle 2 : begin
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2, // triangle 2 : end
        1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2,-1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        -1.0f*length/2, 1.0f*height/2, 1.0f*breadth/2,
        1.0f*length/2,-1.0f*height/2, 1.0f*breadth/2
    };
    for(int i=0;i<108;i++){
        data[i]=vertex_buffer_data[i];
    }
}
void check_volcano(){
    float x1=ball1.position.x;
    float z1=ball1.position.z;
    float h2=ball1.position.y;
    for(int i=0;i<map_volcano.size();i++){        
    float x=map_volcano[i].position.x;
    float h1=map_volcano[i].h;
    float z=map_volcano[i].position.z;
    float r=map_volcano[i].r1;
        if(volcano_collision(x,z,h1,r,x1,z1,h2,36,ball1.yaw)){
            exit(0);
        }
    }
}
bool volcano_collision(float x,float z,float h1,float r,float x1,float z1,float h2,float l,float yaw){
if(h1+5<h2){
return false;
}
x1+=(l*cos(yaw*M_PI/180)/2);    
z1+=(l*sin(yaw*M_PI/180)/2);
if((x1-x)*(x1-x)+(z1-z)*(z1-z)<(r+5)*(r+5)){
return true;
}
x1-=(l*cos(yaw*M_PI/180));
z1-=(l*sin(yaw*M_PI/180));
if((x1-x)*(x1-x)+(z1-z)*(z1-z)<(r+5)*(r+5)){
return true;
}
return false;
}

bool sphere_coll(glm::vec3 P,glm::vec3 P1,float r){
    float dist=glm::distance(P,P1);
    if(dist<r)return true;
    return false;
}
void bullets_aero(){
    for(int i=0;i<cannon_bullets.size();i++){
        if(sphere_coll(cannon_bullets[i].position,ball1.position,cannon_bullets[i].r+50))exit(0);
    }
}
void missiles_enem(){
    for(int i=0;i<missiles.size();i++){
        glm::vec3 P1=missiles[i].position;
        float r1=10;
        for(int j=0;j<ene.size();j++){
              glm::vec3 P2=ene[j].position;
              float r2=142  ;
              if(sphere_coll(P1,P2,r1+r2)){
                  ene.erase(ene.begin()+j);
                  missiles.erase(missiles.begin()+i);
                  score+=10;
                  j--;
                  i--;
              }
        }
        if(missiles[i].time<0){
            missiles.erase(missiles.begin()+i);
            i--;
        }

    }
}
void draw_aim(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::vec3 position=ball1.position+1000.0f*ball1.roll_axis;
    glm::mat4 translate = glm::translate (position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(aim);
}
void draw_arrow(glm::mat4 VP){
    glm::vec3 P1=ball1.position+20.0f*ball1.roll_axis+20.0f * glm::vec3(0,1,0);
    glm::vec3 P2=P1;
    if(ene.size()!=0){
        P2=ene[0].position;
    }
    else return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate =glm::translate (P1);
    glm::mat4 rotate1   = glm::rotate((float) (acos(dot(normalize(glm::vec3(0,0,1)),normalize(P2-P1)))), cross(glm::vec3(0,0,1),normalize(P2-P1)));
    Matrices.model *= (translate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(show_direction);
}
void init_arrow(){
    float l=5;
    float b=5;
    float h=2;
    vector <glm::vec3> vertices;
    vertices.push_back(glm::vec3(0,0,0));
    vertices.push_back(glm::vec3(0,0,l));
    vertices.push_back(glm::vec3(-b,0,-l));
    vertices.push_back(glm::vec3(b,0,-l));
    vertices.push_back(glm::vec3(0,-h,0));
    vertices.push_back(glm::vec3(0,-h,l));
    vertices.push_back(glm::vec3(-b,-h,-l));
    vertices.push_back(glm::vec3(b,-h,-l));
    int indices[]={0,1,2,0,1,3,4,5,6,4,5,7,2,0,6,4,0,6,0,3,4,3,4,7,1,5,3,3,5,7,1,5,6,1,2,6};
    int j=0;
        GLfloat data[5000];
    for(int i=0;i<sizeof(indices)/sizeof(indices[0]);i++){
    int k=indices[i];
    data[j++]=vertices[k].x;
    data[j++]=vertices[k].y;
    data[j++]=vertices[k].z;
}   

    show_direction = create3DObject(GL_TRIANGLES, j/3, data, {50,205,50}, GL_FILL);

}
void Print_speed(glm::mat4 VP){
     Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(10,30,0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    float l=1,b=0.1;
     GLfloat data[]={
         0,0,0,
         l,0,0,
         0,b,0,
        l,0,0,
         0,b,0,
        l,b,0
    };
    glm::mat4 temp= Matrices.model;
    VAO * object = create3DObject(GL_TRIANGLES,6,data, {124,252,0}, GL_FILL);
    VAO *object2= create3DObject(GL_TRIANGLES,6,data, {255,69,0}, GL_FILL);
   for(int i=1;i<int(ball1.v);i+=1)
   {
    translate=glm::translate (glm::vec3(0,2*b,0));
     Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);
   }
   Matrices.model=temp*glm::translate (glm::vec3(-4,0,0));
    for(int i=1;i<int(ball1.fuel);i+=100)
   {
    translate=glm::translate (glm::vec3(0,2*b,0));
     Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object2);
   }
}
void Print_direction(glm::mat4 VP){
     Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(10,23,0));
        glm::mat4 rotate    = glm::rotate((float) (ball1.yaw * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      float l=3,b=1;
     GLfloat data[]={
         -b/2,0,0,
         +b/2,0,0,
         0,l,0
    };   
      GLfloat data2[]={
         -b/2,0,0,
         +b/2,0,0,
         0,-l,0
    };   
    VAO * object = create3DObject(GL_TRIANGLES,3,data, {255,0,0}, GL_FILL);
    VAO * object2 = create3DObject(GL_TRIANGLES,3,data2, {0,0,255}, GL_FILL);
    draw3DObject(object);
        draw3DObject(object2);

}
void Print_screen(){
      int windowheight,windowwidth;
    glfwGetWindowSize( window,&windowwidth, &windowheight );
     float top    = screen_center_y + (4.0*windowheight/windowwidth) / screen_zoom;
    float bottom = screen_center_y - (4.0*windowheight/windowwidth)/ screen_zoom;
    float left   = screen_center_x - (4.0) / screen_zoom;
    float right  = screen_center_x + (4.0) / screen_zoom;
    glm::mat4   view = glm::lookAt(glm::vec3(40,40, 3), glm::vec3(40,40, 0), glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    glm::mat4 VP = projection * view;
    float xx=10;
    float yy=60;
    int temp_score=score;
    for(int i=0;i<4;i++){
        Score temp=Score(xx,yy);
        temp.draw(VP,temp_score%10);
        temp_score/=10;
        xx-=2.4;
}
 xx=25;
 yy=60;
  temp_score=ball1.position.y;
    for(int i=0;i<4;i++){
        Score temp=Score(xx,yy);
        temp.draw(VP,temp_score%10);
        temp_score/=10;
        xx-=2.4;
}

Print_speed(VP);
Print_direction(VP);
refuel();
}
void refuel(){
    glm::vec3 P=ball1.position;
    glm::vec3 P1=rings.position;
    glm::vec3 P2=glm::vec3(P.x,P1.y,P.z);
    if(abs(P.y-P1.y)<90){
        if(rings.r-rings.ring_radius<glm::distance(P2,P1) && glm::distance(P2,P1)< rings.r+rings.ring_radius){
            ball1.fuel+=ball1.v;
            if(ball1.fuel>14000)ball1.fuel=14000;
}
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_camera.Zoom(yoffset);
}