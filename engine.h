#include "mathlib.cpp"
#include <string>

class Engine{
    public:
        Engine();
        
        class Camera{
            public:
                Vector3 position;
                Vector3 target;
                Camera();
        };
        
        class Mesh{
            public:
                string name;
                Vector3 vertices[10];
                Vector3 position;
                Vector3 rotation;
                Mesh(string name, int verticesCount);
        };
};
