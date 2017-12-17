
#include <stdio.h>
//#include "ofMain.h"


class GismoManager{
    
    public:
    
        static GismoManager *GetInstance(){
            
            return g_pInstance;
            
            
        }
    
        static void Create();
        static void Terminate();
        int foo = 137;
    
        static GismoManager *g_pInstance;
        GismoManager(); //Hide the instance methods
    
    
    private:
        GismoManager() = default;
        ~GismoManager() = default;
    
    
    
};
