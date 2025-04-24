#include "library.h"

//функция для сравнения
int cmp(const void * x1, const void * x2){
    return ( *(int*)x1 - *(int*)x2 );
}
 
//функция применяющая медианный фильтр
int medi(int i,int j,int width, int channels, int colour, int size_of_kernel,unsigned char*img2,int new_width,int new_height){
    //массив для пикселей свёртки
    int arr[size_of_kernel*size_of_kernel];
    memset(arr,0,sizeof(arr));
    int ind=0;

    //заполнение массива пикселей свёртки
    for(int k = i; k<(i+size_of_kernel) &&k<new_height;k++){
        for(int h=j;h<(j+size_of_kernel);h++){
            arr[ind++] = img2[(k*new_width+h)*channels+colour];
        }
    }

    qsort(arr, size_of_kernel*size_of_kernel, sizeof(int), cmp);
    return arr[(size_of_kernel*size_of_kernel)/2];
}

unsigned char* Median_filter(unsigned char*img, int width,int height,int channels,int size_of_kernel){

    //dop_pix это кол-во пикселей на которое нужно евеличить изображение, чтобы коректно обрабатывать пиксели находящиеся по краям
    int dop_pix = size_of_kernel/2;
    //ширина с учётом dop_pix
    int new_width=width+dop_pix;
    //высота с учётом dop_pix
    int new_height = height+dop_pix;

    //увеличенное изображение
    unsigned char *img2 = Interpolation(img,width,height,channels,size_of_kernel,dop_pix,new_width,new_height);

    //применение фильтра
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int colour=0;colour<channels;colour++){
                img[(i*width+j)*channels + colour] = medi(i,j,width,channels,colour, size_of_kernel, img2, new_width, new_height);
            }
        }
    }   

    free(img2);
    return img;
}