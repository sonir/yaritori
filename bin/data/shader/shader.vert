#version 150

in vec4 position;
in float uSizeOffset;

uniform mat4 modelViewProjectionMatrix;


float getPointSize(float _size) {
    float pointSize = 3.5;
    if(_size < 0.02) {
        pointSize = 2.0;
    } else if (0.02 <= _size && _size < 0.03) {
        pointSize = 2.0;
    } else if(0.03 <= _size && _size < 0.04) {
        pointSize = 2.5;
    } else if(0.04 <= _size && _size < 0.05) {
        pointSize = 3.0;
    } else {
        pointSize += 4.0 * _size;
    }
    
    return pointSize;
}



void main() {
    vec4 pos = modelViewProjectionMatrix * position;
    
    gl_Position = pos;
    gl_PointSize = getPointSize(uSizeOffset);

}
