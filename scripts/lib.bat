cd ..
@REM создание динамической библеотеки
gcc -shared functions/Interpolation.c functions/Median_filter.c functions/Gaussian_filter.c functions/Canny_Edge_Detector.c functions/bord_on_img.c functions/Sharpening_Kernels.c functions/image_rotation.c functions/Scaling.c functions/morphing.c functions/library.h -o mylib.dll

@REM компиляция файла main.c с библеотекой
gcc main.c functions/library.h -L. -lmylib -o main

@REM удвление объектных файлов
del /s *.o
cd scripts