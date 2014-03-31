#ifndef _VECTOR4_H_
#define _VECTOR4_H_

// Structure used for graphics data

struct Vector4 {

    float x, y, z, w;

    Vector4() {}

    Vector4(float x, float y, float z, float w = 1.0f) {

        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

#endif // _VECTOR4_H_
