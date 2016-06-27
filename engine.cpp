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
    
    void Engine::draw_line(int x1,int y1,int x2,int y2,int color){
        int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
        dx = x2-x1;
        dy = y2-y1;
        dx1 = fabs(dx);
        dy1 = fabs(dy);
        px = 2*dy1-dx1;
        py = 2*dx1-dy1;
        if(dy1<=dx1){
            if(dx>=0){
               x=x1;
               y=y1;
               xe=x2;
            }else{
               x=x2;
               y=y2;
               xe=x1;
            }
            this->put_pixel(x,y,color);
            for(i=0;x<xe;i++){
                x=x+1;
                if(px<0){
                    px=px+2*dy1;
                }else{
                    if((dx<0 && dy<0) || (dx>0 && dy>0)){
                        y=y+1;
                    }else{
                        y=y-1;
                    }
                    px=px+2*(dy1-dx1);
                }
                this->put_pixel(x,y,color);
            }
        }else{
            if(dy>=0){
               x=x1;
               y=y1;
               ye=y2;
            }else{
               x=x2;
               y=y2;
               ye=y1;
            }
            this->put_pixel(x,y,color);
            for(i=0;y<ye;i++){
                y=y+1;
                if(py<=0){
                    py=py+2*dx1;
                }else{
                    if((dx<0 && dy<0) || (dx>0 && dy>0)){
                        x=x+1;
                    }else{
                        x=x-1;
                    }
                    py=py+2*(dx1-dy1);
                }
                this->put_pixel(x,y,color);
            }
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
    double x = point.x * /*(this->width/64.0)*/ 1.5 + (this->width/2.0); 
    double y = point.y * /*(this->height/64.0)*/ 1.5 + (this->height/2.0);
    return Vector2(x, y); 
}

void Engine::render(Camera camera, Mesh meshes[]){
    Matrix4 viewMatrix = Matrix4().new_look_at(camera.position, camera.target, Vector3(0,1,0));
    Matrix4 projectionMatrix = Matrix4().new_perspective(0.2, 1, 0.01, 1.0);
    // for(int i = 0; i <= sizeof(meshes)/sizeof(meshes[0]); i++){
    for(int i = 0; i < 1; i++){
        Mesh mesh = meshes[i];
        Vector3 mRotation = mesh.rotation;
        Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.x, mRotation.z);
        Matrix4 translated = Matrix4().new_translate(mesh.position.x, mesh.position.y, mesh.position.z);
        //worldMatrix = worldMatrix * translated;
        Matrix4 result;
        result.a = worldMatrix.a * translated.a + worldMatrix.b * translated.e + worldMatrix.c * translated.i + worldMatrix.d * translated.m;
        result.b = worldMatrix.a * translated.b + worldMatrix.b * translated.f + worldMatrix.c * translated.j + worldMatrix.d * translated.n;
        result.c = worldMatrix.a * translated.c + worldMatrix.b * translated.g + worldMatrix.c * translated.k + worldMatrix.d * translated.o;
        result.d = worldMatrix.a * translated.d + worldMatrix.b * translated.h + worldMatrix.c * translated.l + worldMatrix.d * translated.p;
        result.e = worldMatrix.e * translated.a + worldMatrix.f * translated.e + worldMatrix.g * translated.i + worldMatrix.h * translated.m;
        result.f = worldMatrix.e * translated.b + worldMatrix.f * translated.f + worldMatrix.g * translated.j + worldMatrix.h * translated.n;
        result.g = worldMatrix.e * translated.c + worldMatrix.f * translated.g + worldMatrix.g * translated.k + worldMatrix.h * translated.o;
        result.h = worldMatrix.e * translated.d + worldMatrix.f * translated.h + worldMatrix.g * translated.l + worldMatrix.h * translated.p;
        result.i = worldMatrix.i * translated.a + worldMatrix.j * translated.e + worldMatrix.k * translated.i + worldMatrix.l * translated.m;
        result.j = worldMatrix.i * translated.b + worldMatrix.j * translated.f + worldMatrix.k * translated.j + worldMatrix.l * translated.n;
        result.k = worldMatrix.i * translated.c + worldMatrix.j * translated.g + worldMatrix.k * translated.k + worldMatrix.l * translated.o;
        result.l = worldMatrix.i * translated.d + worldMatrix.j * translated.h + worldMatrix.k * translated.l + worldMatrix.l * translated.p;
        result.m = worldMatrix.m * translated.a + worldMatrix.n * translated.e + worldMatrix.o * translated.i + worldMatrix.p * translated.m;
        result.n = worldMatrix.m * translated.b + worldMatrix.n * translated.f + worldMatrix.o * translated.j + worldMatrix.p * translated.n;
        result.o = worldMatrix.m * translated.c + worldMatrix.n * translated.g + worldMatrix.o * translated.k + worldMatrix.p * translated.o;
        result.p = worldMatrix.m * translated.d + worldMatrix.n * translated.h + worldMatrix.o * translated.l + worldMatrix.p * translated.p;
        
        worldMatrix = result;
        
        Matrix4 transformMatrix, result1, result2;
        
        result1.a = worldMatrix.a * viewMatrix.a + worldMatrix.b * viewMatrix.e + worldMatrix.c * viewMatrix.i + worldMatrix.d * viewMatrix.m;
        result1.b = worldMatrix.a * viewMatrix.b + worldMatrix.b * viewMatrix.f + worldMatrix.c * viewMatrix.j + worldMatrix.d * viewMatrix.n;
        result1.c = worldMatrix.a * viewMatrix.c + worldMatrix.b * viewMatrix.g + worldMatrix.c * viewMatrix.k + worldMatrix.d * viewMatrix.o;
        result1.d = worldMatrix.a * viewMatrix.d + worldMatrix.b * viewMatrix.h + worldMatrix.c * viewMatrix.l + worldMatrix.d * viewMatrix.p;
        result1.e = worldMatrix.e * viewMatrix.a + worldMatrix.f * viewMatrix.e + worldMatrix.g * viewMatrix.i + worldMatrix.h * viewMatrix.m;
        result1.f = worldMatrix.e * viewMatrix.b + worldMatrix.f * viewMatrix.f + worldMatrix.g * viewMatrix.j + worldMatrix.h * viewMatrix.n;
        result1.g = worldMatrix.e * viewMatrix.c + worldMatrix.f * viewMatrix.g + worldMatrix.g * viewMatrix.k + worldMatrix.h * viewMatrix.o;
        result1.h = worldMatrix.e * viewMatrix.d + worldMatrix.f * viewMatrix.h + worldMatrix.g * viewMatrix.l + worldMatrix.h * viewMatrix.p;
        result1.i = worldMatrix.i * viewMatrix.a + worldMatrix.j * viewMatrix.e + worldMatrix.k * viewMatrix.i + worldMatrix.l * viewMatrix.m;
        result1.j = worldMatrix.i * viewMatrix.b + worldMatrix.j * viewMatrix.f + worldMatrix.k * viewMatrix.j + worldMatrix.l * viewMatrix.n;
        result1.k = worldMatrix.i * viewMatrix.c + worldMatrix.j * viewMatrix.g + worldMatrix.k * viewMatrix.k + worldMatrix.l * viewMatrix.o;
        result1.l = worldMatrix.i * viewMatrix.d + worldMatrix.j * viewMatrix.h + worldMatrix.k * viewMatrix.l + worldMatrix.l * viewMatrix.p;
        result1.m = worldMatrix.m * viewMatrix.a + worldMatrix.n * viewMatrix.e + worldMatrix.o * viewMatrix.i + worldMatrix.p * viewMatrix.m;
        result1.n = worldMatrix.m * viewMatrix.b + worldMatrix.n * viewMatrix.f + worldMatrix.o * viewMatrix.j + worldMatrix.p * viewMatrix.n;
        result1.o = worldMatrix.m * viewMatrix.c + worldMatrix.n * viewMatrix.g + worldMatrix.o * viewMatrix.k + worldMatrix.p * viewMatrix.o;
        result1.p = worldMatrix.m * viewMatrix.d + worldMatrix.n * viewMatrix.h + worldMatrix.o * viewMatrix.l + worldMatrix.p * viewMatrix.p;

        //transformMatrix = transformMatrix * projectionMatrix;
        
        result2.a = result1.a * projectionMatrix.a + result1.b * projectionMatrix.e + result1.c * projectionMatrix.i + result1.d * projectionMatrix.m;
        result2.b = result1.a * projectionMatrix.b + result1.b * projectionMatrix.f + result1.c * projectionMatrix.j + result1.d * projectionMatrix.n;
        result2.c = result1.a * projectionMatrix.c + result1.b * projectionMatrix.g + result1.c * projectionMatrix.k + result1.d * projectionMatrix.o;
        result2.d = result1.a * projectionMatrix.d + result1.b * projectionMatrix.h + result1.c * projectionMatrix.l + result1.d * projectionMatrix.p;
        result2.e = result1.e * projectionMatrix.a + result1.f * projectionMatrix.e + result1.g * projectionMatrix.i + result1.h * projectionMatrix.m;
        result2.f = result1.e * projectionMatrix.b + result1.f * projectionMatrix.f + result1.g * projectionMatrix.j + result1.h * projectionMatrix.n;
        result2.g = result1.e * projectionMatrix.c + result1.f * projectionMatrix.g + result1.g * projectionMatrix.k + result1.h * projectionMatrix.o;
        result2.h = result1.e * projectionMatrix.d + result1.f * projectionMatrix.h + result1.g * projectionMatrix.l + result1.h * projectionMatrix.p;
        result2.i = result1.i * projectionMatrix.a + result1.j * projectionMatrix.e + result1.k * projectionMatrix.i + result1.l * projectionMatrix.m;
        result2.j = result1.i * projectionMatrix.b + result1.j * projectionMatrix.f + result1.k * projectionMatrix.j + result1.l * projectionMatrix.n;
        result2.k = result1.i * projectionMatrix.c + result1.j * projectionMatrix.g + result1.k * projectionMatrix.k + result1.l * projectionMatrix.o;
        result2.l = result1.i * projectionMatrix.d + result1.j * projectionMatrix.h + result1.k * projectionMatrix.l + result1.l * projectionMatrix.p;
        result2.m = result1.m * projectionMatrix.a + result1.n * projectionMatrix.e + result1.o * projectionMatrix.i + result1.p * projectionMatrix.m;
        result2.n = result1.m * projectionMatrix.b + result1.n * projectionMatrix.f + result1.o * projectionMatrix.j + result1.p * projectionMatrix.n;
        result2.o = result1.m * projectionMatrix.c + result1.n * projectionMatrix.g + result1.o * projectionMatrix.k + result1.p * projectionMatrix.o;
        result2.p = result1.m * projectionMatrix.d + result1.n * projectionMatrix.h + result1.o * projectionMatrix.l + result1.p * projectionMatrix.p;

        transformMatrix = result2;
        //for(int j = 0; j <= sizeof(mesh.vertices)/sizeof(mesh.vertices[0]); j++){
        /*for(int j = 0; j <= 7; j++){
            Vector2 point = this->project(mesh.vertices[j], transformMatrix);
            this->put_pixel(point.x, point.y, BLACK);
        }*/
        /*for(int j = 0; j < 7; j++){
            Vector2 point0 = this->project(mesh.vertices[j], transformMatrix);
            Vector2 point1 = this->project(mesh.vertices[j+1], transformMatrix);
            this->draw_line(point0.x, point0.y, point1.x, point1.y, BLACK);
        }*/
        for(int j = 0; j < sizeof(mesh.faces)/sizeof(mesh.faces[0]); j++){
            int a = mesh.faces[j].a;
            int b = mesh.faces[j].b;
            int c = mesh.faces[j].c;
            Vector3 vertexA = mesh.vertices[a];
            Vector3 vertexB = mesh.vertices[b];
            Vector3 vertexC = mesh.vertices[c];
            
            Vector2 pixelA = this->project(vertexA, transformMatrix);
            Vector2 pixelB = this->project(vertexB, transformMatrix);
            Vector2 pixelC = this->project(vertexC, transformMatrix);
            
            this->draw_line(pixelA.x, pixelA.y, pixelB.x, pixelB.y, BLACK);
            this->draw_line(pixelB.x, pixelB.y, pixelC.x, pixelC.y, BLACK);
            this->draw_line(pixelC.x, pixelC.y, pixelA.x, pixelA.y, BLACK);
        }
        
    }
}
