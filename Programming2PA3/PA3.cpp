#include "pa3.h"

using namespace std;

void stack::push(string a) {
	st[count] = a;
	count++;
}
string stack::pop() {
	if (!this->isempty()) {
		string str = st[count - 1];
		cout << str << endl;
		st[count - 1] = "";
		count--;
		return str;
	}
	else {
		return "";
	}
}

void stack::deleteTop() {
	st[count - 1] = "";
	count--;
}

void stack::showup() {
	if (count == 0) {
		return;
	}
	for (int i = count; i > 0; i--) {
		cout << st[i - 1] << " ";
	}
	cout << endl;
}

bool stack::check(string stuff) {
	for (int i = 0; i < count; i++) {
		if (stuff == st[i]) {
			return true;
		}
	}
	return false;
}

bool stack::isempty() {
	if (count == 0) {
		return true;
	}
	return false;
}

string stack::onTop() {
	if (!this->isempty())
		return st[count - 1];
	else {
		return"s";
	}
}

int stack::numTwos() {
	int index = 0;
	for (int b = 0; b < count; b++) {
		if (st[b] == "2") {
			index++;
		}
	}
	return index;
}

bool isKeyword(string word) {
	if ((word == "FOR") || (word == "BEGIN") || (word == "END")) {
		return true;
	}
	return false;
}

bool isOperator(char character) {
	if ((character == '-') || (character == '*') || (character == '/') || (character == '=') || (character == '+')) {
		return true;
	}
	return false;
}

bool isDelimiter(char oops) {
	if ((oops == ';') || (oops == ',')) {
		return true;
	}
	return false;
}

bool isParenthesis(char ah_oh) {
	if ((ah_oh == '(') || (ah_oh == ')')) {
		return true;
	}
	return false;
}

