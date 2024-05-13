# ReedPlayer-Clover
Nintendo SNES Classic Mini. Clover Launcher

# Это не законченный код!
Это только начало, которое никак не может начаться.
Для успешной компиляции нужны библиотеки:
- mingw32
- SDL2
- SDL2_mixer
- Opengl32
- FreeImage
- jsoncpp

Для запуска нужны файлы оригинального образа SNES Classic Mini, а именно директория "usr\share\ui\snes-eur" со всем содержимым.
Параметры запуска

ReedPlayer-Clover.exe --language=en_USA --region=EUR --bootapp=usr\share\ui\snes-eur

--bootapp: Это путь где у вас нахдятся файлы оригинального образа.
