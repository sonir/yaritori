//
//  VSyn.cpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#include "VSyn.hpp"

using namespace std;

void VSyn::setup(){
    
    ofBackground(0, 0, 0);
    ofSetCircleResolution(50);
    screen_w = ofGetWidth();
    screen_h = ofGetHeight();

    //CAM SETUP
    cam_flg = false;
    pov.set(POV_INIT_X*ofGetWidth()*(-1), POV_INIT_Y*ofGetHeight(), POV_INIT_Z*ofGetWidth());
    look.set(LOOK_INIT_X*ofGetWidth()*(-1), LOOK_INIT_Y*ofGetHeight(), LOOK_INIT_Z*ofGetWidth());
    //Setup Particles
    particle.setup(ofGetWidth(),ofGetHeight());
    
    
    cout << "VSyn SETUP" << endl;
    receiver.setup(PORT);    
    current_msg_string = 0;
    
    //Init Buffers for Graphics
    initColors(CONTAINER_MAX);
    initShapes(CONTAINER_MAX);
    
    //Setup Gismo
    gismo.setup();
    //Do Test Code
    this->test();

}


void VSyn::update(){
    
    sync();

    gismo.addSync();
    makeInteracts(&gismo.agents);

    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/circle"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            int fill = m.getArgAsInt32(4);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toCircle(&shapes[uid] ,uid, x, y, size, fill);
            }
        } else if(m.getAddress() == "/triangle"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            float angle = m.getArgAsFloat(4);
            int fill = m.getArgAsInt32(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toTriangle(&shapes[uid] ,uid, x, y, size, angle, fill);
            }
        } else if(m.getAddress() == "/square"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            float angle = m.getArgAsFloat(4);
            int fill = m.getArgAsInt32(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toSquare(&shapes[uid] ,uid, x, y, size, angle, fill);
            }
        } else if(m.getAddress() == "/rect"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float angle = m.getArgAsFloat(5);
            int fill = m.getArgAsInt32(6);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toRect(&shapes[uid] ,uid, x1, y1, x2, y2, angle, fill);
            }
        } else if(m.getAddress() == "/line"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float thick = m.getArgAsFloat(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toLine(&shapes[uid] ,uid, x1, y1, x2, y2, thick);
            }
        } else if(m.getAddress() == "/arc"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float height = m.getArgAsFloat(5);
            float expose = m.getArgAsFloat(6);
            float thick = m.getArgAsFloat(7);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toArc(&shapes[uid] ,uid, x1, y1, x2, y2, height, expose, thick);
            }
        } else if(m.getAddress() == "/wave"){
            
            int uid =  m.getArgAsInt32(0);
            
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float freq = m.getArgAsFloat(5);
            float amp = m.getArgAsFloat(6);
            float phase = m.getArgAsFloat(7);
            float thick = m.getArgAsFloat(8);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toWave(&shapes[uid] ,uid, x1, y1, x2, y2, freq, amp, phase, thick);
            }
            
        } else if(m.getAddress() == "/color"){
            
            int uid = m.getArgAsInt32(0);
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                colors[uid].r = (char) ( 255.0f * m.getArgAsFloat(1) );
                colors[uid].g = (char) ( 255.0f * m.getArgAsFloat(2) );
                colors[uid].b = (char) ( 255.0f * m.getArgAsFloat(3) );
                colors[uid].a = (char) ( 255.0f * m.getArgAsFloat(4) );
                
            }

        } else if(m.getAddress() == "/mute"){
            
            int uid =  m.getArgAsInt32(0);
            bool flg = (bool)m.getArgAsInt32(1);

            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toMute(&shapes[uid], flg);
            }
            
        } else if(m.getAddress() == "/cam/pov"){
            
            pov.x =  ( m.getArgAsFloat(0) * ofGetWidth() * (-1)); //Invert x posi for GL coordinate sys
            pov.y =  ( m.getArgAsFloat(1) * ofGetWidth() );
            pov.z =  ( m.getArgAsFloat(2) * ofGetWidth() );
            
        } else if(m.getAddress() == "/cam/look"){
            
            look.x =  ( m.getArgAsFloat(0) * ofGetWidth()  * (-1) ); //Invert x posi for GL coordinate sys
            look.y =  ( m.getArgAsFloat(1) * ofGetWidth() );
            look.z =  ( m.getArgAsFloat(2) * ofGetWidth() );
            
        } else if(m.getAddress() == "/cam/on"){
            
            if ( m.getArgAsInt(0) == 1 )
                cam_flg = true;
            else if(m.getArgAsInt(0) == 0)
                cam_flg = false;
            
        }else if(m.getAddress() == "/particle/attractor/x"){
            
            particle.attractor_x = m.getArgAsFloat(0) * ofGetWidth();
            
        }else if(m.getAddress() == "/particle/attractor/y"){
            
            particle.attractor_y = m.getArgAsFloat(0) * ofGetHeight();
            
        }else if(m.getAddress() == "/particle/modulation"){
            
            particle.modulation = m.getArgAsFloat(0);
            
        }else if(m.getAddress() == "/particle/size"){
            
            particle.size = m.getArgAsFloat(0) * 2.5;
            
        }else if(m.getAddress() == "/particle/num"){
            
            particle.particleNum = m.getArgAsInt(0);
            
        }else if(m.getAddress() == "/particle/mode"){
            
            //particle.mode = m.getArgAsInt(0);
            int flg =  m.getArgAsInt(0);
            switch (flg){
                    
                case 0:
                    particle.mode = BROWNIAN;
                    break;
                case 1:
                    particle.mode = GRAVITY;
                    break;
                case 2:
                    particle.mode = GATHERING;
                    break;
                    
                    
            }
            
        }else {
            
            cout << "OSC :: unknown ADR :: " << m.getAddress() << endl;
            
        }
        
        
   
    }// end of while

    
    particle.update();


}


