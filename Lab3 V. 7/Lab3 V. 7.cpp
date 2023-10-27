#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <sstream>
#include <locale>;
#include "windows.h";

using namespace std;

class LexemeData {
public:
	string lexeme;
	string type;

	LexemeData(string lexeme, string type) : lexeme(lexeme), type(type) {}
};

string getLexemeType(string lexeme) {

	if (regex_match(lexeme, regex("\"[^\"]*\"|'[^']*'"))) {
		return "Рядок";
	}
	else if (regex_match(lexeme, regex("\\d+\\.\\d*|\\d*\\.\\d+"))) {
		return "Число з плаваючою крапкою";
	}
	else if (regex_match(lexeme, regex("0x[0-9a-fA-F]+"))) {
		return "Шістнадцяткове число";
	}
	else if (regex_match(lexeme, regex("\\d+"))) {
		return "Число";
	}
	else if (regex_match(lexeme, regex("(#[If|ElseIf|Else|End If|Const]+.*)"))) {
		return "Директива препроцесора";
	}
	else if (regex_match(lexeme, regex("'[^\n]*"))) {
		return "Коментар";
	}
	else if (
		lexeme == "Module" ||
		lexeme == "Program" ||
		lexeme == "Sub" ||
		lexeme == "String" ||
		lexeme == "As" ||
		lexeme == "Dim" ||
		lexeme == "Double" ||
		lexeme == "Char" ||
		lexeme == "Integer" ||
		lexeme == "Console" ||
		lexeme == "WriteLine" ||
		lexeme == "If" ||
		lexeme == "Then" ||
		lexeme == "ElseIf" ||
		lexeme == "Else" ||
		lexeme == "End If" ||
		lexeme == "End" ||
		lexeme == "End If"
		) {
		return "Зарезервоване слово";
	}
	else if (lexeme == "+" || lexeme == "-" || lexeme == "*" || lexeme == "/" || lexeme == "=") {
		return "Оператор";
	}
	else if (lexeme == ";" || lexeme == "," || lexeme == "(" || lexeme == ")") {
		return "Розділовий знак";
	}
	else if (regex_match(lexeme, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
		return "Ідентифікатор";
	}
	else {
		return "Нерозпізнано";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "ukr");

	regex pattern(R"(\"[^\"]*\"|'[^']*'|[(]|[)]|[,]|[\]|["]|[a-zA-Z_]\w*|0[xX][0-9a-fA-F]+|\d*\.\d+|\d+\.\d*|\d+|//[^$]*|#\w+|==|=|[+\-*/])");
	vector<LexemeData> data;
	ifstream file("input.txt");
	if (!file.is_open()) {
		cerr << "File open error, no file found." << endl;
		return 0;
	}

	string line;
	while (getline(file, line)) {
		sregex_iterator it(line.begin(), line.end(), pattern);
		sregex_iterator it_end;
		while (it != it_end) {
			string lexeme = it->str();
			string type = getLexemeType(lexeme);
			data.push_back(LexemeData(lexeme, type));
			++it;
		}
	}

	cout << "Лексема - Тип лексеми" << endl;
	for (const LexemeData& element : data) {
		cout << element.lexeme << " - " << element.type << endl;
	}

	system("pause");
	return 0;
}
