@echo off 
set BAT_BASE_PATH=%~dp0
set PRJ_BASE_PATH=%BAT_BASE_PATH%

MD %PRJ_BASE_PATH%\bin

clang -I%PRJ_BASE_PATH%\app\include -I%PRJ_BASE_PATH%\core\include -o %PRJ_BASE_PATH%\bin\DoublyLists.exe %PRJ_BASE_PATH%app\DoublyLinkedList_main.c -L %PRJ_BASE_PATH%\bin -l doublylinkedlist