#include "library.h"

//применение оператора Собеля
int horizontal_and_vertical(unsigned char* img2, int new_width, int channels, int colour, int i, int j, int new_height,unsigned char*arr_of_corner,int width ){

    //горизонтальная маска
    int kernelH[3][3]={
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    //вертикальная маска
    int kernelV[3][3]={
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };
    int X=0;
    int Y=0;

    //применение масок
    for(int k=i;k<i+3 && k<new_height;k++){
        for(int h=j;h<j+3;h++){
            X+=(img2[(k*new_width+h)*channels+colour]*kernelH[k-i][h-j]);
            Y+=(img2[(k*new_width+h)*channels+colour]*kernelV[k-i][h-j]);
        }
    }

    //заполнение массива с направлениями векторов пикселей
    if(X==0) arr_of_corner[i*width+j+colour] = atan(0);
    else arr_of_corner[i*width+j+colour] = atan(Y/X)*57.3;


    int gradient = sqrt(X*X+Y*Y);
    if(gradient>255)gradient=255;

    return gradient;
}

//проверяет значения пикселей(сверху, справа, слева, снизу)
int checking_the_nearest_ones(unsigned char* imgX, int i, int j, int width,int height, int channels, int colour, int* max_colour){
    if(i == 0 && j == 0){
        if(imgX[(i*width+j)*channels+colour]==max_colour[colour] || imgX[((i+1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(i==0 && j == (width-1)){
        if(imgX[((i+1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j-1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(i==0){
        if(imgX[((i+1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else if(imgX[(i*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j-1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(j==0 && i==(height-1)){
        if(imgX[((i-1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(j==0){
        if(imgX[((i+1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else if(imgX[((i-1)*width+(j))*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(i==(height-1) && j==(width-1)){
        if(imgX[((i-1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[(i*width+(j-1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(i==(height-1)){
        if(imgX[((i-1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else if(imgX[((i)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i)*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(j==(width-1)){
        if(imgX[((i-1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i)*width+(j-1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else if(imgX[((i+1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        if(imgX[((i-1)*width+j)*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i)*width+(j-1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else if(imgX[((i+1)*width+(j-1))*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j))*channels+colour]==max_colour[colour] || imgX[((i+1)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[((i)*width+(j+1))*channels+colour]==max_colour[colour] || imgX[((i-1)*width+(j+1))*channels+colour]==max_colour[colour]){
            return 1;
        }
        else{
            return 0;
        }
    }
}

unsigned char* Canny_Edge_Detector(unsigned char*img, int width, int height, int channels, int size_of_kernel,int square_of_devation){

    //dop_pix это кол-во пикселей на которое нужно евеличить изображение, чтобы коректно обрабатывать пиксели находящиеся по краям
    int dop_pix = size_of_kernel/2;
    //ширина с учётом dop_pix
    int new_width = width+dop_pix;
    //высота с учётом dop_pix
    int new_height = height+dop_pix;

    //изображение с применёным гауссовым размытием
    unsigned char* img2 = Gaussian_filter(img,width,height,channels,size_of_kernel,square_of_devation);
    //увеличенное изображение с применёным гауссовым размытием
    unsigned char* expanded_img = Interpolation(img2,width,height,channels,3,1,new_width,new_height);

    unsigned char*imgX = (unsigned char*)malloc(width*height*channels);
    //массив, который хранит направление вектора для каждого пикселя
    unsigned char*arr_of_corner = (unsigned char*)malloc(width*height*channels);

    //применение оператора Собеля
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int colour=0;colour<channels;colour++){
                imgX[(i*width+j)*channels+colour] = horizontal_and_vertical(expanded_img, new_width, channels, colour, i ,j,new_height,arr_of_corner,width);
            }
        }
    }

    //массив для хранения максимальных значений каналлов
    int max_colour[channels];
    memset(max_colour,0,sizeof(channels));

    //подавление немаксимумов
    for(int i=1;i<height-1;i++){
        for(int j=1;j<width-1;j++){
            for(int colour=0;colour<channels;colour++){
                double per = arr_of_corner[i*width+j+colour];
                if((per<5 && per>-5) || (per>175 && per<185) || (per>175 && per<185) || (per<-175 && per>-185) || (per>360 && per<365 )){
                    if(imgX[(i*width+j)*channels+colour]<imgX[(i*width+j+1)*channels+colour] || imgX[(i*width+j)*channels+colour]<imgX[(i*width+j-1)*channels+colour]){
                        imgX[(i*width+j)*channels+colour] = 0;
                    }
                }
                else if((per>85 && per<95) || (per>265 && per<275) || (per<-265 && per>-275)){
                    if(imgX[(i*width+j)*channels+colour]<imgX[((i+1)*width+j)*channels+colour] || imgX[((i-1)*width+j)*channels+colour]){
                        imgX[(i*width+j)*channels+colour] = 0;
                    }
                }

                if(imgX[(i*width+j)*channels+colour]> max_colour[colour]) max_colour[colour] = imgX[(i*width+j)*channels+colour];

            }
        }
    }

    //массив для хранения верхнего порога каналов
    int upper_threshold[channels];

    //массив для хранения нижнего порога каналов
    int lower_threshold[channels];

    //заполнение массивов с порогами
    for(int i=0;i<channels;i++){
        if(max_colour[i]>255){
            upper_threshold[i] = 255*0.25;
            lower_threshold[i] = 255*0.15;
        }
        else{
            upper_threshold[i] = max_colour[i]*0.25;
            lower_threshold[i] = max_colour[i]*0.15;
        }
    }

    //применение двойной пороговой фильтрации
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int colour=0;colour<channels;colour++){
                if(imgX[(i*width+j)*channels+colour]>upper_threshold[colour]){
                    imgX[(i*width+j)*channels+colour] = max_colour[colour];
                }
                else if(imgX[(i*width+j)*channels+colour]<lower_threshold[colour]){
                    imgX[(i*width+j)*channels+colour] = 0;
                }
                else{
                    imgX[(i*width+j)*channels+colour] = (max_colour[colour]*0.5);
                }
            }
        }
    }

    //трассировка области неоднозначности
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int colour=0;colour<channels;colour++){  
                if(imgX[(i*width+j)*channels+colour] == (int)(max_colour[colour]*0.5)){
                    if(!checking_the_nearest_ones(imgX, i,j,width,height,channels,colour,max_colour)){
                        imgX[(i*width+j)*channels+colour] = 0;
                    }
                    else{
                        imgX[(i*width+j)*channels+colour] = max_colour[colour];
                    }
                }
            }
        }
    }

    //очистка памяти
    free(expanded_img);
    free(arr_of_corner);
    free(img2);

    return imgX;
}