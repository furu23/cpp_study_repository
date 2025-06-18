#pragma once
#include <cmath>

struct vector3{
    float x, y, z;
    vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_){}
    
    float magnificant(){
        return sqrtf(powf(x, 2) + pow(y, 2) + powf(z, 2));
    }

    vector3 nomalize(){
        float mag = magnificant();
        if (mag != 0){
            return vector3(x / mag, y / mag, z / mag);
        }
        return vector3(0.0, 0.0, 0.0);
    }

    static float dot(const vector3& a, const vector3& b){
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static vector3 cross(const vector3& a, const vector3& b){
        return vector3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    vector3 operator-(const vector3& other) const{
        return vector3(x - other.x, y - other.y, z - other.z);
    }
};
