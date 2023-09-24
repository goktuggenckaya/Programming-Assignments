#include <iostream>
#include <string>
#include <fstream>
#include "DynamicStack.h"
#include "strutils.h"
using namespace std;

struct cellStruct{
	char bit;
	bool flag ;
};


void Print_Table(cellStruct ** values, int rows, int cols){
	for (int i =0; i< rows; i++){
		for (int j = 0; j<cols ; j++){
			cout << values[i][j].bit << " ";
		}
		cout << endl;
	}

}
int main() {
	int row, col;
	string fname;
	ifstream file;
	cout << "Please enter the number of rows: ";
	cin >> row;
	cout << "Please enter the number of columns: ";
	cin >> col;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fname;
	file.open(fname.c_str());
	while (file.fail()) {
		cout << "File cannot be opened." << endl << "Please enter the name of the input file that contains the matrix again: " ;
		cin >> fname;
		file.open(fname.c_str());
	}
	string strbit;
	cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	cin >> strbit;
	cellStruct ** matrixx = new cellStruct*[row];
	for (int i = 0; i< row; i++){
		matrixx[i] = new cellStruct[col];
	}
	for (int i = 0; i< row; i++){
		for(int j= 0; j< col; j++){
			matrixx[i][j].flag = false;
		}
	}
	string line;
	int itr = 0;
	while(getline(file , line)){
		int length = line.length();
		for (int o = 0; o < length ; o++){
			matrixx[itr][o].bit = line.at(o);
		}
		itr++;
	}
		
	Print_Table(matrixx, row,col);
	do {
		cellStruct **matrix = matrixx;
		DynamicStack stack;
		bool colbool = true;
		bool rowbool = true;
		bool couldbefound = true;
		bool stopsearching = false;
		bool goback = false;
		int currentrow=0, currentcol=0, currentindex=0;
		/*
		if (strbit.at(currentindex) == matrix[currentrow][currentcol].bit){

		} 
		else if (strbit.at(currentindex) == matrix[currentrow][currentcol+1].bit){
			currentcol++;
			colbool = true;
		}
		else if (strbit.at(currentindex) == matrix[currentrow+1][currentcol].bit) {
			currentrow++;
			colbool = false;
		}
		else {
			cout << "The bit string " << strbit <<" could not be found." << endl;

		}
		*/
		Print_Table(matrix,row,col);
		if (strbit.at(0) != matrix[0][0].bit){
			stopsearching = true;
			cout << "The bit string " << strbit <<" could not be found." << endl;
			couldbefound = false;
			matrix[currentrow][currentcol].flag = true;
		}
		else {
			string added = "("+itoa(currentrow)+ "," + itoa(currentcol)+ ")";
			stack.push(added);
			currentindex++;
			matrix[currentrow][currentcol].flag = true;
		}
		while ( (stopsearching == false) && (currentindex < strbit.length())){
			//matrix[currentrow][currentcol].flag == false)&&(strbit.at(currentindex) == matrix[currentrow][currentcol].bit) &&
			if ((currentrow == 0 && currentcol ==0) || (goback == true)) {
				if ((strbit.at(currentindex) == matrix[currentrow][currentcol].bit) && (matrix[currentrow][currentcol].flag == false)){

				}
				else if ((strbit.at(currentindex) == matrix[currentrow][currentcol+1].bit) && (matrix[currentrow][currentcol+1].flag == false)){
					currentcol++;
					colbool = true;
					rowbool =false;
				}
				else if ((strbit.at(currentindex) == matrix[currentrow+1][currentcol].bit)&& (matrix[currentrow+1][currentcol].flag == false)) {
					currentrow++;
					colbool = false;
					rowbool =true;
				}
				else {
					cout << "The bit string " << strbit <<" could not be found." << endl;
					matrix[currentrow][currentcol].flag = true;
					couldbefound = false;
					stopsearching = true;
				}
			}
			/*
			if ((currentrow == 0 && currentcol == 0) && ((matrix[currentrow+1][currentcol].flag == true)|| (matrix[currentrow+1][currentcol].bit != strbit.at(1))) && ((matrix[currentrow][currentcol+1].flag == true)|| (matrix[currentrow][currentcol+1].bit != strbit.at(1)))) {
				cout << "The bit string "<< strbit<<" could not be found." << endl;
				matrix[currentrow][currentcol].flag == true;
			}
			*/
			string added = "("+itoa(currentrow)+ "," + itoa(currentcol)+ ")";
			stack.push(added);
			currentindex++;
			if (currentindex != strbit.length()){
				if ((matrix[currentrow][currentcol+1].flag ==false) && (strbit.at(currentindex) == matrix[currentrow][currentcol+1].bit)){
					currentcol++;
					colbool = true;
					rowbool = false;
					goback = false;
				}
				else if ((matrix[currentrow+1][currentcol].flag ==false) && (strbit.at(currentindex) == matrix[currentrow+1][currentcol].bit)){
					currentrow++;
					rowbool = true;
					colbool = false;
					goback = false;
				}
				else {
					string deleted;
					stack.pop(deleted);
					currentindex--;
					matrix[currentrow][currentcol].flag = true;
					goback = true;
					if (colbool && rowbool){

					}
					else if (colbool && (rowbool ==false)){
						currentcol--;
					}
					else if (rowbool && (colbool ==false)) {
						currentrow--;
					}
				}
			}
			else {
				stopsearching = true;
			}
		}
		if (couldbefound == true){
			cout << "The bit string "<< strbit << " is found following these cells:" << endl;
			DynamicStack PrintStack;
			string print1, print2;
			while (!stack.isEmpty()) {
				stack.pop(print1);
				PrintStack.push(print1);
			}
			while (!PrintStack.isEmpty()) {
				PrintStack.pop(print2);
				cout << print2 << "	";
			}
		}
		cout << endl<< "---------------------------------------------------------" << endl;
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		stopsearching = false;
	} while (cin >> strbit);
	cout << "Program ended successfully!"<< endl<< endl;


	return 0;
}