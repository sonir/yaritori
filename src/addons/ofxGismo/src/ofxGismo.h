
// How to Use from your src
//      GismoManager& gismo = GismoManager::getInstance();
//      cout << gismo.foo << endl;
//      gismo.foo = 139;



#pragma once


// PARAMS SET MACROS
#define AG_MAX 3000
#define SEED_MAX 63
//Agent Default Parameters
#define AG_DEF_SIZE 0.0034f
#define AG_DEF_MOV 0.002f
#define AG_DEF_VIEW 0.2f
#define AG_DEF_SIZE_FIX 0.005f //Scaling factor for frand(0.0-1.0)


///

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "agTypes.h"
#include "Event.hpp"
#include "EventHandler.hpp"


//Function Prototypes
//Inits
void initAgent(ag_t *ags);
void initAgentActive(ag_t *ags);
void initAgents(ag_t *ags);
void initPutBuff(put_buf_t *put_buf);
//AgentOperation
void addAgentToBuff(ag_t ag, put_buf_t put_buf);
void agBuffReset(agent_buf_t *agents);
//InteractionTool
float distance(posi_t p1, posi_t p2);
int seekNearest(int ag_id, agent_buf_t *agbuf);
bool isViewRange(ag_t *ag, float distance);
bool isLarge(float f1, float f2);
void move(ag_t *ag, posi_t *posi);
void randomMove(ag_t *ag);
void interactWith(ag_t *focus , ag_t *target);
void makeInteracts(agent_buf_t *agents);
void positionLoop(posi_t *position);
float logistic(float fval=0.5);
void setSeed(int seed);
float frand();
int irand();
bool brand();


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
        Event *sound;

        //Methods
        void setup();
        ag_t* getAgents();
        void addAgent(ag_t tmp);
        void addSync(); //Sync actual agent array and add_buffer
        //float random();


    
    private:
        GismoManager();
        ~GismoManager() = default;
    
    
    
};