void VSyn::initColors(int max_num){
    
    for(int i=0; i<max_num; i++){
        
        colors[i].r = 255;
        colors[i].g = 255;
        colors[i].b = 255;
        colors[i].a = 255;
        
        
    }
    
}


void VSyn::initShapes(int max_num){

    for(int i=0; i<max_num; i++){

        shapeContainer *pC = &shapes[i];
        pC->type = VOID;
        pC->active = true;
        pC->uid = -1;
        
        pC->x1 = 0.5f;
        pC->y1 = 0.5f;
        pC->x2 = 0.5f;
        pC->y2 = 0.5f;
        
        pC->size = 0.0f;
        pC->height = 0.0f;
        pC->angle = 0.0f;
        pC->freq = 0.0f;
        pC->amp = 0.0f;
        pC->phase = 0.0f;
        pC->thick = 0.0f;
        pC->expose = 1.0f;
        
        pC->fill = false;

        
    }

}



void VSyn::draw(){
    
    screen_w = ofGetWidth();
    screen_h = ofGetHeight();

    
    //CAM CONTROL
    if(cam_flg){
        
        cam.begin();
        cam.setPosition(pov);
        cam.lookAt(look);
        
        //Invert Y axis for GL
        ofPushMatrix();
        ofScale(1, -1); //Invert Y only
        
    }


    //drawing particle
    particle.draw();
    
#ifndef DEBUG_MODE
    //drawAgents
    drawAgents(&gismo);
#endif
    
    for(int i=0; i<CONTAINER_MAX; i++){
        
        shapeContainer *elm = &shapes[i];
        //Set Color
        ofSetColor(colors[i]);

        if ( !elm->active || elm->type == VOID){
            
            continue;
            
        }
        
        switch(elm->type){
                
            case CIRCLE:
                circle(elm->x1, elm->y1, elm->size, elm->fill);
                break;
                
            case TRIANGLE:
                triangle(elm->x1, elm->y1, elm->size, elm->angle, elm->fill);
                break;

            case SQUARE:
                square(elm->x1, elm->y1, elm->size, elm->angle, elm->fill);
                break;

            case RECT:
                rect(elm->x1, elm->y1, elm->x2, elm->y2, elm->angle, elm->fill);
                break;

            case LINE:
                line(elm->x1, elm->y1, elm->x2, elm->y2, elm->thick);
                break;

            case ARC:
                arc(elm->x1, elm->y1, elm->x2, elm->y2, elm->height, elm->expose, elm->thick);
                break;

            case WAVE:
                wave(elm->x1, elm->y1, elm->x2, elm->y2, elm->freq, elm->amp, elm->phase, elm->thick);
                break;
                
            default:
                break;
                
        }
        
        
    }

    
#ifdef DEBUG_MODE
    /// DRAW_AGENTS_CONDITIONS
    int count = gismo.agents.count;
    ag_t *agents = gismo.getAgents(); //sets agents pointer
    ag_t *ag;
    string cond_flg;
    
    for(int i =0; i<count; i++){
        
        ag = agents; //Set agent address
        
        if(ag->active){

            int tmp_x = (int)( ag->posi.x * (float)screen_w );
            int tmp_y = (int)( ag->posi.y * (float)screen_h );
            
            switch(ag->condition){
                    
                case CALM:
                    cond_flg = "+";
                    //cond_flg = to_string(ag->mov);
                    ofSetColor(50,255,50);
                    break;
                    
                case CHASE:
                    cond_flg = "C";
                    ofSetColor(255,255, 50);
                    break;
                    
                case RUN:
                    cond_flg = "R";
                    ofSetColor(200, 50, 50);
                    break;
                    
                case DMG:
                    cond_flg = "D";
                    ofSetColor(255, 100, 100);
                    break;
                    
                case DEATH:
                    cond_flg = "x";
                    ofSetColor(100, 100, 100);
                    break;
                    
                default:
                    break;
                    
                    
            }
            
            ofDrawBitmapString( cond_flg, tmp_x, tmp_y);
            circle(ag->posi.x+0.0078f, ag->posi.y+0.00078f, ag->size*10.0f,false);
            ofSetColor(255,255,255);
        }
        agents++;
        
    }
    ///
#endif
    
    
    if(cam_flg){
        ofPopMatrix();
        cam.end();
    }
    
}


