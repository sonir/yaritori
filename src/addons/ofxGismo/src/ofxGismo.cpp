#include "ofxGismo.h"

using namespace std;

//Imlementations of C Functions

void initAgent(ag_t *tmp){
    
    tmp->active = false;
    tmp->posi.x = frand();
    tmp->posi.y = frand();
    tmp->size = AG_DEF_SIZE;
    tmp->view = 0.05f;
    tmp->mov = 0.05f;

    tmp->condition = CALM;
    
    
}

void initAgentActive(ag_t *tmp){
    
    initAgent(tmp);
    tmp->active = true;
    
}


void initAgents(ag_t *ags){ //Init all agents with default paramas
    
    printf("initAgents\n");
    for (int i=0; i<AG_MAX; i++){
        
        ags++; //Increment the index
        
    }
        
    
}


void initPutBuff(put_buf_t *put_buf){
    
    put_buf->count = 0;
    ag_t *ags = put_buf->buf;
    
    for(int i=0; i<AG_BUF_MAX; i++){
        
        initAgent(ags);
        ags++;
        
    }
    
}



void addAgentToBuff(ag_t ag, put_buf_t *put_buf){ //Put agent to buff
    
    put_buf->buf[put_buf->count] = ag;
    put_buf->count += 1;
    
}


void agBuffReset(agent_buf_t *agents){
    
    for(int i=0; i<agents->count;i++){
        
        agents->buf[i].active = false;
        
    }
    agents->count = 0;
    
}




//Interaction Tool Kits
float distance(posi_t p1, posi_t p2){
    
    posi_t tmp;
    // calc differences
    tmp.x = p2.x - p1.x;
    tmp.y = p2.y = p2.y;
    
    tmp.x = tmp.x*tmp.x;
    tmp.y = tmp.y*tmp.y;
    
    //	pythagoras theorem
    return (float)( sqrt(tmp.x+tmp.y) );
    
    
}


int seekNearest(int ag_id, agent_buf_t *agbuf){
    
    ag_t *forcus = &agbuf->buf[ag_id];
    ag_t *target;
    int nearest_id = -1;
    float nearest_val = 999.0f;
    float val = 0.0f;
    for(int i=0; i<agbuf->count;i++){
        target = &agbuf->buf[i];
        if (target->active == false || ag_id == i){ //Ignore dead or void agent or myself
            
            continue;
            
        }
        val = distance(forcus->posi, target->posi);
        
        if(val < nearest_val){ //If find tmpolary longest
            
            nearest_id = i; //store the id
            nearest_val = val; //update the lon
        }
        
    } // end of for
    
    return nearest_id;
    
    
}


bool isViewRange(ag_t *ag, float distance){
    
    if(ag->view > distance) return true;
    else if (ag->view <= distance) return false;
    
}


void move(ag_t *ag, posi_t *posi){
    
    GismoManager& gismo = GismoManager::getInstance();
    
    //decision X
    if ( isLarge(ag->posi.x, posi->x) ) ag->posi.x = ag->posi.x - (frand()*ag->mov);
    else ag->posi.x = ag->posi.x + ( frand() * ag->mov );
    //decision y
    if ( isLarge(ag->posi.y, posi->y) ) ag->posi.y = ag->posi.y - (frand()*ag->mov);
    else ag->posi.y = ag->posi.y + ( frand() *ag->mov);
    
}


void randomMove(ag_t *ag){

    GismoManager& gismo = GismoManager::getInstance();

    //for X
    float fval = frand();
    //invert sign randomly
    if( fmod(fval, 2.0) == 0.0 )fval *= 1;
    else fval *= -1;
    //Set the next X
    ag->posi.x = ag->posi.x + (ag->mov*fval);

    //for Y
    fval = frand();
    //invert sign randomly
    if( fmod(fval, 2.0) == 0.0 )fval *= 1;
    else fval *= -1;
    //Set the next X
    ag->posi.y = ag->posi.y + (ag->mov*fval);

    
}


void interactWith(ag_t *focus , ag_t *target){
    
    float dist = distance(focus->posi, target->posi);
    if (isViewRange(focus, dist)){
        
        if( isLarge(focus->size, target->size) ){

            move(focus, &target->posi);
            focus->condition=CHASE;
            
        } else {

            posi_t tmp = target->posi; //set invert position for running
            tmp.x = tmp.x*(-1);
            tmp.y = tmp.y*(-1);
            move(focus, &tmp);
            focus->condition=RUN;

        }
        
    }else{

        randomMove(focus);
        focus->condition=CALM;
        
    }
    
    //Loop of World
    positionLoop(&focus->posi); //rest by some of memory bug

}


void makeInteracts(agent_buf_t *agents){

    int nearest = -1;
    
    if (agents->count==1){
        
        randomMove(&agents->buf[0]);
        return; //when an agent only, do randomwalk.
        
    }
    
    for(int i=0; i<agents->count;i++){
                
        nearest = seekNearest(i, agents);
        if(nearest != -1) interactWith(&agents->buf[i], &agents->buf[nearest]);
        
    }
    
}


void positionLoop(posi_t *position){
    
    if(position->x > 1.0f) position->x = 0.0f;
    else if (position->x < 0.0f) position->x = 1.0f;
    
    if(position->y > 1.0f) position->y = 0.0f;
    else if (position->y < 0.0f) position->y = 1.0f;
    
}


float logistic(float fval){
    
    float tmp = 1.0f-fval;
    tmp = (tmp*fval)*3; //3 is constant
    return tmp;
    
}

void setSeed(int seed){
    
    srand(seed);
    
}

float frand(){
    
    return ( ( (float)( rand()%10 ) ) * 0.1 );
    
}



//Definication of GismoManager :::::::::::

GismoManager::GismoManager() //Constructor
{
    setSeed(137);
    initAgents(agents.buf);
    agents.count = 0;
    put_buf_t add;
    initPutBuff(&add);
    
}

void GismoManager::setup(){
    
    cout << "GismoManager setup" <<endl;

}



ag_t* GismoManager::getAgents()
{
    
    return agents.buf;
    
}


void GismoManager::addAgent(ag_t tmp){
    
    addAgentToBuff(tmp, &add);
    
}


void GismoManager::addSync(){
    
    
    for(int i=0; i<add.count;i++){
        
        agents.buf[agents.count]=add.buf[i];
        agents.count++;
        
    }
    add.count = 0; //reset add_buf count
    
}

