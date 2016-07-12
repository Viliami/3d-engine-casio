#include "mathlib.cpp"
#include "camera.h"
#include "mesh.h"
extern "C"{
#include "fxlib.h"
}
class Engine{
    public:
        int width, height;
        int fps, fps_counter;
        char temp[16];
        Engine(int width = 128, int height = 64);
        void clear();
        void present();
        void put_pixel(int x, int y, int color);
        void draw_line(int x1, int y1, int x2, int y2, int color);
        void draw_thick_line(int x0, int y0, int x1, int y1, int thickness, int color);
        void draw_rect(int x, int y, int w, int h, int color);
        Vector2 project(Vector3 coord, Matrix4 transMat);
        void draw_point(Vector2 point);
        void render(Camera camera, Mesh* meshes[], int numMeshes = 1);
        Mesh load_obj(const FONTCHARACTER *filename);
        void updateFPS();
        void printFPS();
};
