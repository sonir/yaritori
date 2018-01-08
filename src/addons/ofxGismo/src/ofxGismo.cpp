#include "ofxGismo.h"

using namespace std;

//Imlementations of C Functions

void initAgent(ag_t *tmp){
    
    tmp->active = false;
    tmp->posi.x = frand();
    tmp->posi.y = frand();
    tmp->size = AG_DEF_SIZE;
    tmp->view = AG_DEF_VIEW;
    tmp->mov = AG_DEF_MOV;

    tmp->spd.x = 0.0f;
    tmp->spd.y = 0.0f;
    
    tmp->condition = CALM;
    tmp->interact_with = DEFAULT_INTERACT_WITH;
    
    
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
    
    posi_t tmp1, tmp2;
    // calc differences
    tmp1.x = p2.x - p1.x;
    tmp1.y = p2.y - p1.y;
    
    tmp2.x = tmp1.x*tmp1.x;
    tmp2.y = tmp1.y*tmp1.y;
    
    //	pythagoras theorem
    return (float)( sqrt(tmp2.x+tmp2.y) );
    
    
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


bool isLarge(float f1, float f2){
    
    if (f1>f2)return true;
    else if (f1<f2) return false;
    else if (f1==f2){
     
        if( brand() ) return true;
        else return false;
        
    }
    
}



void move(ag_t *ag, posi_t *posi){

    //decision X
    float x_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.x, posi->x) ) ag->spd.x -= x_move; //WHEN LARGE change xspd to negative
    else ag->spd.x += x_move; //WHEN SMALL change xspd to negative
    
    ag->spd.x = limitter(ag->spd.x, SPD_LIMIT); //LimitCheck
    ag->posi.x += ag->spd.x; //Move with the refleshed sppd

    //decision X
    float y_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.y, posi->y) ) ag->spd.y -= y_move; //WHEN LARGE change xspd to negative
    else ag->spd.y += y_move; //WHEN SMALL change xspd to negative
    
    ag->spd.y = limitter(ag->spd.y, SPD_LIMIT); //LimitCheck
    ag->posi.y += ag->spd.y; //Move with the refleshed sppd

    
    cout << ag->spd.x << " , " << ag->spd.y << endl;
    
}



void randomMove(ag_t *ag){

    GismoManager& gismo = GismoManager::getInstance();

    //for X
    //invert sign randomly
    float fval=1.0f;
    if( irand()<50 )fval *= 1;
    else fval *= -1;
    //Set the next X
    ag->posi.x = ag->posi.x + (ag->mov*fval);

    //for Y
    //invert sign randomly
    if( irand()<50 )fval *= 1;
    else fval *= -1;
    //Set the next X
    ag->posi.y = ag->posi.y + (ag->mov*fval);

    
}


float limitter(float val, float limit){
    
    //get abs
    float abs;
    if (val < 0) abs= val * (-1);
    else abs = val;
    
    printf("abs :: %f\n", abs);
    
    if ( abs<limit ){
        return val;
        
    }else{
        
        if ( val < 0 ) return ( limit * (-1) ); //val was negative, return negative abs
        else return limit; // val was positive, return positive abs
        
    }
    
}



bool conditionCheck(condition_e cond1, condition_e cond2){
    
    if (cond1==cond2) return true;
    else return false;
    
    
}



void attackCheck(float distance, float *f_param){
    
    if(distance <= ATK_DIST) *f_param -= AG_DMG;
    
}


void deadCheck(float *size, bool *active){
    
    if(*size < DEAD_THREATH ){
        
        *size = 0.0f;
        *active = false;
        
    }
    
}


void interactWith(ag_t *focus , ag_t *target){

    
    float dist = distance(focus->posi, target->posi);
    if (isViewRange(focus, dist)){
        
        if( isLarge(focus->size, target->size) ){

            move(focus, &target->posi);
            attackCheck( distance(focus->posi, target->posi) , &target->size);
            deadCheck(&target->size, &target->active);
            
            if( !conditionCheck(focus->condition, CHASE) ){
                
                //WORK137
                setSound( (int)focus->condition );
                focus->condition=CHASE;
            }
            
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
    //positionLoop(&focus->posi, gismo.width_rate, gismo.height_rate); //rest by some of memory bug

}


void makeInteracts(agent_buf_t *agents){

    
    //Get singleton to get width rate
    GismoManager& gismo = GismoManager::getInstance();

    
    int nearest = -1;
    
    if (agents->count==1){
        
        randomMove(&agents->buf[0]);
        return; //when an agent only, do randomwalk.
        
    }
    
    for(int i=0; i<agents->count;i++){
                
        nearest = seekNearest(i, agents);
        if(nearest != -1)
        {
            //Interact
            interactWith(&agents->buf[i], &agents->buf[nearest]);
            //Loop of World
            positionLoop(&agents->buf[i].posi, gismo.width_rate, gismo.height_rate);
            //Set who is interacted agent
            if(agents->buf[i].condition != CALM) agents->buf[i].interact_with = nearest;
            else agents->buf[i].interact_with = DEFAULT_INTERACT_WITH;
        
        }
        
    }
    
    
    
}


void positionLoop(posi_t *position, float w_max, float h_max){
    
    if(position->x > w_max) position->x = 0.0f;
    else if (position->x <= 0.0f) position->x = w_max;
    
    if(position->y > h_max) position->y = 0.0f;
    else if (position->y <= 0.0f) position->y = h_max;
    
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

int irand(){
    
    return ( ( rand()%100 ) );
    
}

bool brand(){
    
    if (rand()%2==0)return true;
    else return false;
    
}

int setSound(int sound_id){
    
    //Get singleton
    GismoManager& gismo = GismoManager::getInstance();
    gismo.bang("/snd" , &sound_id);

    return sound_id;

    
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

ag_t* GismoManager::getAgent(int aid)
{
    
    return &agents.buf[aid];
    
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

