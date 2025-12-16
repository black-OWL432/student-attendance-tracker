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

string sheetName;
string columns[3] = {
	"StudentID",
	"Name",
	"Status"
};  //modify here

void printDoubleLine() {
	cout << "===========================================" << endl;
}

void printSingleLine() {
	cout << "-------------------------------------------" << endl;
}

void printAppHeader() {
	printDoubleLine();
	cout << " STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
	printDoubleLine();
	cout << endl;
}

void printSectionHeader(string title) {
	cout << endl;
	printSingleLine();
	cout << " " << title << endl;
	printSingleLine();
}

void setupColumns() {
	int numColumns;
	cout << "Define number of columns (max 10): ";
	cin >> numColumns;
	cin.ignore();	// Clear newline character from input buffer
	cout << endl;

	for (int i = 0; i < numColumns; i++) {
		string columnName;	//modify here
		cout << "Enter column " << (i + 1) << " name: ";
		getline(cin, columnName);	// Store or process columnName as needed
	}
	
	cout << endl;
	cout << "Columns structure created successfully." << endl;
	cout << endl;
}

void printInsertRowInterface(string colNames[], int colCount) {
	cout << "Insert Attendance Row:" << endl;
	for(int i = 0; i < colCount; i++) {
		cout << "Enter" << colNames[i] << ": ";
		string input;
		getline(cin, input);
	}
	cout << "Attendance row inserted successfully." << endl;
}

int main() {

	printAppHeader();


	cout << "Enter attendace sheet name: ";
	cin >> sheetName;
	cout << "Attendance sheet \"" << sheetName << "\" created successfully." << endl;
	
	setupColumns();

	printSectionHeader("Insert New Attendance Row");

	printInsertRowInterface(columns, 3);	//modify here
	return 0;
}
