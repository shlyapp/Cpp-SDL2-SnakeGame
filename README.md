# Cpp-SDL2-SnakeGame

Ремейк классической игры "Змейка", созданный на C++ с использованием SDL2.

Функиональность:
- Меню с выбором
- Просмотр рекордов

Правила игры:
- Управление стрелками
- Красное яблоко +1 очко
- Синее яблоко +5 очков
- У карты нет границ
- Игра начиается сначала, если змейка врезалась в себя

Инструкция по установке:
1. Переходим по ссылке https://github.com/libsdl-org/SDL_ttf/releases и скачиваем версию (2.20.1), файл `SDL2_ttf-devel-2.20.1-VC.zip`
2. Распаковываемый файл в удобное место
   (в моем случае `C:\Users\shlyapp\Documents\libraries`)
3. В Visual Studio открываем решением, в верхней панели `Проект > Свойства`
4. Выбираем платформу (x64)
5. Вкладка `C/C++ > Общие > Дополнительные каталоги включаемых файлов` добавляем путь до папки `include`
   (в моем случае `C:\Users\shlyapp\Documents\libraries\SDL2_ttf-2.20.1\include`)
6. Вкладка `Компоновщик > Общие > Дополнительных каталоги библиотек` добавляем путь до папки `lib\x64`
   (в моем случае `C:\Users\shlyapp\Documents\libraries\SDL2_ttf-2.20.1\lib\x64`)
7. Вкладка `Ввод > Дополнительные зависимости`, добавляем `SDL2_ttf.lib`
8. Переносим файл `lib\x64\SDL2_ttf.dll` в папку с решением

![demo](https://user-images.githubusercontent.com/78727203/211174830-434890e8-0833-45ac-a00e-1faeeb793641.gif)
