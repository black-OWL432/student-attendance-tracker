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
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Global constants
const int DIVIDER_SIZE = 40;
const string doubleLine(DIVIDER_SIZE, '=');
const string singleLine(DIVIDER_SIZE, '-');

const int MAX_COLUMNS = 10;

// Global variables
string sheetName;
vector<string> columnNames;
vector<string> columnTypes;
vector<vector<string>> dataRows;

int COLUMN_COUNT = 0;
int ROW_COUNT = 0;

// Function declare
void printHeader(string);
void loadFromFile(string);
void setupColumns();
string getInputByType(int);
int searchRowIndex();
void insertDataRow();
void updateDataRow();
void deleteDataRow();
void printCsvFormat(ostream& out = cout);
void saveToFile(string);
void countRows();

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
	string fileName;

	printHeader("");

	cout << "Create attendance sheet"<< endl;
	cout << singleLine << endl;
	cout << "Enter sheet name: ";
	getline(cin, fileName);
	loadFromFile(fileName);

	while (choice != 0) {
		cout << singleLine << endl;
		cout << "1. Insert new attendance row" << endl;
		cout << "2. Update attendance row" << endl;
		cout << "3. Delete attendance row" << endl;
		cout << "4. View Attendance Sheet (CSV)" << endl;
		cout << "5. Count Rows" << endl;
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
				printHeader("Update Attendance Row");
				updateDataRow();
				cout << endl;
				break;
			case 3:
				printHeader("Delete Attendance Row");
				deleteDataRow();
				cout << endl;
				break;
			case 4:
				printHeader("View Attendance Sheet (CSV)");
				printCsvFormat(cout);
				cout << endl;
				break;
			case 5:
                printHeader("Count Rows");
                countRows();
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

	if (ROW_COUNT > 0) {
		saveToFile(fileName);
	} 
	return 0;
}

// Print initial header if arg is empty string, else print custom header
void printHeader(string title)
{
	string content, divider;

	if (title.empty()) {
		content = " STUDENT ATTENDANCE TRACKER - MILESTONE 2 ";
		divider = doubleLine;
	} else {
		content = title;
		divider = singleLine;
	}

	cout << divider << endl;
	cout << content << endl;
	cout << divider << endl << endl;
}

void loadFromFile(string filename)
{
	ifstream inputFile(filename + ".csv");
	if (!inputFile.is_open()) {
		cout << "File doesn't exist, creating new file: " << filename << ".csv" << endl;
		setupColumns();
		return;
	}

	columnNames.clear();
	columnTypes.clear();
	dataRows.clear();
	ROW_COUNT = 0;

	string line,word;

	if (getline(inputFile, line)) {
		stringstream ss(line);
		while (getline(ss, word, ',')) {
			size_t pos = word.find('|');
			if (pos != string::npos) {
				columnNames.push_back(word.substr(0, pos));
				columnTypes.push_back(word.substr(pos + 1));
			} else {
				columnNames.push_back(word);
				columnTypes.push_back("string");
			}
		}
		COLUMN_COUNT = columnNames.size();
	}

	while (getline(inputFile, line)) {
		stringstream ss(line);
		vector<string> row;
		while (getline(ss, word, ',')) {
			row.push_back(word);
		}
		if (!row.empty()) {
			dataRows.push_back(row);
			ROW_COUNT++;
		}
	}

	inputFile.close();
	cout << "Successfully loaded: " << filename << endl;
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
	cin.ignore(1000, '\n');
	cout << endl;

	columnNames.resize(COLUMN_COUNT);
	columnTypes.resize(COLUMN_COUNT);

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
	vector<string> newRow(COLUMN_COUNT);

	for(int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter " << columnNames[i] << " (" << columnTypes[i] << "): ";
		newRow[i] = getInputByType(i);
	}

	dataRows.push_back(newRow);
	ROW_COUNT++;
	cout << "Row inserted successfully." << endl;
}

// Print data in csv format
void printCsvFormat(ostream& out)
{
	// header with types
	for (int i = 0; i < COLUMN_COUNT; i++) {
		out << columnNames[i] << "|" << columnTypes[i];
		if (i < COLUMN_COUNT - 1) {
			out << ",";
		}
	}
	out << endl;

	// data rows
	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COLUMN_COUNT; col++) {
			out << dataRows[row][col];
			if (col < COLUMN_COUNT - 1) {
				out << ",";
			}
		}
		out << endl;
	}
}

