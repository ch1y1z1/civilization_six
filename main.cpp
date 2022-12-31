#include <iostream>
#include "Display.h"
#include <cstring>
using namespace std;
void full_screen()
{
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN); /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN); /* 屏幕高度 像素 */

    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); /* 获取窗口信息 */
    /* 设置窗口信息 最大化 取消标题栏及边框 */
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}
int main()
{
    full_screen();
    Controller *controller = new Controller();

    Activity *symposium = new Activity((char *)"symposium", 50, Attributes(30.0));
    Activity *exhibition = new Activity((char *)"exhibition", 50, Attributes(0, 30.0));
    Activity *distribution = new Activity((char *)"distribution", 50, Attributes(0, 0, 0, 30.0));

    Activity **activities = new Activity *[3]
    { symposium, exhibition, distribution };

    Building *center = new Building((char *)"cen", 0.0, Attributes(0.0), Attributes(0.7, 0.3, 0.5, 0.5), Attributes(1.0), (char *)"a", NOTYPE, symposium, 0);
    Building *campus = new Building((char *)"cam", 100.0, Attributes(1.0), Attributes(0.2), Attributes(1.0), (char *)"a", MOUNTAIN, symposium, 1);
    Building *theatre = new Building((char *)"the", 100.0, Attributes(0, 1.0), Attributes(0, 0.2), Attributes(1.0), (char *)"aw", NOTYPE, exhibition, 2);
    Building *wonder = new Building((char *)"won", 250.0, Attributes(0, 20.0), Attributes(0), Attributes(5.0), (char *)"w", NOTYPE, 0, 3);
    Building *industrialPark = new Building((char *)"ind", 100.0, Attributes(0, 0, 0, 2.0), Attributes(0, 0, 0, 2.0), Attributes(1.0), (char *)"a", NOTYPE, distribution, 4);

    Building **buildings = new Building *[5]
    { center, campus, theatre, wonder, industrialPark };

    Grid *grid = new Grid("./resource/map.txt");

    Display d;
    d.MainProcess(controller, grid, buildings, activities);
    return 0;
}
// 移动光标位置至(x,y);
// 隐藏光标;
void go(float x, float y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, coord);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(a, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(a, &CursorInfo);
}
// 划分输入区
void out()
{
    go(0, 23);
    cout << "--------------------------------------------\n";
    cout << "              INTERACT HERE\n";
    go(0, 25);
}
// 清空输入区
void clear()
{
    go(0, 25);
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 65; i++)
        {
            cout << " ";
        }
        cout << endl;
    }
}
// 交互整合
void DISPLAY_(Display *dis, Grid *grid, Controller *con)
{
    out();
    dis->DrawMap(grid, con);
    dis->DrawAttributes(con, grid);
    dis->DrawProduction(con);
    clear();
}
// 判断人口输入是否合法
void judge(int x, int y,Grid*grid)
{
    while (1)
    {
        Cell arr = grid->getRepresent(x / 2 - 1, y - 1);
        Landform form = arr.landform;
        if (x % 2 != 0 || form == SEA || form == OCEAN || form == MOUNTAIN)
        {
            cout << "invalid input\n";
            continue;
        }
    }
}