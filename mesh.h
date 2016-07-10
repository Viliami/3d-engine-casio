#include "mathlib.cpp"

class Face{
    public:
        double a;
        double b;
        double c;
        Face(double a = 0, double b = 0, double c = 0){
            this->a = a;
            this->b = b;
            this->c = c;
        }
};

class Mesh{
    public:    
        Vector3 vertices[8];
        Vector3 position;
        Vector3 rotation;
        int numVertices;
        int numFaces;
        Face faces[12];
        int type;
        int color;
        Matrix4 transformMatrix;
        bool shown;
        int line_thickness;
        Mesh(int verticesCount = 0, int facesCount = 0, int type = 0, int color = 0){
            this->numVertices = verticesCount;
            this->numFaces = facesCount;
            this->type = type;
            this->color = color;
            this->shown = true;
            this->line_thickness = 1;
        };
        
        Matrix4 build_transformMatrix(Camera cam){
            
            Matrix4 viewMatrix = Matrix4().new_look_at(cam.position, cam.target, Vector3(0,1,0));
            Matrix4 projectionMatrix = Matrix4().new_perspective(0.98, 2.0, 0.01, 10.0);
            
            Matrix4 result, result1, result2;
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

            
            Vector3 mRotation = this->rotation;
            Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.z, mRotation.x);
            Matrix4 translated = Matrix4().new_translate(this->position.x, this->position.y, this->position.z);
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

            this->transformMatrix = result2;
            return result2;
        };
};
