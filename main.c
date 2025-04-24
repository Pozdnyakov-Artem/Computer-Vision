#include "functions/library.h"


//функция для проверки существования файла
int check_file(char*filename){
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}

//функция, которая проверяет является ли строка целым числом или нет
int is_digit(char*str){
    char *endptr;
    long num = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    return 1;
}

//функция, которая проверяет является ли строка дробным числом или нет
int is_float(char*str){
    char*endptr;
    float num = strtof(str,&endptr);
    if(endptr == str || *endptr!='\0'){
        return 0;
    }
    return 1;
}

//функция для проверки коректности направления вращения
int is_side(char*str){
    if(!strcmp(str,"L") || !strcmp(str,"R") || !strcmp(str,"V")){
        return 1;
    }
    return 0;
}

//функциия для проверки существования вызываемой операции
int check_operation(char*str){
    if(!strcmp(str,"-median") || !strcmp(str,"-gauss") || !strcmp(str,"-edges")){
        return 1;
    }
    else if(!strcmp(str,"-brd_on_img") || !strcmp(str,"-sharp") || !strcmp(str,"-rotation")){
        return 1;
    }
    else{
        return 0;
    }
}
//функция для преобразования строки в целое число
int str_to_int(char*str){
    return strtol(str,0,10);
}

//функция для сохранения изображения в png
int save_img_png(char*file_path, int width, int height, int channels, unsigned char* new_img){
    if (!stbi_write_png(file_path, width, height, channels, new_img, width*channels)) {
        printf("Saving error PNG!\n");
    } else {
        printf("The file was saved successfully: %s\n", file_path);
    }
}

//функция для сохранения изображения в jpg
int save_img_jpg(char*file_path, int width, int height, int channels, unsigned char* new_img){
    if (!stbi_write_jpg(file_path, width, height, channels, new_img, 100)) {
        printf("Saving error JPG!\n");
    } else {
        printf("The file was saved successfully: %s\n", file_path);
    }
}

//функция определяющая формат сохраняемого изображения и вызывающая функцию для созхранения
int save_img(char*str,int width,int height, int channels,unsigned char* new_img){
    int len = strlen(str);

    if(str[len-4]=='.' && str[len-3]=='p' && str[len-2]=='n' && str[len-1]=='g'){
        save_img_png(str,width,height,channels,new_img);
    }
    else if(str[len-4]=='.' && str[len-3]=='j' && str[len-2]=='p' && str[len-1]=='g'){
        save_img_jpg(str,width,height,channels,new_img);
    }
    else{
        printf("unsupported save format\n");
    }
}


