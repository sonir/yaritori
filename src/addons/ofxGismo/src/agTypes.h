//
//  agTypes.h
//  yaritori
//
//  Created by sonir on 12/13/17.
//
//

#ifndef agTypes_h
#define agTypes_h

#define AG_BUF_MAX 2500


//ENUM CONDITIONS
typedef enum {CALM, CHASE, RUN, DMG, DEATH} condition_t;

//Define Structs
typedef struct posi_t {
    
    float x;
    float y;
    
} posi_t;


typedef struct ag_t {
    
    bool active;
    posi_t posi;
    float size;
    float view;
    float mov;
    condition_t condition;
    
} ag_t;


typedef struct agent_buf_t{
    
    int count;
    ag_t buf[AG_BUF_MAX];
    
    
}agent_buf_t;

typedef struct put_buf_t {

    int count;
    ag_t buf[AG_BUF_MAX];

} put_buf_t;



#endif /* agTypes_h */
