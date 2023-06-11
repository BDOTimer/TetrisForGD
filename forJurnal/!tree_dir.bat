@echo off
rem Вывод списка файлов текущего каталога:-------
::dir /b/a-d >result.txt

::dir "%~1" /b /s /ad >result.txt
rem Вывод дерева каталогов:----------------------
tree /F /A >tree_dir.txt

goto ob
echo.путь до батника
echo %~dp0
echo.Путь к текущему каталогу
echo %CD%
echo.Путь к текущему каталогу с завершающим обратным слешем
echo %__CD__%
rem Присваиваем переменной текуший каталог:------
set  oldipforsite=%~dp0
:ob

echo Смотри файл result.txt в текущем каталоге %cd%

::For /D %%a In ("%oldipforsite:~0,-1%.txt") Do Set oldipforsite=%%~na
::Echo %oldipforsite%


pause