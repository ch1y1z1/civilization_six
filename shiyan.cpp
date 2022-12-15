#include <stdio.h>
#include <windows.h>


#include <iostream>
#define COLOR_DEFAULT "\033[0m"
#define COLOR_Blue "\033[0;34m"
#define COLOR_Green "\033[0;32m"
#define COLOR_Red "\033[0;31m"
#define COLOR_Yellow "\033[0;33m"
#define COLOR_White "\033[0;37m"
#define COLOR_Cyan "\033[0;36m"
#define COLOR_Magenta "\033[0;35m"

#define COLOR_BrightBlue "\033[1;34m"
#define COLOR_BrightGreen "\033[1;32m"
#define COLOR_BrightRed "\033[1;31m"
#define COLOR_BrightYellow "\033[1;33m"
#define COLOR_BrightWhite "\033[1;37m"
#define COLOR_BrightCyan "\033[1;36m"
#define COLOR_BrightMagenta "\033[1;35m"

int main()
{

for (int i = 0; i < 10; i++)
{
    printf(COLOR_BrightRed "test red\n" COLOR_DEFAULT);
    printf("test default\n");
    printf(COLOR_BrightGreen "test green\n" COLOR_DEFAULT);
    printf(COLOR_BrightYellow "test yellow\n" COLOR_DEFAULT);
    printf(COLOR_BrightCyan "test cyan\n" COLOR_DEFAULT);
    printf(COLOR_BrightMagenta "test magenta\n" COLOR_DEFAULT);
}
std::cout << "Hello World!\n";
}