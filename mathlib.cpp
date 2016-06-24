#include <math.h>

class Vector3{
    public:
        float x, y, z;
        Vector3(float x = 0, float y = 0, float z = 0){
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        Vector3 operator+(Vector3 other){
            return Vector3(this->x + other.x,
                           this->y + other.y,
                           this->z + other.z);
        }
        
        Vector3 operator-(Vector3 other){
            return Vector3(this->x - other.x,
                           this->y - other.y,
                           this->z - other.z); 
        }
        
        Vector3 operator*(Vector3 other){
            return Vector3(this->x * other.x,
                           this->y * other.y,
                           this->z * other.z);
        }
        
        Vector3 operator/(Vector3 other){
            return Vector3(this->x / other.x,
                           this->y / other.y,
                           this->z / other.z);
        }
        
        double magnitude(){
            return sqrt((this->x * this->x) +
                        (this->y * this->y) +
                        (this->z * this->z));
        }
        
        Vector3 normalize(){
            double d = this->magnitude();
            if(d != 0){
                this->x /= d;
                this->y /= d;
                this->z /= d;
            }
            return *this;
        }
        
        Vector3 dot(Vector3 other){
            return this->x * other.x +
                   this->y * other.y +
                   this->z * other.z;
        }
        
        Vector3 cross(Vector3 other){
            return Vector3(this->y * other.z - this->z * other.y,
                           this->z * other.x - this->x * other.z,
                           this->x * other.y - this->y * other.x);
        }
        
        Vector3 project(Vector3 other){
            Vector3 n = other.normalize();
            return this->dot(n)*n;
        }
};
