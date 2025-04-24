cd ..

@REM тесты для медианного фильтра
main images/lisa.jpg -median 10 tests/median1.jpg
main images/image.jpg -median 5 tests/median2.jpg
main images/cat.jpg -median 3 tests/median3.png

@REM тесты для Гауссова фильтра
main images/apple.jpg -gauss 10 2 tests/gauss1.jpg
main images/image.jpg -gauss 5 1 tests/gauss2.jpg
main images/apple.jpg -gauss 3 1 tests/gauss3.png

@REM тесты для Детектора границ Кэнни
main images/face.jpg -edges 10 2 tests/edges1.jpg
main images/image.jpg -edges 5 1 tests/edges2.jpg
main images/apple.jpg -edges 3 3 tests/edges3.png

@REM тесты для Маштабирования
main images/face.jpg -scale 0.5 tests/scale1.jpg
main images/image.jpg -scale 1.5 tests/scale2.jpg
main images/cat.jpg -scale 2 tests/scale3.png

@REM тесты для Увеличения резкости
main images/face.jpg -sharp tests/sharp1.jpg
main images/image.jpg -sharp tests/sharp2.jpg
main images/cat.jpg -sharp tests/sharp3.png

@REM тесты для Вращения изображения
main images/face.jpg -rotation L tests/rotation1.jpg
main images/image.jpg -rotation R tests/rotation2.jpg
main images/cat.jpg -rotation V tests/rotation3.png

@REM тесты для Отображения границ на изображении
main images/face.jpg -brd_on_img 10 2 tests/brd_on_img1.jpg
main images/image.jpg -brd_on_img 5 1 tests/brd_on_img2.jpg
main images/cat.jpg -brd_on_img 3 3 tests/brd_on_img3.png

@REM тесты для Морфинга
main images/apple.jpg images/fon.jpg -morph tests/morph1.jpg
main images/face2.jpg images/fon2.jpg -morph tests/morph2.jpg
main images/apple.jpg images/fon3.jpg -morph tests/morph3.png

cd scripts