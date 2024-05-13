# ReedPlayer-Clover
Nintendo SNES Classic Mini. Clover Launcher

Попытка написать с нуля лаунчер "Clover". Это типа порт для использования на всяких RaspberryPi. На данном этапе происходит парсинг json файлов, создаётся основная структура элементов и их рендеринг. 
В идеале, дальше надо разбираться как работают Lua скрипты и как приложение с ними взаимоействует.

Идея приложения - не пытаться маскироваться под Clover используя его спрайты, а именно быть таким же как оригинальный Clover и работать с его оригильными файлами, так же как это делает оригинал.

### На текущий момент оно играет музыку домашнего экрана и выглядит вот так: 

![](images/example%20screen.png)

Я не питаю илюзии, что у меня это получится. Скорее всего этот репозиторий так и останется без изменений. Однако, если Вам это интересно, и Вы можете помочь, - буду рад.

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

В репозитории находится [usr.zip](usr.zip) архив, в которой находится нужное содержимое, но без игр.

Также есть [lua_scripts_decode.zip](lua_scripts_decode.zip) архив, содержащий декомпилированные оригинальные Lua скрипты.

Параметры запуска

ReedPlayer-Clover.exe --language=en_USA --region=EUR --bootapp=usr\share\ui\snes-eur

--bootapp: Это путь где у вас нахдятся файлы оригинального образа.
