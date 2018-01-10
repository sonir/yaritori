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
    
    
    //Create TestClass
    myTest = new Test(&sound, &ripple);
    
    ofBackground(255);
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
    //SetupEvents
    gismo.eventAdd("/addShape", this);
    
    //Set ag_shape_t and gismo pointer
    visual.motion.setShapePtr(ag_shapes);
    visual.motion.setGismoPtr(&gismo);
    visual.events.setMotionManagerPtr(&visual.motion);
    
    //Do Test Code
    this->test();
}


void VSyn::update(){
    
    //Test Update
    myTest->update();
    if( !sound.bankIsEmpty()) sound.update();
        
    
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
    screenBegin();

    
    //Draw Agents
    drawAgents(&visual);
    
    //Ripple
    ripple.draw();
    
    screenEnd();
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
            
            //square(ag->posi.x, ag->posi.y, ag->size*10.0f, 0.0f, false);
            ofDrawBitmapString( cond_flg, tmp_x, tmp_y);
            //circle(ag->posi.x+0.0078f, ag->posi.y+0.00078f, ag->view,false);
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


void VSyn::addAgShape(ag_shape_t shape){
    
    //Count exceeding check
    if( ag_shapes_count >= AG_MAX ){
        
        ag_shapes_count = 0;
        
    }
    
    ag_shapes[ag_shapes_count] = shape;
    ag_shapes_count += 1;
    
}


void VSyn::createShape(ag_shape_t &shape) {
    //Create random shape
    
    shape.node_count = (NODE_MAX - 12) * frand() + 12;
    shape.edge_count = shape.node_count * (1.0 + frand());
    
    for(int i = 0; i < NODE_MAX; i++) {
        shape.nodes[i].x = frand() - 0.5;
        shape.nodes[i].y = frand() - 0.5;
    }
    
    for (int i = 0; i <  shape.edge_count; i++) {
        shape.edges[i].node_id_a = i % int(shape.node_count * 0.25);
        shape.edges[i].node_id_b = i % shape.node_count;
    }

}


void VSyn::test(){
    
    //Draw Your Test Code. This method was invoked when the end of setup().
    std::cout << "test method is starting..." << std::endl;
    
    //Run test codes
    myTest->run();
    myTest->runVisualTest(&visual);
    
    //Test addAgShape
    ag_shape_t shape;
    shape.node_count = 137;
    shape.edges[1].node_id_a = 138;
    gismo.bang("/addShape" , &shape);
    //addAgShape(shape); //Add the shapoe
    assert(ag_shapes_count == 1);
    assert( ag_shapes[0].node_count == 137 );
    assert (ag_shapes[0].edges[1].node_id_a == 138);
    std::cout << "VSyn:: addAgShape is ok." << std::endl;
    



//    createShape(shape);
//    gismo.bang("/addShape" , &shape);
//    createShape(shape);
//    gismo.bang("/addShape" , &shape);
    
    createShape(shape);
    shape.edge_count = 4;
    shape.node_count = 4;
    shape.edges[0].node_id_a = 0; shape.edges[0].node_id_b = 1;
    shape.edges[1].node_id_a = 1; shape.edges[1].node_id_b = 2;
    shape.edges[2].node_id_a = 2; shape.edges[2].node_id_b = 3;
    shape.edges[3].node_id_a = 3; shape.edges[3].node_id_b = 0;
    gismo.bang("/addShape" , &shape);

    
    //Reset all agents
    agBuffReset(&gismo.agents);
    
    //Set Agents
    ag_t act1, act2, act3, act4, act5, act6, act7, act8;

    initAgentActive(&act8);
    act8.posi.x = 0.25f; act8.posi.y = 0.75f;
    gismo.addAgent(act8);
<<<<<<< HEAD
    act8.posi.x = frand(); act8.posi.y = 0.25f;
    act8.mov = 0.0f;
    act8.size = 0.03f;
    act8.mov = 0.001;
    gismo.addAgent(act8);
    
    
    act8.posi.x = frand();
    act8.posi.y = 0.5f;
    act8.mov = 0.0f;
    act8.mov = 0.001;
    gismo.addAgent(act8);
    
    act8.posi.y = 0.75f;
    act8.mov = 0.0f;
    act8.mov = 0.001;
    gismo.addAgent(act8);

    
    
    
=======
    act8.posi.x = 0.75f; act8.posi.y = 0.5f;
//    act8.mov = 0.0f;
    gismo.addAgent(act8);
    for(int i=0;i<600;i++) gismo.addAgent(act8);
    act8.size *= 0.8f;
    act8.mov *= 2.5f;
    act8.view *= 5.0f;
    for(int i=0;i<100;i++) gismo.addAgent(act8);
>>>>>>> origin/gismo

    
    std::cout << "test method has finished." << std::endl;
    

}
