#include "engine.h"
extern "C"{
#include "fxlib.h"
}
Engine::Engine(int width, int height){
    this->width = width;
    this->height = height;
}

extern "C"{
    void Engine::clear(){
        Bdisp_AllClr_VRAM();
    }
    
    void Engine::present(){
        Bdisp_PutDisp_DD();
    }
};

void Engine::render(Camera camera, Mesh meshes){
    
}
