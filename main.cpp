#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<ctime>
#include<windows.h> // console game
#include<conio.h> // input check
#include<cwchar> // font size modification
using namespace std;

void HideCursor();
void Gotoxy(int x, int y);
void PressAnyKey();
void GetKeyInput();
bool check();

vector<vector<int>> is_found;
vector<vector<int>> map;
int x = 0, y = 0;
int S;
bool is_boom = 0;


int main() {
	srand((unsigned int)time(0));
	system("cls");
	system("mode con cols=50 lines=20");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 30;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	cout << "Enter gamesize : ";
	cin >> S;

	map.assign(S, vector<int>(S, 0));

	is_found.assign(S, vector<int>(S, 0));

	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {

			int randnum = rand() % 8;
			if (!randnum) {
				map[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			if (map[i][j]) continue;
			if (i > 0) {//up
				if (map[i - 1][j] == -1) map[i][j]++;
			}
			if (i < S - 1) {//down
				if (map[i + 1][j] == -1) map[i][j]++;
			}
			if (j > 0) {//left
				if (map[i][j - 1] == -1) map[i][j]++;
			}
			if (j < S - 1) {//right
				if (map[i][j + 1] == -1) map[i][j]++;
			}
			if (i > 0 && j > 0) { //left up
				if (map[i - 1][j - 1] == -1) map[i][j]++;
			}
			if (i < S - 1 && j > 0) { //left down
				if (map[i + 1][j - 1] == -1) map[i][j]++;
			}
			if (i > 0 && j < S - 1) { //right up 
				if (map[i - 1][j + 1] == -1) map[i][j]++;
			}
			if (i < S - 1 && j < S - 1) { //right down
				if (map[i + 1][j + 1] == -1) map[i][j]++;
			}

		}
	}

	while (1) {
		system("cls");

		if (is_boom) {
			cout << "BOOOM!!!!!!!!!" << endl;

			for (int i = 0; i < S; i++) {
				for (int j = 0; j < S; j++) {
					if (map[i][j] == -1) {
						cout << "B ";
					}
					else {
						cout << map[i][j] << " ";
					}
				}
				cout << endl;
			}

			_getch();
			break;
		}
		if (check()) {
			cout << "CONGRATULATIONS!!!!!!!!" << endl;
			for (int i = 0; i < S; i++) {
				for (int j = 0; j < S; j++) {
					if (map[i][j] == -1) {
						cout << "B ";
					}
					else {
						cout << map[i][j] << " ";
					}
				}
				cout << endl;
			}

			_getch();
			break;
		}

		for (int i = 0; i < S; i++) {
			for (int j = 0; j < S; j++) {
				if (is_found[i][j]) {
					if (map[i][j] == -1) {
						cout << "B ";
					}
					else {
						cout << map[i][j] << " ";
					}
				}
				else {
					cout << "? ";
				}
			}
			cout << endl;
		}

		cout << x << " " << y;
		Gotoxy(2 * x, y);

		GetKeyInput();
	}

}

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void GetKeyInput() {
	int inp;
	inp = _getch();
	if (inp == 'a') {
		if (x > 0) x--;
	}
	if (inp == 's') {
		if (y < S - 1) y++;
	}
	if (inp == 'd') {
		if (x < S - 1) x++;
	}
	if (inp == 'w') {
		if (y > 0) y--;
	}
	if (inp == 'o') {
		if (map[y][x] == -1) is_boom = 1;
		is_found[y][x] = 1;
	}
}

bool check() {
	int cnt = 0;
	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			if (map[i][j] == -1) cnt++;
		}
	}
	int cnt_uf = 0;
	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			if (is_found[i][j] == 0) cnt_uf++;
		}
	}
	if (cnt == cnt_uf) return 1;
	return 0;
}
