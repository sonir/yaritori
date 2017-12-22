
// How to Use from your src
//      GismoManager& gismo = GismoManager::getInstance();
//      cout << gismo.foo << endl;
//      gismo.foo = 139;



#pragma once


// PARAMS SET MACROS
#define AG_MAX 3000
#define SEED_MAX 63

#define AG_DEF_SIZE 0.002f


///

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "agTypes.h"
#include "Event.hpp"
#include "EventHandler.hpp"


//Function Prototypes
//Inits
float initAgent(ag_t *ags, float fval=0.5);
float initAgentActive(ag_t *ags, float fval=0.5);
void initAgents(ag_t *ags);
void initPutBuff(put_buf_t *put_buf);
//AgentOperation
void addAgentToBuff(ag_t ag, put_buf_t put_buf);
void agBuffReset(agent_buf_t *agents);
//InteractionTool
float distance(posi_t p1, posi_t p2);
int seekNearest(int ag_id, agent_buf_t *agbuf);
bool isViewRange(ag_t *ag, float distance);
bool isLarge(float f1, float f2){
    
    if (f1>f2)return true;
    else return false;
    
}
void move(ag_t *ag, posi_t *posi);
void randomMove(ag_t *ag);
void interactWith(ag_t *focus , ag_t *target);
void makeInteracts(agent_buf_t *agents);
void positionLoop(posi_t *position);
float logistic(float fval=0.5);
void setSeed(int seed);
float frandom();



//Class for Data management

class GismoManager : public EventHandler {
    
    public:
        //Kill methods related with duplication of instance
        GismoManager(const GismoManager&) = delete;
        GismoManager& operator=(const GismoManager&) = delete;
        GismoManager(GismoManager&&) = delete;
        GismoManager& operator=(GismoManager&&) = delete;
    
        static GismoManager& getInstance(){
            static GismoManager instance; //Invoke privated constructor
            return instance;
        }
    
        const char* getString(){
            return "Hello world!";		//to invoke, write " Singleton::getInstance().getString(); " 
        }
    
        //Variables
        agent_buf_t agents;
        put_buf_t add;
        int random_count = 0;
        float seed[SEED_MAX] = {0.3000,0.5000,0.5000,0.4000,0.3000,0.2000,0.1000,0.8000,0.6000,0.9000,0.7000,0.4000,0.8000,0.3000,0.7000,0.5000,0.9000,0.2000,0.1000,0.6000,0.8000,0.1000,0.3000,0.6000,0.9000,0.2000,0.7000,0.4000,0.5000,0.5000,0.6000,0.4000,0.2000,0.7000,0.3000,0.1000,0.8000,0.9000,0.8000,0.2000,0.3000,0.7000,0.4000,0.6000,0.5000,0.9000,0.1000,0.1000,0.8000,0.3000,0.7000,0.2000,0.9000,0.4000,0.5000,0.6000,0.5000,0.3000,0.7000,0.8000,0.1000,0.2000,0.4000};
        Event *sound;

        //Methods
        void setup(Event *pSound);
        ag_t* getAgents();
        void addAgent(ag_t tmp);
        void addSync(); //Sync actual agent array and add_buffer
        float random();


    
    private:
        GismoManager();
        ~GismoManager() = default;
    
    
    
};


