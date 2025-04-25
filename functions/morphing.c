#include "library.h"

/** @brief функция проверяет является ли пиксель частью границы или нет
 * 
 * @param brd_img границы объекта
 * @param i расположение пикселя по высоте
 * @param j расположение пикселя по ширине
 * @param width ширина изображения
 * @param channels кол-во каналов изображения
 * 
 * @return int 0 если граница, иначе 1
 */
int check_brd(unsigned char*brd_img,int i,int j,int width,int channels){

    int count=0;

    for(int colour=0;colour<channels;colour++){
        if(brd_img[(i*width+j)*channels+colour]==0)count++;
    }
    if(count==3)return 1;
    return 0;

}

/**
 * @brief наложение фона на пиксели находящиеся в границах объекта
 * 1 поиск границ предмета
 * 2 наложение фона на пиксели находящиеся в границах объекта
 * 
 * @param img основное изображение
 * @param img2 фоновое изображение
 * @param width ширина основного изображения
 * @param height ширина основного изображения
 * @param channels кол-во каналов основного изображения
 * @param width2 ширина фонового изображения
 * @param height2 ширина фонового изображения
 * @param channels2 кол-во каналов фонового изображения
 * 
 * @return указатель на новое изображение
 * 
 * @warning работате с изображениями на которых один объект 
 */

unsigned char* Morphing(unsigned char*img,unsigned char*img2,int width,int height,int channels,int width2,int height2,int channels2 ){

    //границы объекта
    unsigned char*brd_img = Canny_Edge_Detector(img,width,height,channels, 5,5);

    //новое изображение
    unsigned char*new_img = (unsigned char*)malloc(width*height*channels);

    //если изображение с фоном меньше изображения с объектом, то изображение с фоном увеличивается
    if(width2<width || height2<height){
        float scale =1;
        while((width2*scale)<width || (height2*scale)<height){
            scale+=0.5;
        }
        img2 = Scaling(img2,width2,height2,channels2,scale);
        width2=(int)(width2*scale);
        height2=(int)(height2*scale);
    }

    //наложение фона на пиксели фходящие в границы объекта
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int count=0;
            for(int colour=0;colour<channels;colour++){
                if(brd_img[(i*width+j)*channels+colour]==0)count++;
            }
            if(count==3){
                for(int colour=0;colour<channels;colour++){
                    new_img[(i*width+j)*channels+colour] = img[(i*width+j)*channels+colour];
                }
            }
            else{
                for(int colour=0;colour<channels;colour++){
                    new_img[(i*width+j)*channels+colour] = img[(i*width+j)*channels+colour];
                }

                int h=j+1;
                int k=i;
                int sig=0;

                while(check_brd(brd_img,k,h,width,channels) && h<width){
                    if(h<width-1)h++;
                    else{
                        sig=1;
                        break;
                    }
                }
                if(!sig){

                    for(;j<h;j++){
                        for(int colour=0;colour<channels;colour++){
                            new_img[(i*width+j)*channels+colour] = (int)(img2[(i*width2+j)*channels2+colour]*0.5)+(int)(img[(i*width+j)*channels+colour]*0.5);
                        }
                    }
                    j=j-1;
                }
                else{
                    for(;j<h;j++){
                        for(int colour=0;colour<channels;colour++){
                            new_img[(i*width+j)*channels+colour] = img[(i*width+j)*channels+colour];
                        }
                    }
                }

            }
        }
    }
    //очистка памяти
    free(brd_img);

    return new_img;
}