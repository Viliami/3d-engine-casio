#include "engine.h"
#define BLACK 1
#define WHITE 0
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
    
    void Engine::put_pixel(int x, int y, int color){
        if(x >= 0 && y >= 0 && x < width && y < height){
            Bdisp_SetPoint_VRAM(x, y, color);
        }
    }
};

void Engine::draw_point(Vector2 point){
    if(point.x >= 0 && point.y >= 0 && point.x < this->width && point.y < this->height){
        this->put_pixel(point.x, point.y, BLACK);
    }
}

Vector2 Engine::project(Vector3 coord, Matrix4 transMat){
    Vector3 point = transMat.transform(coord);
    double x = point.x * (this->width/64.0) + (this->width/2.0); 
    double y = point.y * (this->height/64.0)+ (this->height/2.0);
    return Vector2(x, y); 
}

void Engine::render(Camera camera, Mesh meshes[]){
    Matrix4 viewMatrix = Matrix4().new_look_at(camera.position, camera.target, Vector3(0,1,0));
    Matrix4 projectionMatrix = Matrix4().new_perspective(0.2, (this->width/this->height), 0.01, 1.0);
    
    // for(int i = 0; i <= sizeof(meshes)/sizeof(meshes[0]); i++){
    for(int i = 0; i <= 1; i++){
        Mesh mesh = meshes[i];
        Vector3 mRotation = mesh.rotation;
        Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.x, mRotation.z);
        Matrix4 translated = Matrix4().new_translate(mesh.position.x, mesh.position.y, mesh.position.z);
        //worldMatrix = worldMatrix * translated;
        
        worldMatrix.a = worldMatrix.a * translated.a + worldMatrix.b * translated.e + worldMatrix.c * translated.i + worldMatrix.d * translated.m;
        worldMatrix.b = worldMatrix.a * translated.b + worldMatrix.b * translated.f + worldMatrix.c * translated.j + worldMatrix.d * translated.n;
        worldMatrix.c = worldMatrix.a * translated.c + worldMatrix.b * translated.g + worldMatrix.c * translated.k + worldMatrix.d * translated.o;
        worldMatrix.d = worldMatrix.a * translated.d + worldMatrix.b * translated.h + worldMatrix.c * translated.l + worldMatrix.d * translated.p;
        worldMatrix.e = worldMatrix.e * translated.a + worldMatrix.f * translated.e + worldMatrix.g * translated.i + worldMatrix.h * translated.m;
        worldMatrix.f = worldMatrix.e * translated.b + worldMatrix.f * translated.f + worldMatrix.g * translated.j + worldMatrix.h * translated.n;
        worldMatrix.g = worldMatrix.e * translated.c + worldMatrix.f * translated.g + worldMatrix.g * translated.k + worldMatrix.h * translated.o;
        worldMatrix.h = worldMatrix.e * translated.d + worldMatrix.f * translated.h + worldMatrix.g * translated.l + worldMatrix.h * translated.p;
        worldMatrix.i = worldMatrix.i * translated.a + worldMatrix.j * translated.e + worldMatrix.k * translated.i + worldMatrix.l * translated.m;
        worldMatrix.j = worldMatrix.i * translated.b + worldMatrix.j * translated.f + worldMatrix.k * translated.j + worldMatrix.l * translated.n;
        worldMatrix.k = worldMatrix.i * translated.c + worldMatrix.j * translated.g + worldMatrix.k * translated.k + worldMatrix.l * translated.o;
        worldMatrix.l = worldMatrix.i * translated.d + worldMatrix.j * translated.h + worldMatrix.k * translated.l + worldMatrix.l * translated.p;
        worldMatrix.m = worldMatrix.m * translated.a + worldMatrix.n * translated.e + worldMatrix.o * translated.i + worldMatrix.p * translated.m;
        worldMatrix.n = worldMatrix.m * translated.b + worldMatrix.n * translated.f + worldMatrix.o * translated.j + worldMatrix.p * translated.n;
        worldMatrix.o = worldMatrix.m * translated.c + worldMatrix.n * translated.g + worldMatrix.o * translated.k + worldMatrix.p * translated.o;
        worldMatrix.p = worldMatrix.m * translated.d + worldMatrix.n * translated.h + worldMatrix.o * translated.l + worldMatrix.p * translated.p;
        
        
        Matrix4 transformMatrix;
        
        transformMatrix.a = worldMatrix.a * viewMatrix.a + worldMatrix.b * viewMatrix.e + worldMatrix.c * viewMatrix.i + worldMatrix.d * viewMatrix.m;
        transformMatrix.b = worldMatrix.a * viewMatrix.b + worldMatrix.b * viewMatrix.f + worldMatrix.c * viewMatrix.j + worldMatrix.d * viewMatrix.n;
        transformMatrix.c = worldMatrix.a * viewMatrix.c + worldMatrix.b * viewMatrix.g + worldMatrix.c * viewMatrix.k + worldMatrix.d * viewMatrix.o;
        transformMatrix.d = worldMatrix.a * viewMatrix.d + worldMatrix.b * viewMatrix.h + worldMatrix.c * viewMatrix.l + worldMatrix.d * viewMatrix.p;
        transformMatrix.e = worldMatrix.e * viewMatrix.a + worldMatrix.f * viewMatrix.e + worldMatrix.g * viewMatrix.i + worldMatrix.h * viewMatrix.m;
        transformMatrix.f = worldMatrix.e * viewMatrix.b + worldMatrix.f * viewMatrix.f + worldMatrix.g * viewMatrix.j + worldMatrix.h * viewMatrix.n;
        transformMatrix.g = worldMatrix.e * viewMatrix.c + worldMatrix.f * viewMatrix.g + worldMatrix.g * viewMatrix.k + worldMatrix.h * viewMatrix.o;
        transformMatrix.h = worldMatrix.e * viewMatrix.d + worldMatrix.f * viewMatrix.h + worldMatrix.g * viewMatrix.l + worldMatrix.h * viewMatrix.p;
        transformMatrix.i = worldMatrix.i * viewMatrix.a + worldMatrix.j * viewMatrix.e + worldMatrix.k * viewMatrix.i + worldMatrix.l * viewMatrix.m;
        transformMatrix.j = worldMatrix.i * viewMatrix.b + worldMatrix.j * viewMatrix.f + worldMatrix.k * viewMatrix.j + worldMatrix.l * viewMatrix.n;
        transformMatrix.k = worldMatrix.i * viewMatrix.c + worldMatrix.j * viewMatrix.g + worldMatrix.k * viewMatrix.k + worldMatrix.l * viewMatrix.o;
        transformMatrix.l = worldMatrix.i * viewMatrix.d + worldMatrix.j * viewMatrix.h + worldMatrix.k * viewMatrix.l + worldMatrix.l * viewMatrix.p;
        transformMatrix.m = worldMatrix.m * viewMatrix.a + worldMatrix.n * viewMatrix.e + worldMatrix.o * viewMatrix.i + worldMatrix.p * viewMatrix.m;
        transformMatrix.n = worldMatrix.m * viewMatrix.b + worldMatrix.n * viewMatrix.f + worldMatrix.o * viewMatrix.j + worldMatrix.p * viewMatrix.n;
        transformMatrix.o = worldMatrix.m * viewMatrix.c + worldMatrix.n * viewMatrix.g + worldMatrix.o * viewMatrix.k + worldMatrix.p * viewMatrix.o;
        transformMatrix.p = worldMatrix.m * viewMatrix.d + worldMatrix.n * viewMatrix.h + worldMatrix.o * viewMatrix.l + worldMatrix.p * viewMatrix.p;

        //transformMatrix = transformMatrix * projectionMatrix;
        
        transformMatrix.a = transformMatrix.a * projectionMatrix.a + transformMatrix.b * projectionMatrix.e + transformMatrix.c * projectionMatrix.i + transformMatrix.d * projectionMatrix.m;
        transformMatrix.b = transformMatrix.a * projectionMatrix.b + transformMatrix.b * projectionMatrix.f + transformMatrix.c * projectionMatrix.j + transformMatrix.d * projectionMatrix.n;
        transformMatrix.c = transformMatrix.a * projectionMatrix.c + transformMatrix.b * projectionMatrix.g + transformMatrix.c * projectionMatrix.k + transformMatrix.d * projectionMatrix.o;
        transformMatrix.d = transformMatrix.a * projectionMatrix.d + transformMatrix.b * projectionMatrix.h + transformMatrix.c * projectionMatrix.l + transformMatrix.d * projectionMatrix.p;
        transformMatrix.e = transformMatrix.e * projectionMatrix.a + transformMatrix.f * projectionMatrix.e + transformMatrix.g * projectionMatrix.i + transformMatrix.h * projectionMatrix.m;
        transformMatrix.f = transformMatrix.e * projectionMatrix.b + transformMatrix.f * projectionMatrix.f + transformMatrix.g * projectionMatrix.j + transformMatrix.h * projectionMatrix.n;
        transformMatrix.g = transformMatrix.e * projectionMatrix.c + transformMatrix.f * projectionMatrix.g + transformMatrix.g * projectionMatrix.k + transformMatrix.h * projectionMatrix.o;
        transformMatrix.h = transformMatrix.e * projectionMatrix.d + transformMatrix.f * projectionMatrix.h + transformMatrix.g * projectionMatrix.l + transformMatrix.h * projectionMatrix.p;
        transformMatrix.i = transformMatrix.i * projectionMatrix.a + transformMatrix.j * projectionMatrix.e + transformMatrix.k * projectionMatrix.i + transformMatrix.l * projectionMatrix.m;
        transformMatrix.j = transformMatrix.i * projectionMatrix.b + transformMatrix.j * projectionMatrix.f + transformMatrix.k * projectionMatrix.j + transformMatrix.l * projectionMatrix.n;
        transformMatrix.k = transformMatrix.i * projectionMatrix.c + transformMatrix.j * projectionMatrix.g + transformMatrix.k * projectionMatrix.k + transformMatrix.l * projectionMatrix.o;
        transformMatrix.l = transformMatrix.i * projectionMatrix.d + transformMatrix.j * projectionMatrix.h + transformMatrix.k * projectionMatrix.l + transformMatrix.l * projectionMatrix.p;
        transformMatrix.m = transformMatrix.m * projectionMatrix.a + transformMatrix.n * projectionMatrix.e + transformMatrix.o * projectionMatrix.i + transformMatrix.p * projectionMatrix.m;
        transformMatrix.n = transformMatrix.m * projectionMatrix.b + transformMatrix.n * projectionMatrix.f + transformMatrix.o * projectionMatrix.j + transformMatrix.p * projectionMatrix.n;
        transformMatrix.o = transformMatrix.m * projectionMatrix.c + transformMatrix.n * projectionMatrix.g + transformMatrix.o * projectionMatrix.k + transformMatrix.p * projectionMatrix.o;
        transformMatrix.p = transformMatrix.m * projectionMatrix.d + transformMatrix.n * projectionMatrix.h + transformMatrix.o * projectionMatrix.l + transformMatrix.p * projectionMatrix.p;

        
        //for(int j = 0; j <= sizeof(mesh.vertices)/sizeof(mesh.vertices[0]); j++){
        for(int j = 0; j <= 7; j++){
            Vector2 point = this->project(mesh.vertices[j], transformMatrix);
            this->put_pixel(point.x, point.y, BLACK);
        }
    }
}
