#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <Windows.h>

#define MEM_SIZE 30000

class MemoryError : public std::exception {
public:
    MemoryError(const std::string& errorMsg) : _errorMsg(errorMsg){}

    virtual const char* what() const noexcept override {
        return _errorMsg.c_str();
    }
private:
    std::string _errorMsg;
};

void setCharacterColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printCode(unsigned currChar, const std::string& code) {
	for (int i = 0; i < code.length(); i++) {
		if (i != currChar) {
			setCharacterColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // WHITE
		}
		else {
			setCharacterColor(FOREGROUND_RED); // RED
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
			setCharacterColor(FOREGROUND_RED);
		}
		else {
			setCharacterColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		std::cout << (int)mem[i] << " ";
	}
	std::cout << "\n";
}

void interpret(std::string code){
    std::vector<unsigned char> mem(MEM_SIZE, 0);
    std::stack<int> positionStack;
	std::string output = "";
	int cell = 0;
	int loopStart = 0, loopEnd = 0;

	printTenCells(code, 0, output, cell, mem);
	std::cin.get();

    for (unsigned i = 0; i < code.length(); i++){
        switch (code[i]){
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
				loopStart++;
				if (mem[cell] == 0) { // the data in that cell = 0
					while (code[i++] != ']');
				}
				else { // cell data != 0
					positionStack.push(i);
				}
                break;
            case ']':
				loopEnd++;
				if (mem[cell] != 0) {
					i = positionStack.top();
				}
				else {
					if (loopStart - loopEnd == 0)
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
		printTenCells(code, i, output, cell, mem);
		//std::cin.get();
    }
}

int main(){
	std::string code;

    try {
		std::cin >> code;
		interpret(code);
    } catch (MemoryError memError){
        std::cout << memError.what() << "\n";
    }

	std::cin.ignore();
	std::cin.get();
    return 0;
}