#ifndef SURFTEXTH
#define SURFTEXTH

#include "texture.h"

class image_texture : public texture {
    public:
        image_texture() {}
        image_texture(unsigned char *pixels, int A, int B) : data(pixels), nx(A), ny(B) {}
                virtual vec3 value(float u, float v, const vec3& p) const;
        unsigned char *data;
        int nx, ny;
};

vec3 image_texture::value(float u, float v, const vec3& p) const {
     int i = (  u)*nx;
     int j = (1-v)*ny-0.001;
     if (i < 0) i = 0;
     if (j < 0) j = 0;
     if (i > nx-1) i = nx-1;
     if (j > ny-1) j = ny-1;
     float r = int(data[3*i + 3*nx*j]  ) / 255.0;
     float g = int(data[3*i + 3*nx*j+1]) / 255.0;
     float b = int(data[3*i + 3*nx*j+2]) / 255.0;
     return vec3(r, g, b);
}

#endif
