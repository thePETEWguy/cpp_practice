#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <Windows.h>

#define MEM_SIZE 30000
#define RED FOREGROUND_RED
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE


class MemoryError : public std::exception {
public:
	MemoryError(const std::string& errorMsg) : _errorMsg(errorMsg) {}

	virtual const char* what() const noexcept override {
		return _errorMsg.c_str();
	}
private:
	std::string _errorMsg;
};

void setOutputColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void interpret(bool withSteps);

void showMenu() {
	int item = 0;
	do {
		system("cls");
		setOutputColor(RED);
		std::cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t    BRAINFUCK INTERPRETER\t\t\n\n\n";

		(!item) ? setOutputColor(WHITE) : setOutputColor(RED);
		std::cout << "\t\t\t\t\t   INTERPRET SHOWING STEPS\n\n";

		(!item) ? setOutputColor(RED) : setOutputColor(WHITE);
		std::cout << "\t\t\t\t\tINTERPRET SHOWING OUTPUT ONLY\n";

		if (GetAsyncKeyState(VK_DOWN) < 0) {
			if (!item)
				item++;
		}
		else if (GetAsyncKeyState(VK_UP) < 0) {
			if (item)
				item--;
		}
		Sleep(25);
	} while (GetAsyncKeyState(VK_RETURN) >= 0);

	(!item) ? interpret(true) : interpret(false);
}

void printCode(unsigned currChar, const std::string& code) {
	for (unsigned i = 0; i < code.length(); i++) {
		if (i != currChar) {
			setOutputColor(WHITE); // WHITE
		}
		else {
			setOutputColor(RED); // RED
		}
		std::cout << code[i];
	}
	std::cout << "\n";
}

void printTenCells(const std::string& code, unsigned currChar, const std::string& output, const int cell, const std::vector<unsigned char>& mem) {
	system("cls");
	printCode(currChar, code);

	std::cout << "OUTPUT: " << output << "\n";

	for (int i = 0; i < 10; i++) {
		if (i == cell) {
			setOutputColor(FOREGROUND_RED);
		}
		else {
			setOutputColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		std::cout << (int)mem[i] << " ";
	}
	std::cout << "\n";
}

void interpret(bool withSteps) {
	std::string code;
	std::vector<unsigned char> mem(MEM_SIZE, 0);
	std::stack<int> positionStack;
	std::string output = "";
	int cell = 0;

	std::cin.ignore();
	setOutputColor(WHITE);
	std::cout << "INPUT: ";
	std::cin >> code;

	if (withSteps) {
		printTenCells(code, 0, output, cell, mem);
		std::cin.get();
	}

	for (unsigned i = 0; i < code.length(); i++) {
		switch (code[i]) {
		case '>':
			cell++;
			if (cell > MEM_SIZE)
				throw MemoryError("Error! Current cell # > 30000");
			break;
		case '<':
			cell--;
			if (cell < 0)
				throw MemoryError("Error! Current cell # < 0");
			break;
		case '+':
			mem[cell]++;
			break;
		case '-':
			mem[cell]--;
			break;
		case '[':
			if (mem[cell] != 0)
				positionStack.push(i);
			else {
				int loopStart = 1;
				int loopEnd = 0;

				do {
					i++;
					if (code[i] == '[')
						loopStart++;
					else if (code[i] == ']')
						loopEnd++;
				} while (loopStart != loopEnd);
			}
			break;
		case ']':
			if (mem[cell] != 0) {
				i = positionStack.top();
			}
			else {
				positionStack.pop();
			}
			break;
		case ',':
			std::cin.ignore(); // in order to escape the newline character that stays in the buffer
			mem[cell] = std::cin.get();
			break;
		case '.':
			output += mem[cell];
			break;
		default:
			break;
		}
		if (withSteps) {
			printTenCells(code, i, output, cell, mem);
			std::cin.get();
		}
	}

	if (!withSteps) {
		setOutputColor(RED);
		std::cout << "OUTPUT: " << output << "\n";
	}
}

int main() {
	showMenu();

	std::cin.ignore();
	std::cin.get();
	return 0;
}