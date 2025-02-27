#include<raylib.h>
#include"traffic_simulation.hpp"
#include<fstream>
#include<istream>

void initializeTrafficLights(TrafficLight* lights){
    lights->trafficlightstate.green=true;
    if(lights->trafficlightstate.green==true){
        lights->trafficlightstate.red=false;
    }
    lights->timer = 10;//timer idk might be useful in  future
};
void updateTrafficLights(TrafficLight* lights){
    //upade light per need
};
void createVehicle(Vehicle vehile){
    vehile.priority=GetRandomValue(0,1);
    vehile.speed = 10;
    int num = GetRandomValue(1,2,3,4);
    switch (num)
    {
    case 1:
        vehile.direction.east = true;
        vehile.direction.west = false;
        vehile.direction.north = false;
        vehile.direction.south = false;
        break;
    case 2:
        vehile.direction.east = false;
        vehile.direction.west = true;
        vehile.direction.north = false;
        vehile.direction.south = false;
        break;
    case 3:
        vehile.direction.east = false;
        vehile.direction.west = false;
        vehile.direction.north = true;
        vehile.direction.south = false;
        break;
    case 4:
        vehile.direction.east = false;
        vehile.direction.west = false;
        vehile.direction.north = false;
        vehile.direction.south = true;
        break;
    
    default:
        break;
    }
    // random generator for turn
    int turn = GetRandomValue(1,2,3);
    switch (turn)
    {
    case 1:
        vehile.turn.left = true;
        vehile.turn.right = false;
        vehile.turn.none = false;
        break;
    case 2:
        vehile.turn.left = false;
        vehile.turn.right = true;
        vehile.turn.none = false;
        break;
    case 3:
        vehile.turn.left = false;
        vehile.turn.right = false;
        vehile.turn.none = true;
        break;
    
    default:
        break;
    }

};