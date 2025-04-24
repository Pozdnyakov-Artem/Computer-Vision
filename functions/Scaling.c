#include "library.h"

//сплайн Catmull-Rom
float Catmull_Rom(float t){

    float t_abs = fabs(t);
    if (t_abs <= 1.0f) {
        return 1.5f * t_abs * t_abs * t_abs - 2.5f * t_abs * t_abs + 1.0f;
    } else if (t_abs < 2.0f) {
        return -0.5f * t_abs * t_abs * t_abs + 2.5f * t_abs * t_abs - 4.0f * t_abs + 2.0f;
    }

    return 0.0f;
}

//бикубическая интерполяция
float bic_interpolate(unsigned char*img,float i, float j, int width,int height,int colour,int channels){

    int f_i = (int)i;
    int f_j = (int)j;

    float di = i - f_i;
    float dj = j - f_j;

    float res=0;

    for(int k=-1;k<3;k++){
        for(int h=-1;h<3;h++){
            int pi = f_i + k;
            int pj = f_j + h;

            if(pj<0)pj=0;
            if(pi<0)pi=0;
            if(pi>=height)pi=height-1;
            if(pj>width)pj=width-1;

            float weight_i = Catmull_Rom(di-k);
            float weight_j = Catmull_Rom(dj-h);

            res+=img[(pi*width+pj)*channels+colour]*weight_i*weight_j;
        }
    }

    if(res>255)res=255;
    if(res<0)res=0;

    return res;

}

unsigned char* scale(unsigned char*img,int new_width,int new_height,int channels,float magnification_size,int width,int height){

    unsigned char*new_img = (unsigned char*)malloc(new_width*new_height*channels);

    //применение бикубической интерполяции
    for(int i=0;i<new_height;i++){
        for(int j=0;j<new_width;j++){
            float src_i = i/magnification_size;
            float src_j = j/magnification_size;
            for(int colour=0;colour<channels;colour++){
                new_img[(i*new_width+j)*channels+colour] =bic_interpolate(img,src_i,src_j,width,height,colour,channels);
            }
        }
    }

    return new_img;
}

unsigned char* Scaling(unsigned char*img,int width,int height,int channels,float magnification_size){

    //новая ширина
    int new_width=(int)width*magnification_size;
    //новая высота
    int new_height = (int)height*magnification_size;
    //новое изображение
    unsigned char*new_img = scale(img,new_width,new_height,channels,magnification_size,width,height);

    return new_img;
}