// Search for a row index
int searchRowIndex()
{
	if (ROW_COUNT == 0) {
		cout << "No data available." << endl;
		return -1;
	}

	// Search from
	cout << "Columns:" << endl;
	cout << "0. Exit" << endl;
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << i + 1 << ". " << columnNames[i] << endl;
	}
	int index;
	while (true) {
		cout << "Choose a column index to search from: ";
		cin >> index;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		if (index == 0) return -1;
		if (index < 1 || index > COLUMN_COUNT) {
			cout << "Invalid column index." << endl;
			continue;
		}
		break;
	}
	index--;
	cin.ignore(1000, '\n');

	// Search
	string target;
	cout << "Enter target value to search for in \"" << columnNames[index] << "\": ";
	getline(cin, target);

	// Search result
	vector<int> matchIndices;
	cout << endl << "Search Results:" << endl;
	for (int i = 0; i < ROW_COUNT; i++) {
		if (dataRows[i][index] == target) {
			matchIndices.push_back(i);
			cout << matchIndices.size() << ". ";
			for (int j = 0; j < COLUMN_COUNT; j++) {
				cout << dataRows[i][j] << (j < COLUMN_COUNT - 1 ? ", " : "");
			}
			cout << endl;
		}
	}

	if (matchIndices.empty()) {
		cout << "No matching records found." << endl;
		return -1;
	}

	// return if only one search result
	if (matchIndices.size() == 1) {
		return matchIndices[0];
	}

	// Choose result
	int resultIndex;
	while (true) {
		cout << endl << "Choose a result index: ";
		cin >> resultIndex;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		if (resultIndex < 1 || resultIndex > (int)matchIndices.size()) {
			cout << "Invalid result index." << endl;
			continue;
		}
		break;
	}
	int rowIndex = matchIndices[resultIndex - 1];
	cin.ignore(1000, '\n');

	return rowIndex;
}

// Get input from user based on column type
string getInputByType(int index)
{
	// All types are string, so we need to check type manually
	while (true) {
		if (columnTypes[index] == "int") {
			int tmp;
			if (cin >> tmp) {
				cin.ignore(1000, '\n');
				return to_string(tmp);
			} else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter an integer: ";
			}
		} else if (columnTypes[index] == "bool") {
			bool tmp;
			if (cin >> tmp) {
				cin.ignore(1000, '\n');
				return to_string(tmp);
			} else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter a boolean (0/1): ";
			}
		} else { // string
			string tmp;
			getline(cin, tmp);
			if (tmp.empty()) {
				cout << "Invalid input. Please enter a valid string: ";
				continue;
			}
			return tmp;
		}
	}
}

// Update info in existing row
void updateDataRow()
{
	int rowIndex = searchRowIndex();
	if (rowIndex == -1) return;

	// Update logic
	cout << endl << "Updating Row " << rowIndex + 1 << ":" << endl;
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << "Enter new " << columnNames[i] << " (" << columnTypes[i] << ") [current: " << dataRows[rowIndex][i] << "]: ";
		dataRows[rowIndex][i] = getInputByType(i);
	}
	cout << "Row updated successfully." << endl;
}

// Delete existing row (DONE)
void deleteDataRow()
{
	if (ROW_COUNT == 0) {
		cout << "No data available." << endl;
		return;
	}

	string targetID;
	cout << "Enter StudentID to delete: ";

	getline(cin, targetID);

	int rowIndex = -1;

	// student id is assumed to be column 0
	for (int i =0; i <ROW_COUNT; i++) {
		if (dataRows[i][0] ==targetID) {
			rowIndex =i;
			break;
		}
	}

	if (rowIndex ==-1) {
		cout << "Error: StudentID does not exist." << endl;
		return;
	}

	// delete the row
	dataRows.erase(dataRows.begin() + rowIndex);
	ROW_COUNT--;

	cout << "Row deleted successfully." << endl << endl;
	cout << "Updated Sheet:" << endl;

	printCsvFormat(cout);
}

// Save data to file
void saveToFile(string fileName)
{
	ofstream outputFile(fileName + ".csv");

	if (outputFile.is_open()) {
		printCsvFormat(outputFile);

		outputFile.close();
		cout <<"------------------------------------------------------" << endl;
		cout << "Writing updated sheet to output file.... " << endl;
		cout << "Output saved as: " << fileName << ".csv" << endl;
		cout <<"------------------------------------------------------" << endl;
	} else {
		cout << "Error: Could not create output file "<< endl;
	}

}

// Count the number of rows
void countRows()
{
	cout << " Number of rows: "<< ROW_COUNT << endl;
}
