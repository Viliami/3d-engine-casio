#pragma once
#include <math.h>

class Vector3{
    public:
        double x, y, z;
        Vector3(double x = 0, double y = 0, double z = 0){
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        Vector3 operator + (Vector3 other){
            return Vector3(this->x + other.x,
                           this->y + other.y,
                           this->z + other.z);
        }
        
        Vector3 operator - (Vector3 other){
            return Vector3(this->x - other.x,
                           this->y - other.y,
                           this->z - other.z); 
        }
        
        Vector3 operator * (Vector3 other){
            return Vector3(this->x * other.x,
                           this->y * other.y,
                           this->z * other.z);
        }
        
        Vector3 operator / (Vector3 other){
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
        double x, y;
        Vector2(double x = 0, double y = 0){
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
        double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
        
        Matrix4(){
            this->identity();
        }
        
        Matrix4 identity(){
            this->a = this->f = this->k = this->p = 1.0;
            this->b = this->c = this->d = this->e = this->g = this->h = this->i = this->j = this->l = this->m = this->n = this->o = 0;
            return *this;
        }
        
        Matrix4 new_identity(){
            return Matrix4();
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
        
        Vector3 operator * (Vector3 b){
            Matrix4 a = *this;
            Vector3 v = Vector3(0,0,0);
            v.x = a.a * b.x + a.b * b.y + a.c * b.z;
            v.y = a.e * b.x + a.f * b.y + a.g * b.z;
            v.z = a.i * b.x + a.j * b.y + a.k * b.z;
            return v;
        }
        
        Matrix4 multiply(Matrix4 other){
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
        
        Matrix4 new_rotatex(double angle){
            Matrix4 a = *this;
            double s = sin(angle);
            double c = cos(angle);
            a.f = a.k;
            a.k = c;
            a.g = -s;
            a.j = s;
            return a;
        }
        
        Matrix4 new_rotatey(double angle){
            Matrix4 a = *this;
            double s = sin(angle);
            double c = cos(angle);
            a.a = a.k;
            a.k = c;
            a.c = s;
            a.i -s;
            return a;
        }
        
        Matrix4 new_rotatez(double angle){
            Matrix4 a = *this;
            double s = sin(angle);
            double c = cos(angle);
            a.a = a.f;
            a.f = c;
            a.b  = -s;
            a.e = s;
            return a;
        }
        
        Matrix4 new_rotate_axis(double angle, Vector3 axis){
            Vector3 vector = axis.normalize();
            double x = vector.x;
            double y = vector.y;
            double z = vector.z;
            double s = sin(angle);
            double c = cos(angle);
            Matrix4 a = *this;
            double c1 = 1.0 - c;
            
            a.a = x * x * c1 + c;
            a.b = x * y * c1 - z * s;
            a.c = x * z * c1 + y * s;
            a.e = y * x * c1 + z * s;
            a.f = y * y * c1 + c;
            a.g = y * z * c1 - x * s;
            a.i = x * z * c1 - y * s;
            a.j = y * z * c1 + x * s;
            a.k = z * z * c1 + c;
            return a;
        }
        
        Matrix4 new_rotate_euler(double heading, double attitude, double bank){
            double ch = cos(heading);
            double sh = sin(heading);
            double ca = cos(attitude);
            double sa = sin(attitude);
            double cb = cos(bank);
            double sb = sin(bank);
            
            Matrix4 a = *this;
            a.a = ch * ca;
            a.b = sh * sb - ch * sa * cb;
            a.c = ch * sa * sb + sh * cb;
            a.e = sa;
            a.f = ca * cb;
            a.g = -ca * sb;
            a.i = -sh * ca;
            a.j = sh * sa * cb + ch * sb;
            a.k = -sh * sa * sb + ch * cb;
            return a;
        }
        
        Matrix4 new_rotate_triple_axis(Vector3 x, Vector3 y, Vector3 z){
            Matrix4 a = *this;
            a.a = x.x;
            a.b = y.x;
            a.c = z.x;
            a.e = x.y;
            a.f = y.y;
            a.g = z.y;
            a.i = x.z;
            a.j = y.z;
            a.k = z.z;
            return a;
        }
        
        Matrix4 new_look_at(Vector3 eye, Vector3 at, Vector3 up){
            Vector3 z = (eye - at).normalize();
            Vector3 x = up.cross(z).normalize();
            Vector3 y = z.cross(x);
            Matrix4 a = Matrix4().new_rotate_triple_axis(x, y, z);
            a.d = eye.x;
            a.h = eye.y;
            a.l = eye.z;
            return a;
        }
        
        Matrix4 new_perspective(double fov_y, double aspect, double near, double far){
            float f = 1.0 / tan(fov_y/2.0);
            Matrix4 a = *this;
            if(near != 0.0 && near != far){
                a.a = f / aspect;
                a.f = f;
                a.k = (far + near) / (near - far);
                a.l = 2 * far * near / (near - far);
                a.o = -1;
                a.p = 0;
            }
            return a;
        }
        
        Matrix4 new_translate(double x, double y, double z){
            Matrix4 a = *this;
            a.d = x;
            a.h = y;
            a.l = z;
            return a;
        }
        
        Matrix4 rotatex(double angle){
            *this = *this * Matrix4().new_rotatex(angle);
            return *this;
        }
        
        Matrix4 rotatey(double angle){
            *this = *this * Matrix4().new_rotatey(angle);
            return *this;
        }
        
        Matrix4 rotatez(double angle){
            *this = *this * Matrix4().new_rotatez(angle);
            return *this;
        }
        
        Matrix4 rotate_axis(double angle, Vector3 axis){
            *this = *this * Matrix4().new_rotate_axis(angle, axis);
            return *this;
        }
        
        Matrix4 rotate_euler(double heading, double attitude, double bank){
            *this = *this * Matrix4().new_rotate_euler(heading, attitude, bank);
            return *this;
        }
        
        Vector3 transform(Vector3 other){
            Matrix4 a = *this;
            Vector3 b = other;
            Vector3 p = Vector3(0,0,0);
            p.x = a.a * b.x + a.b * b.y + a.c * b.z + a.d;
            p.y = a.e * b.x + a.f * b.y + a.g * b.z + a.h;
            p.z = a.i * b.x + a.j * b.y + a.k * b.z + a.l;
            double w = a.m * b.x + a.n * b.y + a.o * b.z + a.p;
            
            if(w != 0){
                p.x /= w;
                p.y /= w;
                p.z /= w;
            }
            return p;
        }
        
        Matrix4 translate(double x, double y, double z){
            *this = Matrix4().new_translate(x, y, z);
            return *this;
        }
};
