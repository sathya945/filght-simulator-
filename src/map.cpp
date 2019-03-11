#include "map.h"
#include "main.h"
#include "volcano.h"
#include "enemies.h"
#include <vector>

using namespace std;

void init_volcano(vector <volcano>  &map_volcano){

        map_volcano.push_back(volcano(-100,0,0,100));
        for(int i=0;i<30;i++){
            map_volcano.push_back(volcano(-10000+rand()%20000,0,-10000+rand()%20000,50+rand()%600));
        }
}

void init_cannon(vector<cannon> &ene){
    for(int i=0;i<5;i++)
            ene.push_back(cannon(glm::vec3(rand()%20000-10000,200,rand()%20000-10000),5*(rand()%3)));
}

