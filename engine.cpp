#include "engine.h"
#define BLACK 1
#define WHITE 0
/*extern "C"{
#include "fxlib.h"
}*/
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
    double x = point.x * (this->width) + (this->width/2.0); 
    double y = point.y * (this->height) + (this->height/2.0);
    return Vector2(x, y); 
}

extern "C"{
    
    void save_stuff(const FONTCHARACTER *filename, int stuff_to_save){
        int handle = Bfile_OpenFile(filename, _OPENMODE_WRITE);
        if(handle <= 0){
            Bfile_CreateFile(filename, sizeof(stuff_to_save));
            Bfile_OpenFile(filename, _OPENMODE_WRITE);
        }
        Bfile_WriteFile(handle, &stuff_to_save, sizeof(stuff_to_save));
    }
    
    Mesh Engine::load_obj(const FONTCHARACTER *filename){
        const unsigned short * stuff=(const unsigned short *)"¥¥crd0¥¥filename.txt";
        Mesh mesh = Mesh();
        Vector3 vertices[600];
        Vector3 faces[600];
        int file_handle = Bfile_OpenFile(filename, _OPENMODE_READ);
        if(file_handle <= 0){
            return 0;
        }
        char* buffer;
        Bfile_ReadFile(file_handle, &buffer, sizeof("# Blender3D"), 0);
        return mesh;
    }
}

