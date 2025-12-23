/******************************************************************************************
 * Program: attendance.cpp
 * Course: CCP6114 Programming Fundamentals
 * Lecture Class: TC1L
 * Tutorial Class: TT1L/TT3L
 * Trimester: 2530
 * 
 * Member 1: 252UC254Q2	WILLIAM TAN		william.tan@student.mmu.edu.my		011-2746 8433	William-0201
 * Member 2: 252UC254RG	HOONG ZHEN YI	HOONG.ZHEN.YI@student.mmu.edu.my	012-945 6377	zhenyii
 * Member 3: 252UC254YW	LEE CHONG CHUN	lee.chong.chun1@student.mmu.edu.my	019-646 2399	black-OWL432
 * Member 4: 253UC2565E	SHAAN VINAAYAK	shaan.vinaayak@student.mmu.edu.my	016-930 2705	CandyVirtue
 * 
 * ******************************************************************************************
 * 
 * Task distribution
 * Member 1: printHeader(), setupColumns()
 * Member 2: insertDataRow()
 * Member 3: error handling, code reviewer
 * Member 4: printCsvFormat()
 */

#include <iostream>
#include <string>

using namespace std;

// Global constants
const int DIVIDER_SIZE = 40;
const string doubleLine(DIVIDER_SIZE, '=');
const string singleLine(DIVIDER_SIZE, '-');

const int MAX_ROWS = 100;
const int MAX_COLUMNS = 10;

// Global variables
string sheetName;
string columnNames[MAX_COLUMNS];
string columnTypes[MAX_COLUMNS];
string dataRows[MAX_ROWS][MAX_COLUMNS];

int COLUMN_COUNT = 0;
int ROW_COUNT = 0;

// Function declare
void printHeader(string);
void setupColumns();
void insertDataRow();
void printCsvFormat();

/**
 * Concept explaination
 * in first row, we setup columnName, let's say three column, then set their name: id, name, status
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

int main()
{
	int choice = -1;

	printHeader("");

	cout << "Enter attendance sheet name: ";
	cin >> sheetName;
	cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl;

	setupColumns();

	while (choice != 0) {
		cout << singleLine << endl;
		cout << "1. Insert new attendance row" << endl;
		cout << "2. View Attendance Sheet (CSV)" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter an option: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

		switch (choice) {
			case 1:
				printHeader("Insert New Attendance Row");
				insertDataRow();
				cout << endl;
				break;
			case 2:
				printHeader("View Attendance Sheet (CSV)");
				printCsvFormat();
				cout << endl;
				break;
			case 0:
				cout << "Exiting the program..." << endl;
				break;
			default:
				cout << "Invalid choice. Please try again." << endl << endl;
				break;
		}
	}

	return 0;
}

// Print initial header if arg is empty string, else print custom header
void printHeader(string title)
{
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

// Initialize columnName and columnType
void setupColumns()
{
	int tmp;
	while (true) {
		cout << "Define number of columns (max 10): ";
		cin >> tmp;
		if (cin.fail() || tmp < 1 || tmp > 10) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number between 1 and 10." << endl;
			continue;
		}
		COLUMN_COUNT = tmp;
		break;
	}
	cin.ignore();
	cout << endl;

	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter column " << i + 1 << " name: ";
		getline(cin, columnNames[i]);

		string tmp;
		while (true) {
			cout << "Enter type of " << columnNames[i] << " (int/string/bool): ";
			getline(cin, tmp);
			if (tmp != "int" && tmp != "string" && tmp != "bool") {
				cout << "Invalid input. Please enter a valid type." << endl;
				continue;
			}
			columnTypes[i] = tmp;
			break;
		}
		cout << endl;
	}

	cout << endl << "Sheet structure created successfully." << endl << endl;
}

// Add new row
void insertDataRow()
{
	// use to avoid overflowing storage
	if(ROW_COUNT >= MAX_ROWS) {
		cout << "Error: maximum number of rows reached." << endl;
		return;
	}

	for(int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter " << columnNames[i] << " (" << columnTypes[i] << "): ";
		// Since dataRows is string array, we need to check type manually
		while (true) {
			if (columnTypes[i] == "int") {
				int tmp;
				while (!(cin >> tmp)) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter an integer: ";
				}
				dataRows[ROW_COUNT][i] = to_string(tmp);
				break;
			} else if (columnTypes[i] == "bool") {
				bool tmp;
				while (!(cin >> tmp)) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter a boolean (0/1): ";
				}
				dataRows[ROW_COUNT][i] = to_string(tmp);
				break;
			} else { // string could be ANY, so lowest priority
				getline(cin, dataRows[ROW_COUNT][i]);
				break;
			}
		}
	}

	ROW_COUNT++;
	cout << "Row inserted successfully." << endl;
}

// Print data in csv format
void printCsvFormat()
{
	// header
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << columnNames[i];
		if (i < COLUMN_COUNT - 1) {
			cout << ",";
		}
	}
	cout << endl;

	// data rows
	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COLUMN_COUNT; col++) {
			cout << dataRows[row][col];
			if (col < COLUMN_COUNT - 1) {
				cout << ",";
			}
		}
		cout << endl;
	}
}
