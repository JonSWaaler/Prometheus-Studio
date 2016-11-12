// GDW GAME
// By: Mitchell Fukuzawa, Peter Okai-koi, Jon Oliver, Jon Waaler, Noel Shere
// Project: Agarthan Assault
#include "Header.h"

//void read();
void movement();

int x = 2;
int y = 2;
int dir = 0;
int temp;
int temp1;


HANDLE console;
void write();
void SetConsoleWindowSize(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (h == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Unable to get stdout handle.");

	// If either dimension is greater than the largest console window we can have,
	// there is no point in attempting the change.
	{
		COORD largestSize = GetLargestConsoleWindowSize(h);
		if (x > largestSize.X)
			throw std::invalid_argument("The x dimension is too large.");
		if (y > largestSize.Y)
			throw std::invalid_argument("The y dimension is too large.");
	}


	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
		throw std::runtime_error("Unable to retrieve screen buffer info.");

	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		if (!SetConsoleWindowInfo(h, TRUE, &info))
			throw std::runtime_error("Unable to resize window before resizing buffer.");
	}

	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(h, size))
		throw std::runtime_error("Unable to resize screen buffer.");


	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(h, TRUE, &info))
		throw std::runtime_error("Unable to resize window after resizing buffer.");
}

int main()
{
	//Resizes Console Window
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	//console = GetConsoleWindow();
	//RECT ConsoleRect;
	//GetWindowRect(console, &ConsoleRect);
	//MoveWindow(console, 0, 0, 800, 1050, TRUE);

	SetConsoleWindowSize(80, 83);

	front_buffer.resize(lines.size());
	for (int i = 0; i < front_buffer.size(); i++)
	{
		front_buffer[i].resize(front_buffer[i].size());

		for (int x = 0; x < front_buffer[i].size(); x++)
		{
			front_buffer[i][x] = -1;
		}
	}

	temp = lines[y][x];
	lines[y][x] = 16;
	while (true)
	{
		write();
		movement();
		//read();
		Sleep(50);
		//cls();



		//if (GetAsyncKeyState(VK_RIGHT))
		//{
		//lines[0][0] = 7;
		//}
		//if (GetAsyncKeyState(VK_LEFT))
		//{
		//lines[0][0] = 4;
		//}
	}
}


void write()
{
	for (int L = 0; L < 82; L++)
	{
		for (int M = 0; M < 80; M++)
		{
			//cout << front_buffer[L][M] << " " << lines[L][M];

			if (front_buffer[L][M] != lines[L][M])
			{

				COORD p = { (SHORT)M, (SHORT)L };
				SetConsoleCursorPosition(console, p);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), lines[L][M] * 16);

				printf("%c", ' ');

				front_buffer[L][M] = lines[L][M];
			}
		}
	}
}

/*
void read()
{
for (int L = 0; L < 82; L++)
{
for (int M = 0; M < 80; M++)
{
// Depending on the number value in the line vector it will output a certain colour5
if ((lines[L][M]) == 0)
white();
else if ((lines[L][M]) == 1)
black();
else if ((lines[L][M]) == 2)
lightBlue();
else if ((lines[L][M]) == 3)
cyan();
else if ((lines[L][M]) == 4)
brown();
else if ((lines[L][M]) == 5)
green();
else if ((lines[L][M]) == 6)
blue();
else if ((lines[L][M]) == 7)
lightGreen();
else if ((lines[L][M]) == 8)
red();
else if ((lines[L][M]) == 9)
lightGrey();
else if ((lines[L][M]) == 10)
darkGrey();
else if ((lines[L][M]) == 11)
magenta();
}
movement();
}
}
*/

void movement()
{
	//dir = 0;
	//
	//if (GetAsyncKeyState(87)) //w
	//	dir = 1;
	//else if (GetAsyncKeyState(65)) //a
	//	dir = 2;
	//else if (GetAsyncKeyState(83)) //s
	//	dir = 3;
	//else if (GetAsyncKeyState(68)) //d
	//	dir = 4;
	//else //nothing
	//	dir = 0;

	//----DIAGONAL----
	if (GetAsyncKeyState(87)) //w
	{
		if ((GetAsyncKeyState(65)) && (y > 0) && (x > 0)) //a
		{
			temp1 = lines[y - 1][x - 1];
			y--;
			x--;
			lines[y + 1][x + 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
		else if ((GetAsyncKeyState(68)) && (y > 0) && (x < 79)) //d
		{
			temp1 = lines[y - 1][x + 1];
			y--;
			x++;
			lines[y + 1][x - 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
	}
	if (GetAsyncKeyState(83))
	{
		if ((GetAsyncKeyState(65)) && (y > 0) && (x > 0)) //a
		{
			temp1 = lines[y + 1][x - 1];
			y++;
			x--;
			lines[y - 1][x + 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
		}
		else if ((GetAsyncKeyState(68)) && (y > 0) && (x < 79)) //d
		{
			temp1 = lines[y + 1][x + 1];
			y++;
			x++;
			lines[y - 1][x - 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
		}
	}


	//----NORMAL----
	if ((GetAsyncKeyState(87)) && !(GetAsyncKeyState(83))) //w
	{
		if (y > 0) {
			temp1 = lines[y - 1][x];
			y--;
			lines[y + 1][x] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
		lines[y][x] = 1;
	}
	else if ((GetAsyncKeyState(65)) && !(GetAsyncKeyState(68))) //a
	{
		if (x > 0) {
			temp1 = lines[y][x - 1];
			x--;
			lines[y][x + 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
	}
	else if ((GetAsyncKeyState(83)) && !(GetAsyncKeyState(87))) //s
	{
		if (y < 54) {
			temp1 = lines[y + 1][x];
			y++;
			lines[y - 1][x] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
	}
	else if ((GetAsyncKeyState(68)) && !(GetAsyncKeyState(65))) //d
	{
		if (x < 79) {
			temp1 = lines[y][x + 1];
			x++;
			lines[y][x - 1] = temp;
			lines[y][x] = 1;
			temp = temp1;
			//Sleep(50);
		}
	}
	else
		;
}
