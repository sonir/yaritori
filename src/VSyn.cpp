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
    
  ofSetFrameRate(30);
    //// EventSetup ////
    
    //ResetFunction
    //SetUpEvents
    auto f = [&](void* args){ //<- keep this desctiption
        //draw your code
        int *key_num = (int *)args;
        //Reset State
        agBuffReset(&gismo.agents);
        agBuffReset(&gismo.add);
        
    };
    gismo.lambdaAdd("/reset", f);
    
    
    ////////////////////
    
    //Set Metro
    metro = new Metro(GISMO_UPDATE_INTERVAL);
    
    ofBackground(255);
    ofSetCircleResolution(50);
    ofSetFrameRate(30);
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
    visual.events.setMotionManagerPtr(&visual.motion);
    visual.events.setRippleManagerPtr(&ripple);
    
    //Set window size for yaritori
    scManager.setup();
    renderer.setup(ORIGINAL_WIDTH, ORIGINAL_HEIGHT);
    
    
    //Color settings
    scManager.setBackground(BACKGROUND_DEFAULT_COLOR);
    visual.motion.setColor(ANIMATION_DEFAULT_COLOR);
    renderer.setColor(ANIMATION_DEFAULT_COLOR);
    ripple.setColor(ANIMATION_DEFAULT_COLOR);
    
    //Create TestClass
    myTest = new Test(&sound, &ripple);
    myTest->setup();

    //Init agent
    agBuffReset(&gismo.agents);
    agBuffReset(&gismo.add);

    //Do Test Code
    this->test();
    
    //Reset State
    agBuffReset(&gismo.agents);
    agBuffReset(&gismo.add);
}


void VSyn::update(){
    
    
    //Test Update
    myTest->update();
    if( !sound.bankIsEmpty()) sound.update();
        
    
    //sync();

    gismo.addSync();
    if(metro->update())makeInteracts(&gismo.agents);
    //makeInteracts(&gismo.agents);
    
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
    

//#ifdef DEBUG_MODE
//    //drawAgentsForSimpleGraphics for debugging
//    drawAgentsWithChar.draw(&gismo, screen_w, screen_h);
//
//#else
//    //drawAgents
//    for(int i = 0; i < 3; i++){
//        scManager.begin(i);
//
//        //Draw Agents normally
//        drawAgents(&visual);
//
//        //Ripple
//        ripple.draw();
//
//#ifdef PERFORMANCE_MODE
//    performanceManager.updateLines();
//    performanceManager.updateLinesInverted();
//    drawPerformance(&performanceManager);
//#endif
//        scManager.end(i);
//    }
//
//    scManager.draw();
//#endif
    
#ifdef DEBUG_MODE
    //drawAgentsForSimpleGraphics for debugging
    drawAgentsWithChar.draw(&gismo, screen_w, screen_h);
    
#else
    //drawAgents
    scManager.begin();
    
    //Draw Agents normally
    drawAgents(&visual);
    //Ripple
    ripple.draw();
    
    ofSetColor(scManager.getDrawColor());
#ifdef PERFORMANCE_MODE
    performanceManager.updateLines();
    performanceManager.updateLinesInverted();
    drawPerformance(&performanceManager);
    
    renderer.draw();
#endif
    scManager.end();
    
    scManager.draw();
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


    //Draw Performers
    /*
    for(int i=0; i<PERFORMER_NUM;i++){
        
        circle(performance.performers.pfm.buf[i].posi.x, performance.performers.pfm.buf[i].posi.x, SIZE_OF_PERFORMER_INDICATE,false);
        
    }
    
    for(int i=0; i< gismo.agents.count;i++){
        
        line_t *tmp = &performance.lines[i];
        tmp->node_a.x = gismo.agents.buf[i].posi.x;
        tmp->node_a.y = gismo.agents.buf[i].posi.y;
        tmp->node_b.x = performance.performers.pfm.buf[i%PERFORMER_NUM].posi.x;
        tmp->node_b.y = performance.performers.pfm.buf[i%PERFORMER_NUM].posi.y;
        
        line(tmp->node_a.x, tmp->node_a.y, tmp->node_b.x , tmp->node_b.y, 0.1f);
        //tmp->points[0].bang();
        //cout << tmp->points[0].update() << endl;;
        
        performance.bullets[i].bang();
        posi_t pos = performance.bullets[i].update(performance.lines[i]);
        circle(pos.x, pos.y, 0.0045, 1);

        
    }
    
    //bullet->bang();
    posi_t tmp = bullet->update(aLine);
    circle(tmp.x, tmp.y, 0.0045, 1);
    cout << tmp.x << endl;
     */

    
    if(cam_flg){
        ofPopMatrix();
        cam.end();
    }
    
}