void VSyn::initWindowSize(){
    
    int tmp_w = ofGetWidth();
    int tmp_h = ofGetHeight();
    
    initCanvasSize(tmp_w, tmp_h);
    particle.screen_width = tmp_w;
    particle.screen_height = tmp_h;
    
    
}


void VSyn::test(){
    
    //Draw Your Test Code. This method was invoked when the end of setup().
    std::cout << "test method is starting..." << std::endl;
    
    
    //Test frand
    assert( frand()==0.1f );
    assert( frand()==0.7f );
    assert( frand()==0.7f );
    assert( frand()==0.1f );
    cout << "gismoManager::randmom() is OK."<<endl;

    
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
    
    
    //Test Sound Trigger with OSC
    sound.set(9);
    sound.reset();
    assert(sound.count==0);
    sound.set(1);
    sound.set(3);
    sound.set(7);
    assert (sound.update() == 0 );
    sound.update(); //test don't send when the event buffer was vacant.
    cout << "CLASS Sound is ok.(check the receive yourself.)" << endl;

    
    //TestEventHandler
    EventHandler eventHandler;
    EvTest evTest;
    eventHandler.eventAdd("/snd" , &sound);
    eventHandler.eventAdd("/t01" , &evTest);
    sound.set(2);
    sound.set(4);
    int val = 6;
//    int *pVal = &val;
//    assert( eventHandler.bang("/snd", pVal) == 6 );
    int args[] = {0,1,2};
    assert ( eventHandler.bang("/t01", args) == 138 );
    assert ( eventHandler.bang("/t01") == 137 );
    cout << "GismoBundledClass::eventHandler is OK." << endl;
    //Test EventHandler with Gismo
    gismo.eventAdd("/t01" , &evTest);
    gismo.bang("/t01" , args);
    //Sound Trigger
    sound.reset();
    gismo.eventAdd("/snd" , &sound);
    int snd_id = 137;
    assert( gismo.bang("/snd" , &snd_id) == 137);
    sound.update();
    //Test sending via setSound;
    assert(setSound(2355)==2355);
    assert(setSound(2356)==2356);
    sound.update();
    
    cout << "GismoManager::eventHandler with Gismo is OK." << endl;

    
    
    //Test positionLoop()
    posi_t pos;
    pos.x = 1.1; pos.y = -0.01;
    positionLoop(&pos);
    assert (pos.x == 0.0f);
    assert (pos.y == 1.0f);
    pos.x = -0.1; pos.y = 1.4;
    positionLoop(&pos);
    assert (pos.x == 1.0f);
    assert (pos.y == 0.0f);
    pos.x = 0.0f; pos.y = 1.0f;
    positionLoop(&pos);
    assert (pos.x == 1.0f);
    assert (pos.y == 1.0f);
    cout << "GismoLibrary::positionLoop() is OK" << endl;
    
    
    
    //Reset all agents
    agBuffReset(&gismo.agents);
     
     
    ag_t act1, act2, act3, act4, act5, act6, act7, act8;
//    float seed = 0.5;
//    initAgentActive(&act1);
//    act1.size = frand()*0.03f;
//    act1.mov = 0.0f;
//    act1.posi.x = 0.75;
//    act1.posi.y = 0.25;
//    act1.view = 0.0f;
//    gismo.addAgent(act1);
//    initAgentActive(&act2);
//    act2.size = 0.01f;
//    act2.view = 0.05f;
//    gismo.addAgent(act2);
//
//    initAgentActive(&act3);
//    act3.size = frand()*AG_DEF_SIZE_FIX;
//    gismo.addAgent(act3);
//
//    initAgentActive(&act4);
//    act4.size = frand()*AG_DEF_SIZE_FIX;
//    gismo.addAgent(act4);
//
//    initAgentActive(&act5);
//    act5.size = frand()*AG_DEF_SIZE_FIX;
//    gismo.addAgent(act5);
//
//    initAgentActive(&act6);
//    act6.size = frand()*AG_DEF_SIZE_FIX;
//    gismo.addAgent(act6);
//
//    initAgentActive(&act7);
//    act7.size = frand()*AG_DEF_SIZE_FIX;
//    gismo.addAgent(act7);
//    
    initAgentActive(&act8);
    //act8.mov = 0.000f;
//    act8.size = frand()*AG_DEF_SIZE_FIX;
    gismo.addAgent(act8);
    gismo.addAgent(act8);
    gismo.addAgent(act8);
    gismo.addAgent(act8);
    gismo.addAgent(act8);
    
//    for(int i=0;i<500;i++) gismo.addAgent(act8);
    

    
    std::cout << "test method has finished." << std::endl;

}
