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

class Vector2{
    public:
        float x, y;
        Vector2(float x = 0, float y = 0){
            this->x = x;
            this->y = y;
        }
        
        Vector2 operator + (Vector2 other){
            return Vector2(this->x + other.x, this->y + other.y);
        }
        
        Vector2 operator - (Vector2 other){
            return Vector2(this->x - other.x, this->y - other.y);
        }
        
        Vector2 operator * (double other){
            return Vector2(this->x * other, this->y * other);
        }
        
        Vector2 operator / (double other){
            return Vector2(this->x / other, this->y / other);
        }
        
        double magnitude(){
            return sqrt((this->x * this->x) +
                        (this->y * this->y));
        }
        
        Vector2 normalize(){
            double d = this->magnitude();
            if(d != 0){
                this->x /= d;
                this->y /= d;
            }
            return *this;
        }
        
        double dot(Vector2 other){
            return this->x * other.x +
                   this->y * other.y;
        }
        
        Vector2 cross(){
            return Vector2(this->y, -this->x);
        }
        
        Vector2 project(Vector2 other){
            Vector2 n = other.normalize();
            return n*this->dot(n);
        }
};

class Matrix4{
    public:
        float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
        
        Matrix4(){
            
        }
        
        Matrix4 operator * (Matrix4 other){
            double Aa = this->a;
            double Ab = this->b;
            double Ac = this->c;
            double Ad = this->d;
            double Ae = this->e;
            double Af = this->f;
            double Ag = this->g;
            double Ah = this->h;
            double Ai = this->i;
            double Aj = this->j;
            double Ak = this->k;
            double Al = this->l;
            double Am = this->m;
            double An = this->n;
            double Ao = this->o;
            double Ap = this->p;
            
            double Ba = other.a;
            double Bb = other.b;
            double Bc = other.c;
            double Bd = other.d;
            double Be = other.e;
            double Bf = other.f;
            double Bg = other.g;
            double Bh = other.h;
            double Bi = other.i;
            double Bj = other.j;
            double Bk = other.k;
            double Bl = other.l;
            double Bm = other.m;
            double Bn = other.n;
            double Bo = other.o;
            double Bp = other.p;
            
            Matrix4 c = Matrix4();
            c.a = Aa * Ba + Ab * Be + Ac * Bi + Ad * Bm;
            c.b = Aa * Bb + Ab * Bf + Ac * Bj + Ad * Bn;
            c.c = Aa * Bc + Ab * Bg + Ac * Bk + Ad * Bo;
            c.d = Aa * Bd + Ab * Bh + Ac * Bl + Ad * Bp;
            c.e = Ae * Ba + Af * Be + Ag * Bi + Ah * Bm;
            c.f = Ae * Bb + Af * Bf + Ag * Bj + Ah * Bn;
            c.g = Ae * Bc + Af * Bg + Ag * Bk + Ah * Bo;
            c.h = Ae * Bd + Af * Bh + Ag * Bl + Ah * Bp;
            c.i = Ai * Ba + Aj * Be + Ak * Bi + Al * Bm;
            c.j = Ai * Bb + Aj * Bf + Ak * Bj + Al * Bn;
            c.k = Ai * Bc + Aj * Bg + Ak * Bk + Al * Bo;
            c.l = Ai * Bd + Aj * Bh + Ak * Bl + Al * Bp;
            c.m = Am * Ba + An * Be + Ao * Bi + Ap * Bm;
            c.n = Am * Bb + An * Bf + Ao * Bj + Ap * Bn;
            c.o = Am * Bc + An * Bg + Ao * Bk + Ap * Bo;
            c.p = Am * Bd + An * Bh + Ao * Bl + Ap * Bp;
            
            return c;
        }
};
