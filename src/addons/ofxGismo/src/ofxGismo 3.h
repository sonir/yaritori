
// How to Use from your src
//      GismoManager& gismo = GismoManager::getInstance();
//      cout << gismo.foo << endl;
//      gismo.foo = 139;

#include <stdio.h>


class GismoManager{
    
    public:
        //Kill methods related with duplication of instance
        GismoManager(const GismoManager&) = delete;
        GismoManager& operator=(const GismoManager&) = delete;
        GismoManager(GismoManager&&) = delete;
        GismoManager& operator=(GismoManager&&) = delete;
    
        static GismoManager& getInstance(){
            static GismoManager inst; //Invoke privated constructor
            return inst;
        }
    
        const char* getString(){
            return "Hello world!";		//to invoke, write " Singleton::getInstance().getString(); " 
        }
    
    
        int foo = 137;
    
    private:
        GismoManager() = default;
        ~GismoManager() = default;
    
    
    
};
