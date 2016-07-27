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
        Vector3 rotation;
        Vector3 position;
        //Vector3 vertices[8];
        //Face faces[12];
        Vector3 *vertices;
        Face *faces;
        int numVertices, numFaces;
        int type, color, line_thickness;
        //Matrix4 transformMatrix;
        bool shown, filled;
        Mesh(int verticesCount = 0, int facesCount = 0, int type = 0, int color = 1){
            this->numVertices = verticesCount;
            this->numFaces = facesCount;
            this->vertices = new Vector3[verticesCount];
            this->faces = new Face[facesCount];
            this->type = type;
            this->color = color;
            this->shown = true;
            this->line_thickness = 1;
            this->filled = false;
        };
        
        /*Matrix4 build_transformMatrix(Camera cam){
            
            Vector3 mRotation = this->rotation;
            Matrix4 viewMatrix = Matrix4().new_look_at(cam.position, cam.target, Vector3(0,1,0));
            Matrix4 projectionMatrix = Matrix4().new_perspective(0.98, 2.0, 0.01, 10.0);
            Matrix4 worldMatrix = Matrix4().new_rotate_euler(mRotation.y, mRotation.z, mRotation.x);
            Matrix4 translated = Matrix4().new_translate(this->position.x, this->position.y, this->position.z);
            
            Matrix4 result, result1, result2;
            result1 = projectionMatrix;
            result1 *= viewMatrix;
            
            
            result = translated;
            result *= worldMatrix;
            
            this->transformMatrix = result1;
            this->transformMatrix *= worldMatrix;
            
            return this->transformMatrix;
        };*/
};
