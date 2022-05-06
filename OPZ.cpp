#include <iostream>
#include <Windows.h>
using namespace std;

struct OutStack {
	char symbol;
	OutStack* next;
};

void Push(OutStack*& begin, char symbol) {
	OutStack* t = begin;
	begin = new OutStack;
	begin->next = t;
	begin->symbol = symbol;
}

char Pop(OutStack*& begin) {
	OutStack* t = begin;
	begin = begin->next;
	char symbol = t->symbol;
	delete t;
	return symbol;
}

int Pr(char symbol) {
	if (symbol == '*' || symbol == '/') return 3;
	else if (symbol == '+' || symbol == '-') return 2;
	else if (symbol == '(') return 1;
	else return 0;
}

bool InpCheck(char inp[]) {
	int i = 0, a = 1, b = 0, c = 0;
	while (inp[i] != '\0') {
		if (inp[i] >= 97 && inp[i] <= 122) {
			if (a == 0) {
				cout << "Ошибка: неверная запись операндов.\n";
				return 1;
			}
			a = 0;
		}
		else if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
			if (a == 1) {
				cout << "Ошибка: неверная запись операций.\n";
				return 1;
			}
			a = 1;
			b = 0;
		}
		else if (inp[i] == '(') {
			if (b == 1) {
				cout << "Ошибка: неверная запись операций.\n";
				return 1;
			}
			else if (a == 0) {
				cout << "Ошибка: неверная запись операций.\n";
				return 1;
			}
			a = 1;
			c++;
		}
		else if (inp[i] == ')') {
			if (c == 0) {
				cout << "Ошибка: неверная запись скобок.\n";
				return 1;
			}
			a = 0;
			c--;
			b = 1;
		}
		else {
			cout << "Ошибка: неверная запись переменной или операции.\n";
			return 1;
		}
		i++;
	}
	if (a == 1) {
		cout << "Ошибка: незаконченная операция.\n";
		return 1;
	}
	else if (c > 0) {
		cout << "Ошибка: неверная запись скобок.\n";
		return 1;
	}
	return 0;
}

int main() {
	SetConsoleOutputCP(1251);
	while (true) {
		char inp[255];
		char outp[255];
		bool ent = true;
		int i = 0, j = 0;
		OutStack* begin = NULL;

		cout << "Введи выражение (для выхода допусти ошибку)\n";
		cin >> inp;
		if (InpCheck(inp)) return 228;

		while (inp[i] != '\0') {
			if (inp[i] >= 'a' && inp[i] <= 'z') outp[j++] = inp[i];
			else if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
				while (begin != NULL && Pr(begin->symbol) >= Pr(inp[i])) outp[j++] = Pop(begin);
				Push(begin, inp[i]);
			}
			else if (inp[i] == '(') Push(begin, '(');
			else if (inp[i] == ')') {
				while (begin && begin->symbol != '(') outp[j++] = Pop(begin);
				Pop(begin);
			}
			i++;
		}

		while (begin) outp[j++] = Pop(begin);
		outp[j] = '\0';
		cout << "Сформированная ОПЗ: " << outp << "\n--------------------------------------------\n";
	}
	return 0;
}
