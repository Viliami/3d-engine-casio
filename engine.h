#include "mathlib.cpp"
#include "camera.h"
#include "mesh.h"

class Engine{
    public:
        int width;
        int height;
        Engine(int width = 128, int height = 64);
        void clear();
        void present();
        void put_pixel(int x, int y, int color);
        Vector2 project(Vector3 coord, Matrix4 transMat);
        void draw_point(Vector2 point);
        void render(Camera camera, Mesh meshes);
        
};
