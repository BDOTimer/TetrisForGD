@echo off
rem �뢮� ᯨ᪠ 䠩��� ⥪�饣� ��⠫���:-------
::dir /b/a-d >result.txt

::dir "%~1" /b /s /ad >result.txt
rem �뢮� ��ॢ� ��⠫����:----------------------
tree /F /A >tree_dir.txt

goto ob
echo.���� �� ��⭨��
echo %~dp0
echo.���� � ⥪�饬� ��⠫���
echo %CD%
echo.���� � ⥪�饬� ��⠫��� � �������騬 ����� ᫥襬
echo %__CD__%
rem ��ᢠ����� ��६����� ⥪�訩 ��⠫��:------
set  oldipforsite=%~dp0
:ob

echo ����� 䠩� result.txt � ⥪�饬 ��⠫��� %cd%

::For /D %%a In ("%oldipforsite:~0,-1%.txt") Do Set oldipforsite=%%~na
::Echo %oldipforsite%


pause