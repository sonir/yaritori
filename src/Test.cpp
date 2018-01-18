//
//  Test.cpp
//  yaritori
//
//  Created by sonir on 12/27/17.
//
//

#include "Test.hpp"

Test :: Test(Sound *pSnd){
    
   sound = pSnd;
    
}


void Test :: setup(){
    
    //Making lambda event
    auto f = [&](void* args){
        
        //draw your own process for your event
        int *foo = (int *)args;
        runSubTest(args); //you can invoke other function in your event
        
    };
    gismo.lambdaAdd("/lambdaTest", f);

    
}

void Test :: runSubTest(void* args){
    
    param_u *params = (param_u *)args;
    arg1 = params[0].ival;
    arg2 = params[1].ival;
    cout << "---" << endl;
    cout << "EVENT /lambdaTest arg1=" << arg1 << endl;
    cout << "EVENT /lambdaTest arg2=" << arg2 << endl;
    cout << "---" << endl;
    
    
    
}


void Test :: run(){
    
    
    //Test frand
//    assert( frand()==0.1f );
//    assert( frand()==0.7f );
//    assert( frand()==0.7f );
//    assert( frand()==0.1f );
//    cout << "gismoManager::randmom() is OK."<<endl;
//    
    
    //Test Sound Trigger with OSC
    for(int i=0; i<AUDIO_BANK_MAX;i++){
        
        sound->set(i);
        
    }
    sound->update(); //test don't send when the event buffer was vacant.
    cout << "CLASS Sound is ok.(check the receive yourself.)" << endl;

    
    //TestEventHandler
    EventHandler eventHandler;
    EvTest evTest;
    eventHandler.eventAdd("/snd" , sound);
    eventHandler.eventAdd("/t01" , &evTest);
    int args[] = {0,1,2};
    assert ( eventHandler.bang("/t01", args) == 138 );
    assert ( eventHandler.bang("/t01") == 137 );
    cout << "GismoBundledClass::eventHandler is OK." << endl;
    //Test EventHandler with Gismo
    gismo.eventAdd("/t01" , &evTest);
    assert ( gismo.bang("/t01" , args) == 138 );
    //Sound Trigger
    sound->reset();
    gismo.eventAdd("/snd" , sound);
    int snd_id = 0;
    setSound(0);
    setSound(2);
    setSound(4);
    sound->update();
    cout << "GismoManager::eventHandler with Gismo is OK." << endl;
    
    
    
    //Define an agent
    ag_t ag;
    
    //Test GismoManager.getAgents()
    ag_t *agents = gismo.getAgents();
    agents[0].posi.x = 0.13f;
    agents[0].posi.y = 0.2f;
    assert(agents[0].posi.x == 0.13f);
    assert(agents[0].posi.y == 0.2f);
    cout << "GismoManager:getAgent() is OK." << endl;
    
    //Test GismoLibrary distance()
    posi_t tmp1, tmp2;
    tmp1.x = 0.0f;
    tmp1.y = 0.0f;
    tmp2.x = 3.0f;
    tmp2.y = 4.0f;
    assert(distance(tmp1, tmp2) == 5.0f);
    tmp1.x = 0.5f;
    tmp1.y = 0.5f;
    tmp2.x = -0.5f;
    tmp2.y = -0.5f;
    assert(distance(tmp1, tmp2)==(float)sqrt(2.0f));
    tmp1.x = 3.0f;
    tmp1.y = 4.0f;
    tmp2.x = 0.0f;
    tmp2.y = 0.0f;
    assert(distance(tmp1, tmp2) == 5.0f);
    tmp1.x = 5.0f;
    tmp1.y = 12.0f;
    tmp2.x = 0.0f;
    tmp2.y = 0.0f;
    assert(distance(tmp1, tmp2) == 13.0f);
    cout << "GismoLibrary:distance() is OK." << endl;
    
    
    //Test Init AgentActive
    initAgentActive(&ag);
    assert(ag.size == AG_DEF_SIZE);
    assert(ag.active==true);
    cout << "GismoLibrary:initAgentActive() is OK." << endl;
    
    //TestAgentAdd
    initAgentActive(&ag);
    ag.view = 0.23f;
    ag.posi.x = 0.2f; ag.posi.y=0.2f;
    gismo.addAgent(ag);
    assert (gismo.add.buf[0].view == 0.23f);
    assert (gismo.add.count == 1);
    cout << "GismoManager:addAgent() is OK." << endl;
    
    //TestSync
    ag_t ag2;
    initAgentActive(&ag2);
    ag2.view = 0.34f;
    gismo.addAgent(ag2);
    gismo.addSync(); //Finally gismo requires sync to avoid direct agent addition when processing agents.
    assert(gismo.add.count==0 && gismo.agents.count==2);
    assert(agents[0].active && agents[1].active);
    assert(agents[0].view==0.23f && agents[1].view==0.34f);
    cout << "gismoLibrary:addSync() is OK." << endl;
    
    //Test gismo Library seekNearest();
    agents[0].posi.x = 0.0f;
    agents[0].posi.y = 0.0f;
    agents[1].posi.x = 0.5f;
    agents[1].posi.y = 0.5f;
    ag_t ag3;
    initAgentActive(&ag3);
    ag3.posi.x = 0.5f;
    ag3.posi.y = 0.49f;
    gismo.addAgent(ag3); //add the new agent to addBuffer
    ag_t ag4;
    ag4.posi.x = 0.7f;
    ag4.posi.y = 0.49f;
    gismo.addAgent(ag3); //add the new agent to addBuffer
    gismo.addSync(); //refrect the add buffer to actual buffer
    int nearest_agent = seekNearest(0, &gismo.agents); //seek the nearest agent of agent[0]
    cout << nearest_agent << endl;
    assert(nearest_agent==2);
    cout << "gismoManager:seekNearest() is OK."<<endl;
    
    
    //Test isViewRange
    ag_t ag5;
    ag5.view = 0.5f;
    assert( isViewRange(&ag5,0.3f)==true );
    assert( isViewRange(&ag5,0.51f)==false );
    cout << "gismoLibrary::isViewRange() is OK" << endl;
    
    //Test isLarge
    assert( isLarge(0.5 , 0.4)==true );
    assert( isLarge(0.5, 0.501)==false);
    cout << "gismoLibrary::isaLarge is OK" <<endl;
    
    //Test Move
    ag_t ag6;
    posi_t tmp;
    tmp.x=1.0; tmp.y=0.0;
    initAgent(&ag6);
    ag6.posi.x=0.5; ag6.posi.y=0.5;
    move(&ag6,&tmp);
    assert(ag6.posi.x >= 0.5f);
    assert(ag6.posi.y <= 0.5f);
    cout << "gismoLibrary::move() is OK." << endl;
    
    //Test Run
    ag_t tmpAg1, tmpAg2;
    tmpAg1.posi.x = 0.75f;
    tmpAg1.posi.y = 0.75f;
    tmpAg1.mov = 0.001f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    tmpAg2.posi.x = 0.5f;
    tmpAg2.posi.y = 0.5f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x >= 0.75f);
    assert(tmpAg1.posi.y >= 0.75f);
    tmpAg1.posi.x = 0.25f;
    tmpAg1.posi.y = 0.75f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x <= 0.25f);
    assert(tmpAg1.posi.y >= 0.75f);
    tmpAg1.posi.x = 0.75f;
    tmpAg1.posi.y = 0.45f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x >= 0.75f);
    assert(tmpAg1.posi.y <= 0.45f);
    tmpAg1.posi.x = 0.25f;
    tmpAg1.posi.y = 0.25f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;    
    running(&tmpAg1, &tmpAg2.posi);
    //0115 assert(tmpAg1.posi.x < 0.25f);
    assert(tmpAg1.posi.y < 0.25f);
    cout << "gismoLibrary::running() is OK." << endl;
    
    //TestConditionCheck
    condition_e cond1 = CALM;
    condition_e cond2 = RUN;
    assert ( conditionCheck(cond1, cond2) == false );
    cond2 = CALM;
    assert ( conditionCheck(cond1, cond2) == true );
    
    //Test interactWith()
    ag_t ag8 , ag9;
    initAgent(&ag8);
    initAgent(&ag9);
    ag8.size = 1.0f;
    ag8.posi.x = 0.0f; ag8.posi.y = 0.0f;
    ag9.posi.x = 1.0f; ag9.posi.y = 1.0f;
    ag8.view = 1.5;
    interactWith(&ag8 , &ag9);
    
    
    //TestReset
    agents[0].active=true;
    agents[1].active=true;
    agBuffReset(&gismo.agents);
    assert(agents[0].active==false);
    assert(agents[1].active==false);
    assert(gismo.agents.count == 0);
    
    
    //TestLogistic
    float fval=0.5;
    fval = logistic(fval);
    assert(fval==0.75f);
    fval = logistic(fval);
    cout << "GismoLibrary::logistic() is OK." << endl;        

    //Test
    agBuffReset(&gismo.agents);
    ag_t ag1;
    initAgent(&ag1);
    ag1.view = 256.0f;
    gismo.agents.buf[0] = ag1;
    ag1.view = 356.0f;
    gismo.agents.buf[1] = ag1;
    ag_t *pAg1 = gismo.getAgent(0);
    assert(pAg1->view == 256.0f);
    ag_t *pAg2 = gismo.getAgent(1);
    assert(pAg2->view == 356.0f);
    
    //TestSpeedLimit
    assert ( limitter(1.1f, 1.0f) == 1.0f );
    assert ( limitter(-1.1f, 1.0f) == -1.0f );
    assert ( limitter(0.49f, 0.5f) == 0.49f );
    assert ( limitter(-0.49f, 0.5f) == -0.49f );
    assert ( limitter(0.0051f, 0.005f) == 0.005f );
    assert ( limitter(-0.00501f, 0.005f) == -0.005f );

    cout << "speedLimitter is OK." << endl;
    
    
    //Test positionLoop()
    posi_t pos;
    pos.x = 1.1; pos.y = -0.01;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 0.0f);
    assert (pos.y == 1.0f);
    pos.x = -0.1; pos.y = 1.4;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 1.0f);
    assert (pos.y == 0.0f);
    pos.x = 0.0f; pos.y = 1.0f;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 1.0f);
    assert (pos.y == 1.0f);
    //Check result check
    pos.x = 0.5f;
    pos.y = 0.5f;
    bool result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==false);
    pos.x = 1.0f;
    pos.y = 1.0f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==false);
    pos.x = 1.05f;
    pos.y = 1.05f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==true);
    pos.x = 1.05f;
    pos.y = 1.00f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==true);
    cout << "GismoLibrary::positionLoop() is OK" << endl;
    
    
    //Test attackCheck
    float fval2 = 0.0f;
    float size2 = 1.0f;
    attackCheck(fval2, &size2);
    bool size_test2 = true;
    if ( size2 != (1.0f-AG_DMG) ) size_test2 = false;
    assert(size_test2);
    assert(size2 == 1.0f-AG_DMG);
    size2 = 1.0f;
    fval2 = ATK_DIST+0.1;
    attackCheck(fval2, &size2);
    assert(size2 == 1.0f);
    cout << "GismoLibrary::attackCheck() is OK" << endl;

    size2 = 1.0f;
    fval2 = ATK_DIST;
    attackCheck(fval2, &size2);
    assert(size2 == 1.0f-AG_DMG);
    
    //Test deadCheck
    float dummy_size = 0.0001f;
    bool active = true;
    deadCheck( &dummy_size , &active );
    assert(active == false);
    assert(dummy_size == 0.0f);
    dummy_size = 1.0f;
    active = true;
    deadCheck( &dummy_size , &active );
    assert(active == true);
    cout << "GismoLibrary::deadCheck is OK" << endl;
    
    //Test Shape2Agent
    ag_shape_t shape;
    shape.nodes[0].x = 0.5f;
    shape.nodes[0].y = 0.5f;
    shape.nodes[1].x = 1.0f;
    shape.nodes[1].y = 1.0f;
    shape.node_count = 2;
    shape.edges[0].node_id_a = 0;
    shape.edges[0].node_id_b = 1;
    shape.edge_count = 1;
    ag_t tmpAg = shape2Agent(shape);
    assert(tmpAg.view == 0.005f);
    assert(tmpAg.size == 0.011f);
    assert(tmpAg.mov == 0.35f);
    cout << "Shape2Agent.hpp::shape2Agent() is OK" << endl;
    
    //Test moveOnLine()
    posi_t posi = moveOnLine(0.5f, 0.0f, 0.0f, 1.0f, 1.0f);
    assert(posi.x == 0.5f && posi.y == 0.5f);
    posi = moveOnLine(1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    assert(posi.x == 1.0f && posi.y == 1.0f);
    posi = moveOnLine(0.5f, -1.0f, -1.0f, -2.0f, -2.0f);
    assert(posi.x == -1.5f && posi.y == -1.5f);
    posi = moveOnLine(0.0f, -1.0f, -1.0f, -2.0f, -2.0f);
    assert(posi.x == -1.0f && posi.y == -1.0f);
    posi = moveOnLine(0.5f, 0.0f, 0.0f, -1.0f, -2.0f);
    assert(posi.x == -0.5f && posi.y == -1.0f);

    //TestGetArraySize
    int iArray[137];
    posi_t posiArray[138];
    assert(getArraySize(iArray)==137);
    assert(getArraySize(posiArray)==138);
    cout << "TestGetArraySize.h::getArraySize() is ok." << endl;
    
    //Test lambda bang
    int myArg[2];
    myArg[0] = 12;
    myArg[1] = 13;
//    gismo.lambdaBang("/lambdaTest", myArg);
    gismo.bang("/lambdaTest", myArg);

    
}

void Test :: update(){

    

    
//    float fval = fade.update();
//    cout << "fval=" << fval << endl;
//    if(fval>0.5f) fade.reset();
//    fade.bang();
        
}
