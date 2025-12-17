/******************************************************************************************
 * Program: attendance.cpp
 * Course: CCP6114 Programming Fundamentals
 * Lecture Class: TC1L
 * Tutorial Class: TT1L/TT3L
 * Trimester: 2530
 * 
 * Member 1: 252UC254Q2	WILLIAM TAN		william.tan@student.mmu.edu.my			011-2746 8433
 * Member 2: 252UC254RG	HOONG ZHEN YI	.....@student.mmu.edu.my			012-945 6377
 * Member 3: 252UC254YW	LEE CHONG CHUN	lee.chong.chun1@student.mmu.edu.my	019-646 2399
 * Member 4: 253UC2565E	SHAAN VINAAYAK	shaan.vinaayak@student.mmu.edu.my	016-930-2705
 * 
 * ******************************************************************************************
 * 
 * Task distribution
 * Member 1:
 * Member 2:
 * Member 3:
 * Member 4:
 */

#include <iostream>
#include <string>

using namespace std;

const int DIVIDER_SIZE = 40;
const string doubleLine(DIVIDER_SIZE, '=');
const string singleLine(DIVIDER_SIZE, '-');

const int MAX_ROWS = 100;
const int MAX_COLUMNS = 10;

string sheetName;
string columnNames[MAX_COLUMNS];
string dataRows[MAX_ROWS][MAX_COLUMNS];

int COLUMN_COUNT;
int ROW_COUNT = 0;

// Function declare
void printHeader(string);
void setupColumns();
void printInsertRowInterface();

/**
 * Concept explaination
 * in first row, we setup columnName, let's say three column, then set thier name: id, name, status
 * then we add data into folowing row as long as it doesn't exceed MAX_ROWS limitation
 * 
 * first row know as columnNames[index]
 * { id, name, status }
 * 
 * following row known as dataRows[number of row][column's index]
 * {
 * 	{ 1001, Jan, 1 },
 * 	{ 1002, John, 0 }
 * }
 * 
 * then we print it in csv format
 * id,name,status		<- header, columnName
 * 1001,Jan,1			<- data content, 
 * 1002,John,0
 */

int main() {

	printHeader("");


	cout << "Enter attendance sheet name: ";
	cin >> sheetName;
	cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl;

	setupColumns();

	printHeader("Insert New Attendance Row");

	// todo: loop until user decide to stop adding row
	printInsertRowInterface();

	return 0;
}

/**
 * Print initial header if arg is empty string, else print custom header
 */
void printHeader(string title) {
	string content, divider;

	if (title.empty()) {
		content = " STUDENT ATTENDANCE TRACKER - MILESTONE 1 ";
		divider = doubleLine;
	} else {
		content = title;
		divider = singleLine;
	}

	cout << divider << endl;
	cout << content << endl;
	cout << divider << endl << endl;
}

void setupColumns() {
	cout << "Define number of columns (max 10): ";
	cin >> COLUMN_COUNT;
	cin.ignore();	// Clear newline character from input buffer
	cout << endl;

	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter column " << (i + 1) << " name: ";
		getline(cin, columnNames[i]);
	}

	cout << endl << "Sheet structure created successfully." << endl << endl;
}

void printInsertRowInterface() {
	for(int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter " << columnNames[i] << ": ";
		getline(cin, dataRows[ROW_COUNT][i]);
	}
	ROW_COUNT++;
	cout << "Row inserted successfully." << endl;
}
