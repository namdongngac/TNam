#define    KEY_A    0x41
#define    KEY_N    0x4E
#define    KEY_Y    0x59
#define     KEY_LEFT    VK_LEFT
#define     KEY_RIGHT   VK_RIGHT
#define     KEY_UP      VK_UP
#define     KEY_DOWN    VK_DOWN
#define     KEY_ESC     VK_ESCAPE

#include "windows.h"
 
 
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // L?y handle c?a s? console hi?n hành
 
// Ðua con tr? d?n t?a d? x:y
void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
 
// Ð?t màu cho ch?
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
 void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}
// Xóa toàn b? n?i dung c?a s? console - chôm t? MSDN
void cls( HANDLE hConsole )
{
   COORD coordScreen = { 0, 0 };   
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi; 
   DWORD dwConSize;
 
   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
 
   if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten ))
      return;
 
   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;
 
   if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten ))
      return;
 
   SetConsoleCursorPosition( hConsole, coordScreen );
}
// Vi?t l?i hàm clrscr, không c?n cung du?c nhung d? nhìn vào code cho d?p m?t
void clrscr()
{
    cls(hCon);
}
// Ki?m tra xem phím nào du?c nh?n, tr? v? true n?u phím dó dã du?c nh?n xu?ng
bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}
