#include "library.h"

//поворот на право
unsigned char* turn_right(unsigned char*img, int width, int height, int channels,unsigned char*new_img){

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){  
            for(int colour=0;colour<channels;colour++){
                new_img[(j*height+i)*channels+colour] = img[(i*width+j)*channels+colour];
            }
        }
    }

    return new_img;
}

//поворот на лево
unsigned char* turn_left(unsigned char*img, int width, int height, int channels,unsigned char*new_img){

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){  
            for(int colour=0;colour<channels;colour++){
                new_img[(j*height+i)*channels+colour] = img[(((height-1)-i)*width+j)*channels+colour];
            }
        }
    }

    return new_img;
}

//вертикальный поворот
unsigned char* turn_vertically(unsigned char*img, int width, int height, int channels,unsigned char*new_img){

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){  
            for(int colour=0;colour<channels;colour++){
                new_img[((height-1-i)*width+j)*channels+colour] = img[(i*width+j)*channels+colour];
            }
        }
    }

    return new_img;
}

unsigned char* image_rotation(unsigned char*img,int width,int height,int channels,char* side){

    //новое изображение
    unsigned char*new_img = (unsigned char*)malloc(width*height*channels);

    //обработка поворота на лево
    if(!strcmp(side,"L")){
        new_img = turn_left(img,width,height,channels,new_img);
    }
    //обработка поворота на право
    else if(!strcmp(side,"R")){
        new_img = turn_right(img,width,height,channels,new_img);
    }
    //обработка поворота на 180
    else if(!strcmp(side,"V")){
        new_img = turn_vertically(img,width,height,channels,new_img);
    }

    return new_img;
}