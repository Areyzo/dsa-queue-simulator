#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <raylib.h>
#include <stdbool.h>

#define MAX_VEHICLES 10

typedef struct Direction
{
    bool east;
    bool west;
    bool north;
    bool south;
};

typedef struct Turn
{
    bool none;
    bool left;
    bool right;
};
typedef struct State
{
    bool turning;
    bool moving;
    bool stopping;
};

typedef struct Vechicle
{
    bool priority;
    Rectangle rect;
    Direction direction;
    Turn turn;
    State state;
    int speed;


};
typedef struct TrafficLightState
{   
    bool red;
    bool green; 
};
typedef struct TrafficLight
{
    TrafficLightState trafficlightstate;
    int timer;
    Rectangle position;
    Direction direction;
};
typedef struct Node
{
    Vechicle vehicle;
    struct Node*
};
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

void initializeTrafficLights(TrafficLight* lights);
void updateTrafficLights(TrafficLight* lights);
Vehicle* createVehicle(Direction direction);
void updateVehicle(Vehicle* vehicle, TrafficLight* lights);
void renderSimulation(Vehicle* vehicles, TrafficLight* lights, Statistics* stats);
void renderRoads(void);
void renderQueues(void);

//Queue Function
void initQueue(Queue* q);
void enqueue(Queue* q, Vehicle vehicle);
Vehicle* dequeue(Queue* q);
int isQueueEmpty(Queue* q);