int main(int argc, char* argv[]){
    //обработка функций с 6 аргументами
    if(argc==6){
        //ширина, высота, кол-во каналов
        int width, height, channels;
        //считываем поступившее на вход изображение
        unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);

        /*обработка изображений с входными данными типа:
            * argv[1] = input.file
            * argv[2] = операция
            * argv[3] = длина стороны ядра свёртки
            * argv[4] = сигма для Гауссова размытия(влияет на силу размытия)
            * argv[5] = имя для обработанного изображения
        */
        if(check_file(argv[1]) && check_operation(argv[2]) && is_digit(argv[3]) && is_digit(argv[4])){
            //обработка вызова Гауссова фильтра
            if(!strcmp(argv[2],"-gauss")){
                unsigned char* new_img = Gaussian_filter(img,width,height,channels,str_to_int(argv[3]),str_to_int(argv[4]));
                save_img(argv[5],width,height,channels,new_img);
                //читска памяти
                free(new_img);
            }
            //обработка вызова определения границ
            else if(!strcmp(argv[2],"-edges")){
                unsigned char* new_img = Canny_Edge_Detector(img,width,height,channels,str_to_int(argv[3]),str_to_int(argv[4]));
                save_img(argv[5],width,height,channels,new_img);
                //читска памяти
                free(new_img);
            }
            //обработка вызова отображения границ на изображении
            else if(!strcmp(argv[2],"-brd_on_img")){
                unsigned char* new_img = bord_on_img(img,width,height,channels,str_to_int(argv[3]),str_to_int(argv[4]));
                save_img(argv[5],width,height,channels,new_img);
                //читска памяти
                free(new_img);
            }
        }
        //чистка памяти
        stbi_image_free(img);

    }
    else if(argc == 5){
        /*обработка морфинга с входными данными:
            * argv[1] = input.file
            * argv[2] = фон для заливки
            * argv[3] = операция
            * argv[4] = имя для обработанного изображения
        */
        if(check_file(argv[1]) && check_file(argv[2]) && !strcmp(argv[3],"-morph")){
            //ширина, высота, кол-во каналов основного изображения
            int width, height, channels;
            //считываем основное изображение поступившее на вход изображение
            unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);

            //ширина, высота, кол-во каналов фона фонового изображения
            int width2, height2, channels2;
            //считываем фоновое изображение поступившее на вход изображение
            unsigned char *img2 = stbi_load(argv[2], &width2, &height2, &channels2, 0);

            unsigned char*new_img = Morphing(img,img2,width,height,channels,width2,height2,channels2);

            save_img(argv[4],width,height,channels,new_img);

            //чистка памяти
            free(new_img);
            stbi_image_free(img);
            stbi_image_free(img2);
        }
        /*обработка медианного фильтра с входными данными:
            * argv[1] = input.file
            * argv[2] = операция
            * argv[3] = длина стороны ядра свёртки
            * argv[4] = имя для обработанного изображения
        */
        else if(check_file(argv[1]) && check_operation(argv[2]) &&is_digit(argv[3]) && !strcmp(argv[2],"-median")){
            //ширина, высота, кол-во каналов
            int width, height, channels;
            //считываем поступившее на вход изображение
            unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);

            unsigned char* new_img = Median_filter(img,width,height,channels,str_to_int(argv[3]));
            save_img(argv[4],width,height,channels,new_img);

            //читска памяти
            free(new_img);
            stbi_image_free(img);
        }
        /*обработка вращения изображения с входными данными:
            * argv[1] = input.file
            * argv[2] = операция
            * argv[3] = направление вращения
            * argv[4] = имя для обработанного изображения
        */
        else if(check_file(argv[1]) && check_operation(argv[2]) &&is_side(argv[3]) && !strcmp(argv[2],"-rotation")){

            //ширина, высота, кол-во каналов
            int width, height, channels;
            //считываем поступившее на вход изображение
            unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);

            unsigned char*new_img = image_rotation(img,width,height,channels,argv[3]);

            if(!strcmp(argv[3],"V")) save_img(argv[4],width,height,channels,new_img);
            else save_img(argv[4],height,width,channels,new_img);

            //читска памяти
            free(new_img);
            stbi_image_free(img);
        }
        /*обработка масштабирования изображения с входными данными:
            * argv[1] = input.file
            * argv[2] = операция
            * argv[3] = значение определяющее во сколько раз нужно увеличить изображение
            * argv[4] = имя для обработанного изображения
        */
        else if(!strcmp(argv[2],"-scale") && check_file(argv[1]) &&is_float(argv[3])){
            //ширина, высота, кол-во каналов
            int width, height, channels;
            //считываем поступившее на вход изображение
            unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
            float scale = strtof(argv[3],0);
            unsigned char*new_img = Scaling(img,width,height,channels,scale);

            save_img(argv[4],(int)width*scale,(int)height*scale,channels,new_img);

            //читска памяти
            free(new_img);
            stbi_image_free(img);
        }
        //обработка некоректного запроса
        else{
            printf("uncorrected request\n");
        }
    }
    /*обработка увеличения резкости изображения с входными данными:
            * argv[1] = input.file
            * argv[2] = операция
            * argv[3] = имя для обработанного изображения
    */
    else if(argc == 4){
        if(check_file(argv[1]) && check_operation(argv[2])){

            int width, height, channels;
            unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);

            if(!strcmp(argv[2],"-sharp")){
                unsigned char* new_img = Sharpening_Kernels(img,width,height,channels);
                save_img(argv[3],width,height,channels,new_img);
                free(new_img);
            }

            stbi_image_free(img);
        }
        //обработка некоректного запроса
        else{
            printf("uncorrected request\n");
        }
    }
    //обработка некоректного запроса
    else{
        printf("uncorrected request\n");
    }

    return 0;
}