// basic console functions, collected by Nguyen Trung Thanh
// abcxyz tcIT
#include <stdio.h>
#include <conio.h>
#include <iostream>	//cin, cout
#include <sstream>	//stringstream
#include <time.h>	//ham random
#include <string>
#include <windows.h>
//--------------------------------------------------------
#define readfile(f) FILE *f = fopen("./list_input.txt","r")
#define writefile(f) FILE *f = fopen("./results.txt","a")

#define clearfile(f) \
		FILE *f = fopen("./results.txt", "w");\
		fprintf(f, " ");\
		fclose(f)
//--------------------------------------------------------
#ifndef _console_header
#define _console_header
//--------------------------------------------------------
#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15
#define default_ColorCode		7

#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

//--------------------------------------------------------
using namespace std;
//--------------------------------------------------------

int inputKey(){
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

//-------------------------Screen-------------------------
void clrscr(){
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}


//screen: goto [x,y]
void gotoXY (int column, int line){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//screen: get [x]
int whereX(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}
//screen: get [y]
int whereY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

void TextColor (int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}

int getScreen(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		cout<<"Khong lay duoc kich thuoc man hinh"<<endl;
	else return csbi.srWindow.Right-csbi.srWindow.Left;
}

void lineCheck(COORD &pos, int screenWidth){
	if(pos.X >= screenWidth){
			pos.X = 0;
			pos.Y++;
		}
}

void lineCheck(COORD &pos1, COORD pos2, int screenWidth){
	if(pos1.X >= screenWidth){
			pos1.X = 0;
			pos1.Y++;
	}
	else pos1.Y = pos2.Y;
}

#endif