void VSyn::keyPressed(int key) {
    switch (key) {
        case 's': {
            param_u params[2];
            params[0].ival = 1;
            params[1].fval = 1000;
            gismo.bang("/solo", params);
            
            break;
        }
        case 'i': {
            param_u params;
            params.bval = true;
            gismo.lambdaBang("/invert", &params);
            
            break;
        }
        case 'k': {
            param_u params[2];
            params[0].bval = 1;
            params[1].fval = 1000;
            gismo.lambdaBang("/timedInvert", &params);
            
            break;
        }
        case 'm': {
            param_u params[4];
            params[0].ival = 0;
            params[1].ival = 0;
            params[2].fval = 0.1;
            params[3].fval = 0.;
            gismo.lambdaBang("/mask", params);
            
            params[0].ival = 0;
            params[1].ival = 1;
            params[2].fval = 0.8;
            params[3].fval = 0.;
            gismo.lambdaBang("/mask", params);
            
            
            params[0].ival = 1;
            params[1].ival = 0;
            params[2].fval = 0.2;
            params[3].fval = 0.;
            gismo.lambdaBang("/mask", params);
            
            params[0].ival = 1;
            params[1].ival = 1;
            params[2].fval = 0.9;
            params[3].fval = 0.;
            gismo.lambdaBang("/mask", params);
            
            params[0].ival = 1;
            params[1].ival = 2;
            params[2].fval = 0.8;
            params[3].fval = 1.0;
            gismo.lambdaBang("/mask", params);
            
            params[0].ival = 1;
            params[1].ival = 1;
            params[2].fval = 0.1;
            params[3].fval = 1.0;
            gismo.lambdaBang("/mask", params);
            
        }
        default:
            break;
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
    
    gismo.addAgent( shape2Agent(shape) );
    
}


void VSyn::test(){

    //Draw Your Test Code. This method was invoked when the end of setup().
    std::cout << "test method is starting..." << std::endl;
    
    //Run test codes
    myTest->run();
    myTest->runVisualTest(&visual);
    

    //Test addAgShape
    ag_shape_t shape;

    shape.nodes[0].x = -0.5f;
    shape.nodes[0].y = 0.5f;
    shape.nodes[1].x = 0.5f;
    shape.nodes[1].y = 0.5f;
    shape.nodes[2].x = 0.5f;
    shape.nodes[2].y = -0.5f;
    shape.nodes[3].x = -0.5f;
    shape.nodes[3].y = -0.5f;
    shape.node_count = 4;
    shape.edges[0].node_id_a = 0;
    shape.edges[0].node_id_b = 1;
    shape.edge_count = 1;
    for(int i=0;i < AG_MAX;i++) { 
        ag_shapes[i] = shape;
        //gismo.bang("/addShape", &shape);
    }
    assert(ag_shapes_count == 0);
    
    
    //assert(ag_shapes_count == 1);
    //assert( ag_shapes[0].node_count == 2 );
    //assert (ag_shapes[0].edges[0].node_id_b == 1);
    std::cout << "VSyn:: addAgShape is ok." << std::endl;

    
    
    
    
    //Test addAgShape
//    ag_shape_t shape;
//    shape.node_count = 2;     //137
//    shape.edges[1].node_id_a = 50; //138
//    gismo.bang("/addShape" , &shape);
//    addAgShape(shape); //Add the shape
//    assert(ag_shapes_count == 1);
//    assert( ag_shapes[0].node_count == 2 );
//    assert (ag_shapes[0].edges[1].node_id_a == 50);
//    std::cout << "VSyn:: addAgShape is ok." << std::endl;

    ag_shape_t shape2;
    shape2.nodes[0].x = 0.5f;
    shape2.nodes[0].y = 0.5f;
    shape2.nodes[1].x = -0.5f;
    shape2.nodes[1].y = 0.5f;
    shape2.node_count = 2;
    shape2.edges[1].node_id_a = 0;
    shape2.edges[0].node_id_b = 1;
    shape2.edge_count = 1;
    //    ag_t tmpAg = shape2Agent(shape2);
    //    assert(tmpAg.view == 0.005f);
    //    assert(tmpAg.size == 0.00034f);
    //    assert(tmpAg.mov == 0.005f);
//    addAgShape(shape2);
//    gismo.bang("/addShape" , &shape2);
    
    ag_shape_t shape3;
    shape3.nodes[0].x = 0.05f;
    shape3.nodes[0].y = 0.05f;
    shape3.nodes[1].x = -0.05f;
    shape3.nodes[1].y = 0.5;
    shape3.node_count = 2;
    shape3.edges[0].node_id_a = 0;
    shape3.edges[0].node_id_b = 1;
    shape3.edge_count = 1;
//    ag_t tmpAg = shape2Agent(shape2);
//    assert(tmpAg.view == 0.005f);
//    assert(tmpAg.size == 0.00034f);
//    assert(tmpAg.mov == 0.005f);
     //addAgShape(shape3);
    

//    createShape(shape);
//    gismo.bang("/addShape" , &shape);
//    createShape(shape);
//    gismo.bang("/addShape" , &shape);

//    for(int i = 0; i < AG_MAX; i++) {
//        createShape(shape);
//        gismo.bang("/addShape" , &shape);
//    }
    
//    for(int i=0;i < AG_MAX; i++) {
//        myTest->createShape(&ag_shapes[i]);
//    }
    
//    shape.edge_count = 4;
//    shape.node_count = 4;
//    shape.edges[0].node_id_a = 0; shape.edges[0].node_id_b = 1;
//    shape.edges[1].node_id_a = 1; shape.edges[1].node_id_b = 2;
//    shape.edges[2].node_id_a = 2; shape.edges[2].node_id_b = 3;
//    shape.edges[3].node_id_a = 3; shape.edges[3].node_id_b = 0;

    
    //Reset all agents
    agBuffReset(&gismo.agents);
    agBuffReset(&gismo.add);
    
    //Set Agents
    ag_t ag;



    
    initAgentActive(&ag);
    ag.posi.x = 0.25f; ag.posi.y = 0.5f;
    //gismo.addAgent(ag);
    ag.posi.x = 0.75f; ag.posi.y = 0.5f;
    
    
    ag.size = 0.03;
    
    for(int i=0;i<DUMMY_AG_A_NUM;i++) gismo.addAgent(ag);

    ag.size *= 0.8f;
    ag.mov *= 2.5f;
    ag.view *= 1.0f;
    for(int i=0;i<DUMMY_AG_B_NUM;i++) gismo.addAgent(ag);
    
    
    
    
    std::cout << "test method has finished." << std::endl;
    //Reset State
//    agBuffReset(&gismo.agents);
//    agBuffReset(&gismo.add);


    
}
