#version 150

#define M_2XPI 6.2831853
#define TREMOR_RATIO 0.5
#define NODE_MAX 128
#define MOV_FIX 0.12

in vec4 position;
uniform mat4 modelViewProjectionMatrix;

uniform float t;
uniform float carStep[NODE_MAX];
uniform float modStep[NODE_MAX];
uniform float velocityX[NODE_MAX];
uniform float velocityY[NODE_MAX];
uniform float color;
uniform int CANVAS_HEIGHT;
uniform float size;


float modulate(int index) {
    float carPhase = carStep[index] * t;    //Carrier
    float modPhase = modStep[index] * t;    //Modulater
    
    float value = (sin(carPhase) + sin(modPhase)) * 0.5 * CANVAS_HEIGHT * size * TREMOR_RATIO;
    
    return value;
}

void main() {
    vec4 pos = modelViewProjectionMatrix * position;
    
    float phase = modulate(gl_VertexID);
    
//    pos.x += velocityX[gl_VertexID] * phase;
//    pos.y += velocityY[gl_VertexID] * phase;
    
    gl_Position = pos;
}