int main() {
	ifstream in;

	int numNested = 0;
	string nameFile = "ewcvewv";
	string line;
	string line2 = "";
	int pos2 = 0;
	string temp = "";
	int leftPar = 0;
	int rightPar = 0;
	char currentPos = 'o';
	int numLength = 0;
	bool nextLineMustBeBegin = false;
	int numFor = 0;
	int numEnds = 0;
	int numBegins = 0;
	bool isBegin = false;
	int numEndsNeeded = 0;
	bool forTest = false;
	bool beginTest = false;
	bool endTest = false;
	bool parTest = false;
	bool upperYes = false;
	bool isEND = true;
	int numLine = 0;


	stack k;//keyword
	stack i;//identifier
	stack c;//constant
	stack o;//operator
	stack d;//delimiter
	stack s;//syntax error
	stack n;//nested loop count

	cout << "Please enter the name of the input file: " << endl;//This checks if the file exists
	getline(cin, nameFile);
	in.open(nameFile);
	if (!in) {
		cout << "Nah this file does not exist" << endl;
		system("pause");
		exit(1);
	}

	while (getline(in, line)) {//This iterates the file by line
		cout << line << endl;
		numLine++;
		numLength = line.length();
		if (nextLineMustBeBegin == false) {
			while (numLength > pos2) {
				currentPos = line.at(pos2);
				if (currentPos == ' ') {
					while ((currentPos == ' ') && (pos2 < numLength)) {
						pos2++;
						if (pos2 < numLength)
							currentPos = line.at(pos2);
					}
				}
				else if (isupper(currentPos)) {
					upperYes = true;
					for (int l = 0; l < line.length(); l++) {
						if (line.at(l) != ' ') {
							line2 += line.at(l);
						}
					}
					for (int l = 0; l < line2.length(); l++) {
						if (isParenthesis(line2.at(l)) || islower(line2.at(l)) || isOperator(line2.at(l))) {
							isEND = false;
						}
					}
					while ((isupper(currentPos)) && (pos2 < numLength)) {
						temp += currentPos;
						pos2++;
						if (pos2 < numLength) {
							currentPos = line.at(pos2);
						}
					}
					int correctCount = 0;
					string line3 = "";
					if (temp == "FOR") {//fixthis
						nextLineMustBeBegin = true;
						forTest = true;
						numFor++;
					}
					else if (temp == "END") {
						line3 = line.substr(0, pos2 - 3) + line.substr(pos2, numLength - pos2 + 3);//the string without "END", which should not have any character other than spaces
						for (int j = 0; j < line3.length(); j++) {
							if (line3.at(j) != ' ') {
								if (!s.check(line)) {
									s.push(line);
								}
								j = line3.length();
							}
							else {
								correctCount++;
							}
						}
						if (correctCount == line3.length()) {//Once an "END" is found, and on top of the stack is a begin, "FOR" and "BEGIN" are deleted and nested loop counter might increment.
							if (n.onTop() == "2") {
								n.deleteTop();
								n.deleteTop();
								endTest = false;
								numEnds++;
								if (n.numTwos() > 0) {
									numNested++;
								}
								if (!k.check("END")) {
									k.push("END");
								}
							}
							else {
								numEnds++;
							}
						}
						else if (n.onTop() == "1") {
							if (!s.check("BEGIN")) {
								s.push("BEGIN");
							}
						}
					}
					else if (temp == "BEGIN") {
						if (!s.check(line)) {
							s.push("BEGIN");
						}
					}
					if ((isKeyword(temp)) && (!k.check(temp))) {
						k.push(temp);
					}
					if ((isEND) && (line2 != "END")) {
						if (!s.check(line2)) {
							s.push(line2);
						}
						numEnds++;
					}
					temp = "";
				}
				else if (isOperator(currentPos)) {
					if (currentPos != '+') {
						temp += currentPos;
						if (!o.check(temp)) {
							o.push(temp);
						}
						temp = "";
					}
					else {
						if (line.at(pos2 + 1) == '+') {
							pos2++;
							currentPos = line.at(pos2);
							if (!o.check("++")) {
								o.push("++");
							}
						}
						else {
							if (!o.check("+")) {
								o.push("+");
							}
						}
					}
					pos2++;
				}
				else if (isdigit(currentPos)) {
					while (isdigit(currentPos)) {
						temp += currentPos;
						pos2++;
						currentPos = line.at(pos2);
					}
					if (!c.check(temp)) {
						c.push(temp);
					}
					temp = "";
				}
				else if (islower(currentPos)) {
					while (islower(currentPos)) {
						temp += currentPos;
						pos2++;
						currentPos = line.at(pos2);
					}
					if (!i.check(temp)) {
						i.push(temp);
					}
					temp = "";
				}
				else if (isDelimiter(currentPos)) {
					temp += currentPos;
					if (!d.check(temp)) {
						d.push(temp);
					}
					temp = "";
					pos2++;
				}
				else if (isParenthesis(currentPos)) {//Fix this!!!
					if (currentPos == '(') {
						leftPar++;
					}
					else {
						rightPar++;
					}
					pos2++;
				}
			}
			if ((leftPar != rightPar)) {
				if (leftPar > rightPar) {
					if (!s.check("("))
						s.push("(");
				}
				else {
					if (!s.check(")"))
						s.push(")");
				}
				parTest = false;
			}
			else {
				parTest = true;
			}
			if (nextLineMustBeBegin) {
				if ((leftPar == 0) || (rightPar == 0)) {
					if (!s.check("(")) {
						s.push("(");
					}
					if (!s.check(")")) {
						s.push(")");
					}
					parTest = false;
				}
			}
			if ((forTest)) {
				n.push("1");
				forTest = false;
				parTest = false;
			}
			upperYes = false;
			isEND = true;
			pos2 = 0;
			temp = "";
			leftPar = 0;
			rightPar = 0;
			line2 = "";
		}
		else {
			while (numLength > pos2) {
				currentPos = line.at(pos2);
				if (currentPos == ' ') {
					while ((currentPos == ' ') && (pos2 < numLength)) {
						pos2++;
						if (pos2 < numLength)
							currentPos = line.at(pos2);
					}
				}
				else if (isupper(currentPos)) {
					upperYes = true;
					for (int l = 0; l < line.length(); l++) {
						if (line.at(l) != ' ') {
							line2 += line.at(l);
						}
					}
					while ((isupper(currentPos)) && (pos2 < numLength)) {
						temp += currentPos;
						pos2++;
						if (pos2 < numLength) {
							currentPos = line.at(pos2);
						}
					}
					if (temp == "BEGIN") {
						isBegin = true;
					}

					int correctCount = 0;
					string line3 = "";
					if (temp == "BEGIN") {
						line3 = line.substr(0, pos2 - 5) + line.substr(pos2, numLength - pos2 + 5);//the string without "BEGIN", which should not have any character other than spaces
						for (int j = 0; j < line3.length(); j++) {
							if (line3.at(j) != ' ') {
								if (!s.check(line2)) {
									s.push(line2);
								}
							}
							else {
								correctCount++;
							}
						}
					}if (correctCount == line3.length()) {
						if (!k.check("BEGIN")) {
							k.push("BEGIN");
						}if (n.onTop() == "1") {
							n.push("2");
						}
						numBegins++;
					}
					temp = "";
				}
				else if (islower(currentPos)) {
					while (islower(currentPos)) {
						temp += currentPos;
						pos2++;
						currentPos = line.at(pos2);
					}
					if (!i.check(temp)) {
						i.push(temp);
					}
					temp = "";
				}
				else if (isDelimiter(currentPos)) {
					temp += currentPos;
					if (!d.check(temp)) {
						d.push(temp);
					}
					temp = "";
					pos2++;
				}
				else if (isOperator(currentPos)) {
					if (currentPos != '+') {
						temp += currentPos;
						if (!o.check(temp)) {
							o.push(temp);
						}
						temp = "";
					}
					else {
						if (line.at(pos2 + 1) == '+') {
							pos2++;
							currentPos = line.at(pos2);
							if (!o.check("++")) {
								o.push("++");
							}
						}
						else {
							if (!o.check("+")) {
								o.push("+");
							}
						}
					}
					pos2++;
				}
				else if (isdigit(currentPos)) {
					while (isdigit(currentPos)) {
						temp += currentPos;
						pos2++;
						currentPos = line.at(pos2);
					}
					if (!c.check(temp)) {
						c.push(temp);
					}
					temp = "";
				}
			}
			if (!isBegin & !upperYes) {
				if (!s.check("BEGIN")) {
					s.push("BEGIN");
				}
			}
			if ((!isBegin) && (upperYes)) {
				if (!s.check(line2)) {
					s.push(line2);
				}
			}
			pos2 = 0;
			temp = "";
			leftPar = 0;
			rightPar = 0;
			nextLineMustBeBegin = false;
			isBegin = false;
			upperYes = false;
			line2 = "";
		}
	}
	cout << numEnds << numBegins << numFor << endl;
	if (numEnds != numBegins) {
		if (numBegins > numEnds) {
			if (!s.check("END")) {
				s.push("END");
			}
		}
		else {
			if (!s.check("BEGIN")) {
				s.push("BEGIN");
			}
		}
	}
	else {
		if (numFor > numEnds) {
			if (!s.check("END")) {
				s.push("END");
			}
		}
		else if (numFor < numEnds) {
			if (!s.check("BEGIN")) {
				s.push("BEGIN");
			}
		}
	}

	cout << "The depth of nested loop(s) is " << numNested << endl;
	cout << "Keywords: ";
	if (!k.isempty())
		k.showup();
	else
		cout << "NA" << endl;
	cout << "Identifiers: ";
	if (!i.isempty())
		i.showup();
	else
		cout << "NA" << endl;
	cout << "Constants: ";
	if (!c.isempty())
		c.showup();
	else
		cout << "NA" << endl;
	cout << "Operators: ";
	if (!o.isempty())
		o.showup();
	else
		cout << "NA" << endl;
	cout << "Delimiters: ";
	if (!d.isempty())
		d.showup();
	else
		cout << "NA" << endl;
	cout << "Syntax Error(s): ";
	if (!s.isempty())
		s.showup();
	else
		cout << "NA" << endl;
	system("pause");
	in.close();
	return 0;
}