void Engine::render(Camera camera, Mesh meshes[]){
    Matrix4 viewMatrix = Matrix4().new_look_at(camera.position, camera.target, Vector3(0,1,0));
    Matrix4 projectionMatrix = Matrix4().new_perspective(0.78, (this->width/this->height), 0.01, 1.0);
    // for(int i = 0; i <= sizeof(meshes)/sizeof(meshes[0]); i++){
    for(int i = 0; i < 1; i++){
        Mesh mesh = meshes[i];
        Vector3 mRotation = mesh.rotation;
        Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.z, mRotation.x);
        Matrix4 translated = Matrix4().new_translate(mesh.position.x, mesh.position.y, mesh.position.z);
        //worldMatrix = worldMatrix * translated;
        Matrix4 result;
        result.a = translated.a * worldMatrix.a + translated.b * worldMatrix.e + translated.c * worldMatrix.i + translated.d * worldMatrix.m;
        result.b = translated.a * worldMatrix.b + translated.b * worldMatrix.f + translated.c * worldMatrix.j + translated.d * worldMatrix.n;
        result.c = translated.a * worldMatrix.c + translated.b * worldMatrix.g + translated.c * worldMatrix.k + translated.d * worldMatrix.o;
        result.d = translated.a * worldMatrix.d + translated.b * worldMatrix.h + translated.c * worldMatrix.l + translated.d * worldMatrix.p;
        result.e = translated.e * worldMatrix.a + translated.f * worldMatrix.e + translated.g * worldMatrix.i + translated.h * worldMatrix.m;
        result.f = translated.e * worldMatrix.b + translated.f * worldMatrix.f + translated.g * worldMatrix.j + translated.h * worldMatrix.n;
        result.g = translated.e * worldMatrix.c + translated.f * worldMatrix.g + translated.g * worldMatrix.k + translated.h * worldMatrix.o;
        result.h = translated.e * worldMatrix.d + translated.f * worldMatrix.h + translated.g * worldMatrix.l + translated.h * worldMatrix.p;
        result.i = translated.i * worldMatrix.a + translated.j * worldMatrix.e + translated.k * worldMatrix.i + translated.l * worldMatrix.m;
        result.j = translated.i * worldMatrix.b + translated.j * worldMatrix.f + translated.k * worldMatrix.j + translated.l * worldMatrix.n;
        result.k = translated.i * worldMatrix.c + translated.j * worldMatrix.g + translated.k * worldMatrix.k + translated.l * worldMatrix.o;
        result.l = translated.i * worldMatrix.d + translated.j * worldMatrix.h + translated.k * worldMatrix.l + translated.l * worldMatrix.p;
        result.m = translated.m * worldMatrix.a + translated.n * worldMatrix.e + translated.o * worldMatrix.i + translated.p * worldMatrix.m;
        result.n = translated.m * worldMatrix.b + translated.n * worldMatrix.f + translated.o * worldMatrix.j + translated.p * worldMatrix.n;
        result.o = translated.m * worldMatrix.c + translated.n * worldMatrix.g + translated.o * worldMatrix.k + translated.p * worldMatrix.o;
        result.p = translated.m * worldMatrix.d + translated.n * worldMatrix.h + translated.o * worldMatrix.l + translated.p * worldMatrix.p;
        
        worldMatrix = result;
        
        Matrix4 transformMatrix, result1, result2;
        //worldMatrix * viewMatrix * projectionMatrix
        
        //projection * viewMatrix * worldMatrix
        result1.a = projectionMatrix.a * viewMatrix.a + projectionMatrix.b * viewMatrix.e + projectionMatrix.c * viewMatrix.i + projectionMatrix.d * viewMatrix.m;
        result1.b = projectionMatrix.a * viewMatrix.b + projectionMatrix.b * viewMatrix.f + projectionMatrix.c * viewMatrix.j + projectionMatrix.d * viewMatrix.n;
        result1.c = projectionMatrix.a * viewMatrix.c + projectionMatrix.b * viewMatrix.g + projectionMatrix.c * viewMatrix.k + projectionMatrix.d * viewMatrix.o;
        result1.d = projectionMatrix.a * viewMatrix.d + projectionMatrix.b * viewMatrix.h + projectionMatrix.c * viewMatrix.l + projectionMatrix.d * viewMatrix.p;
        result1.e = projectionMatrix.e * viewMatrix.a + projectionMatrix.f * viewMatrix.e + projectionMatrix.g * viewMatrix.i + projectionMatrix.h * viewMatrix.m;
        result1.f = projectionMatrix.e * viewMatrix.b + projectionMatrix.f * viewMatrix.f + projectionMatrix.g * viewMatrix.j + projectionMatrix.h * viewMatrix.n;
        result1.g = projectionMatrix.e * viewMatrix.c + projectionMatrix.f * viewMatrix.g + projectionMatrix.g * viewMatrix.k + projectionMatrix.h * viewMatrix.o;
        result1.h = projectionMatrix.e * viewMatrix.d + projectionMatrix.f * viewMatrix.h + projectionMatrix.g * viewMatrix.l + projectionMatrix.h * viewMatrix.p;
        result1.i = projectionMatrix.i * viewMatrix.a + projectionMatrix.j * viewMatrix.e + projectionMatrix.k * viewMatrix.i + projectionMatrix.l * viewMatrix.m;
        result1.j = projectionMatrix.i * viewMatrix.b + projectionMatrix.j * viewMatrix.f + projectionMatrix.k * viewMatrix.j + projectionMatrix.l * viewMatrix.n;
        result1.k = projectionMatrix.i * viewMatrix.c + projectionMatrix.j * viewMatrix.g + projectionMatrix.k * viewMatrix.k + projectionMatrix.l * viewMatrix.o;
        result1.l = projectionMatrix.i * viewMatrix.d + projectionMatrix.j * viewMatrix.h + projectionMatrix.k * viewMatrix.l + projectionMatrix.l * viewMatrix.p;
        result1.m = projectionMatrix.m * viewMatrix.a + projectionMatrix.n * viewMatrix.e + projectionMatrix.o * viewMatrix.i + projectionMatrix.p * viewMatrix.m;
        result1.n = projectionMatrix.m * viewMatrix.b + projectionMatrix.n * viewMatrix.f + projectionMatrix.o * viewMatrix.j + projectionMatrix.p * viewMatrix.n;
        result1.o = projectionMatrix.m * viewMatrix.c + projectionMatrix.n * viewMatrix.g + projectionMatrix.o * viewMatrix.k + projectionMatrix.p * viewMatrix.o;
        result1.p = projectionMatrix.m * viewMatrix.d + projectionMatrix.n * viewMatrix.h + projectionMatrix.o * viewMatrix.l + projectionMatrix.p * viewMatrix.p;

        //transformMatrix = transformMatrix * projectionMatrix;
        
        result2.a = result1.a * worldMatrix.a + result1.b * worldMatrix.e + result1.c * worldMatrix.i + result1.d * worldMatrix.m;
        result2.b = result1.a * worldMatrix.b + result1.b * worldMatrix.f + result1.c * worldMatrix.j + result1.d * worldMatrix.n;
        result2.c = result1.a * worldMatrix.c + result1.b * worldMatrix.g + result1.c * worldMatrix.k + result1.d * worldMatrix.o;
        result2.d = result1.a * worldMatrix.d + result1.b * worldMatrix.h + result1.c * worldMatrix.l + result1.d * worldMatrix.p;
        result2.e = result1.e * worldMatrix.a + result1.f * worldMatrix.e + result1.g * worldMatrix.i + result1.h * worldMatrix.m;
        result2.f = result1.e * worldMatrix.b + result1.f * worldMatrix.f + result1.g * worldMatrix.j + result1.h * worldMatrix.n;
        result2.g = result1.e * worldMatrix.c + result1.f * worldMatrix.g + result1.g * worldMatrix.k + result1.h * worldMatrix.o;
        result2.h = result1.e * worldMatrix.d + result1.f * worldMatrix.h + result1.g * worldMatrix.l + result1.h * worldMatrix.p;
        result2.i = result1.i * worldMatrix.a + result1.j * worldMatrix.e + result1.k * worldMatrix.i + result1.l * worldMatrix.m;
        result2.j = result1.i * worldMatrix.b + result1.j * worldMatrix.f + result1.k * worldMatrix.j + result1.l * worldMatrix.n;
        result2.k = result1.i * worldMatrix.c + result1.j * worldMatrix.g + result1.k * worldMatrix.k + result1.l * worldMatrix.o;
        result2.l = result1.i * worldMatrix.d + result1.j * worldMatrix.h + result1.k * worldMatrix.l + result1.l * worldMatrix.p;
        result2.m = result1.m * worldMatrix.a + result1.n * worldMatrix.e + result1.o * worldMatrix.i + result1.p * worldMatrix.m;
        result2.n = result1.m * worldMatrix.b + result1.n * worldMatrix.f + result1.o * worldMatrix.j + result1.p * worldMatrix.n;
        result2.o = result1.m * worldMatrix.c + result1.n * worldMatrix.g + result1.o * worldMatrix.k + result1.p * worldMatrix.o;
        result2.p = result1.m * worldMatrix.d + result1.n * worldMatrix.h + result1.o * worldMatrix.l + result1.p * worldMatrix.p;

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
