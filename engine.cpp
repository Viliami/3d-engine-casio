#include "engine.h"
#include "stdlib.h"
#define BLACK 1
#define WHITE 0

double abs(double x){
    if(x < 0){
        return -x;
    }
    return x;
}

double getDistance(int x1, int x2, int y1, int y2){
    double xdiff = abs(x1-x2);
    double ydiff = abs(y1-y2);
    return sqrt((xdiff*xdiff)+(ydiff*ydiff));
}

double getDistance(Vector2 v1, Vector2 v2){
    double xdiff = abs(v1.x-v2.x);
    double ydiff = abs(v1.y-v2.y);
    return sqrt((xdiff*xdiff)+(ydiff*ydiff));
    
}

double getDistance(Vector3 v1, Vector3 v2){
    double xdiff = abs(v1.x-v2.x);
    double ydiff = abs(v1.y-v2.y);
    double zdiff = abs(v1.z-v2.z);
    return sqrt((xdiff*xdiff)+(ydiff*ydiff)+(zdiff*zdiff));
}

Engine::Engine(int width, int height){
    this->width = width;
    this->height = height;
    this->fps = 0;
    this->fps_counter = 0;
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
        Bdisp_DrawLineVRAM(x1, y1, x2, y2);
    }
    
    void Engine::draw_rect(int x, int y, int w, int h, int color){
        for(int ix = x;ix < x+w; ix++){
            for(int iy = y; iy < y+h; iy++){
                this->put_pixel(ix,iy, color);
            }
        }
    }
    
    double max(double n0, double n1){
        return (n0 > n1) ? n0:n1;
    }
    
    double min(double n0, double n1){
        return (n0 > n1) ? n1:n0;
    }
    
    double clamp(double value, double mn = 0.0, double mx = 1.0){
        return max(mn, min(value, mx));
    }
    
    double interpolate(double min, double max, double gradient){
        return min + (max - min) * clamp(gradient);
    }
    
    void Engine::processScanLine(int y, Vector2 va, Vector2 vb, Vector2 vc, Vector2 vd, int color){
        double g1 = ((va.y != vb.y) ? ((double)(y - va.y)/(vb.y-va.y)) : 1);
        double g2 = ((vc.y != vd.y) ? ((double)(y - vc.y)/(vd.y-vc.y)) : 1);
    
        double sx = interpolate(va.x, vb.x, g1);
        double ex = interpolate(vc.x, vd.x, g2);
        
        /*int z1 = interpolate(va.z, vb.z, g1);
        int z2 = interpolate(vc.z, vd.z, g2);*/
        
        for(int x = int(sx); x < int(ex); x++){
            //int grad = (x-sx)/(ex-sx);
            //int z = interpolate(z1, z2, grad);
            this->put_pixel(x,y, color);
        }
    }
    
    void Engine::fill_triangle(Vector2 v0, Vector2 v1, Vector2 v2, int color){
        Vector2 temp;
        if(v0.y > v1.y){
            temp = v1;
            v1 = v0;
            v0 = temp;
        }
        
        if(v1.y > v2.y){
            temp = v1;
            v1 = v2;
            v2 = temp;
        }
        
        if(v0.y > v1.y){
            temp = v1;
            v1 = v0;
            v0 = temp;
        }
        
        double dv0v1 = 0, dv0v2 = 0;
        
        if(v1.y - v0.y > 0){
            dv0v1 = (v1.x - v0.x) / (v1.y - v0.y);
        }else{
            dv0v1 = 0;
        }
        
        if(v2.y - v0.y > 0){
            dv0v2 = (v2.x - v0.x) / (v2.y - v0.y);
        }else{
            dv0v2 = 0;
        }
        
        if(dv0v1 > dv0v2){
            for(int y = v0.y; y < v2.y+1; y++){
                if(y < v1.y){
                    processScanLine(y, v0, v2, v0, v1, color);
                }else{
                    processScanLine(y, v0, v2, v1, v2, color);
                }
            }
        }else{
            for(int y = v0.y; y < v2.y+1; y++){
                if(y < v1.y){
                    processScanLine(y, v0, v1, v0, v2, color);
                }else{
                    processScanLine(y, v1, v2, v0, v2, color);
                }
            }
        }
    }
    
    void Engine::draw_thick_line(int x0, int y0, int x1, int y1, int thickness, int color){
        bool steep;
        int iTmp, dx, dy, error, ystep, y, xthickOver2, ythickOver2;

        steep = abs(y1 - y0) > abs(x1 - x0);
        if(steep){
            //swap(x0, y0)
            iTmp = x0;
            x0 = y0;
            y0 = iTmp;
        
            //swap(x1, y1)
            iTmp = x1;
            x1 = y1;
            y1 = iTmp;
        }
        
        if(x0 > x1){
            //swap(x0, x1)
            iTmp = x0;
            x0 = x1;
            x1 = iTmp;
            
            //swap(y0, y1)
            iTmp = y0;
            y0 = y1;
            y1 = iTmp;
        }
        
        dx = x1-x0;
        dy = abs(y1-y0);
        error = dx/2;
        ystep = 0;
        y = y0;
        if(y0 < y1){
            ystep = 1;
        }else{
            ystep = -1;
        }
        
        for(int x = x0; x <= x1; x++){
            xthickOver2 = thickness/2;
            ythickOver2 = thickness/2;
            if(steep){
                this->draw_rect(y-ythickOver2, x-xthickOver2, thickness, thickness, color);
            }else{
                this->draw_rect(x-xthickOver2, y-ythickOver2, thickness, thickness, color);
            }
            
            error -= dy;
            if(error < 0){
                y+=ystep;
                error+=dx;
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
        //const unsigned short * stuff=(const unsigned short *)"¥¥crd0¥¥filename.txt";
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

int itoa(int value, char *sp, int radix){
        char tmp[16];// be careful with the length of the buffer
        char *tp = tmp;
        int i;
        unsigned v;

        int sign = (radix == 10 && value < 0);    
        if (sign)
            v = -value;
        else
            v = (unsigned)value;

        while (v || tp == tmp)
        {
            i = v % radix;
            v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
            if (i < 10)
              *tp++ = i+'0';
            else
              *tp++ = i + 'a' - 10;
        }

        int len = tp - tmp;

        if (sign) 
        {
            *sp++ = '-';
            len++;
        }

        while (tp > tmp)
            *sp++ = *--tp;

        return len;
    }

double to_degrees(double radians) {
    return radians * (180.0 / 3.141592654);
}

double to_radians(double degrees){
    return degrees * (3.141592654 / 180.0);
}
    
void Engine::render(Camera camera, Mesh* meshes[], int numMeshes){
    Matrix4 viewMatrix = Matrix4().new_look_at(camera.position, camera.target, Vector3(0,1,0));
    //Matrix4 viewMatrix = Matrix4().new_fps_view(Vector3(0,0,20), to_radians(-30), to_radians(30));
    Matrix4 projectionMatrix = Matrix4().new_perspective(0.98, (this->width/this->height), 0.01, 10.0);
    
    Matrix4 result1, transformMatrix;
    result1 = projectionMatrix;
    result1 *= viewMatrix;
    
    for(int i = 0; i < numMeshes; i++){
        Mesh* mesh = meshes[i];
        if(!mesh->shown)
            continue;
        //if(mesh->type == 0){
            Vector3 mRotation = mesh->rotation;
            Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.z, mRotation.x);
            Matrix4 translated = Matrix4().new_translate(mesh->position.x, mesh->position.y, mesh->position.z);
            Matrix4 result, result2;
            
            result = translated;
            result*=worldMatrix;
            worldMatrix = result;
            
            transformMatrix = result1;
            transformMatrix *= worldMatrix;
            
        /*}else if(mesh->type == 1){
            transformMatrix = mesh->transformMatrix;
        }*/
        for(int j = 0; j < mesh->numFaces; j++){
            int a = mesh->faces[j].a;
            int b = mesh->faces[j].b;
            int c = mesh->faces[j].c;
            
            Vector3 vertexA = mesh->vertices[a];
            Vector3 vertexB = mesh->vertices[b];
            Vector3 vertexC = mesh->vertices[c];
            
            Vector2 pixelA = this->project(vertexA, transformMatrix);
            Vector2 pixelB = this->project(vertexB, transformMatrix);
            Vector2 pixelC = this->project(vertexC, transformMatrix);
            
            if(!mesh->filled){
                
                double distanceA = getDistance(vertexA, vertexB);
                double distanceB = getDistance(vertexB, vertexC);
                double distanceC = getDistance(vertexC, vertexA);
                
                double max;
                int max_c;
                
                if(distanceA > distanceB){
                    max = distanceA;
                    max_c = 0;
                }else{
                    max = distanceB;
                    max_c = 1;
                }
                
                if(distanceC > max){
                    max_c = 2;
                }
                
                if(max_c != 0){
                    this->draw_thick_line(pixelA.x, pixelA.y, pixelB.x, pixelB.y, mesh->line_thickness, BLACK);
                }
                if(max_c != 1){
                    this->draw_thick_line(pixelB.x, pixelB.y, pixelC.x, pixelC.y, mesh->line_thickness,  BLACK);
                }
                if(max_c != 2){
                    this->draw_thick_line(pixelC.x, pixelC.y, pixelA.x, pixelA.y, mesh->line_thickness,  BLACK);
                }
            }else{
                this->fill_triangle(pixelA, pixelB, pixelC, BLACK);
            }
        }
        this->fps_counter++;
        
        this->printFPS();
    }
}

void Engine::printFPS(){
    itoa(fps, this->temp, 10);
    PrintXY(1,1,(const unsigned char *)this->temp,0);
}

void Engine::updateFPS(){
    this->fps = this->fps_counter;
    this->fps_counter = 0;
}
