/* Goktug Genckaya
27888
CS300 THE1
STACKS
Main
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "goktuggenckaya_genckaya_goktug_hw1_dynstackclass.h"
#include <random> 
#include <time.h>


using namespace std;

int random_range(const int & min, const int & max) { //function for random integer generation
	static mt19937 generator(time(0)); 
	uniform_int_distribution<int> distribution(min, max); 
	return distribution(generator); 
}

struct cell {
	int x_;
	int y_;
	bool up;
	bool down ;
	bool right;
	bool left;
	bool uw, dw, lw,rw;
	bool visited;
};

string giverandomdirection(cell cel){ //using the previous random integer generator function, gives a possible direction 
	int returned = 0;
	vector<string> directions;
	if (cel.up == true) {
		returned++;
		directions.push_back("up");
	}
	if (cel.down == true){
		returned++;
		directions.push_back("down");
	}
	if (cel.left == true) {
		returned++;
		directions.push_back("left");
	}
	if (cel.right == true) {
		returned++;
		directions.push_back("right");
	}
	if (returned ==0){
		return "no";
	}
	int randint = random_range(0,returned-1);
	return directions[randint];
}

string giverandomdirection2(cell cel){ //for the second part of the homework, gives random direction while path discovery
	int returned = 0;
	vector<string> directions;
	if (cel.uw == false) {
		returned++;
		directions.push_back("up");
	}
	if (cel.dw == false){
		returned++;
		directions.push_back("down");
	}
	if (cel.lw == false) {
		returned++;
		directions.push_back("left");
	}
	if (cel.rw == false) {
		returned++;
		directions.push_back("right");
	}
	if (returned ==0){
		return "no";
	}
	int randint = random_range(0,returned-1);
	return directions[randint];
}

int wallcount(cell cel){ //gives how many walls surround the cell
	int wallc=0;
	if (cel.rw == true) wallc++;
	if (cel.lw == true) wallc++;
	if (cel.uw == true) wallc++;
	if (cel.dw == true) wallc++;
	return wallc;
}
 
bool oppositedir(string dir1, string dir2){ //if the random direction and previous direction are opposite or not (to prevent loops)
	if ((dir1 == "up") && (dir2 == "down")) return true;
	if ((dir1 == "down") && (dir2 == "up")) return true;
	if ((dir1 == "right") && (dir2 == "left")) return true;
	if ((dir1 == "left") && (dir2 == "right")) return true;
}

int main() {
	int M, N, K;
	vector<vector<cell> > mainmaze;
	cout << "Enter the number of mazes: ";
	cin >> K;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M>> N;
	cout << "All mazes are generated." << endl<<endl;
	int mazeid;
	int x_entry, y_entry;
	int x_exit,y_exit;
	cout << "Enter a maze ID between 1 to " << K<<" inclusive to find a path: " ;
	cin >>mazeid;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> x_entry >> y_entry;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> x_exit >> y_exit;
	// Generation of mazes
	for (int k = 0; k < K; k++){
		vector<vector<cell> > maze(M, vector<cell>(N));
		for (int i = 0; i< M; i++){
			for (int j = 0; j< N; j++){
				maze[i][j].x_ = j;
				maze[i][j].y_ = M-1-i;
				maze[i][j].visited = false;
				maze[i][j].dw = true;
				maze[i][j].uw = true;
				maze[i][j].rw = true;
				maze[i][j].lw = true;
				maze[i][j].down = true;
				maze[i][j].up = true;
				maze[i][j].right = true;
				maze[i][j].left = true;
				if (i==0)
					maze[i][j].up = false;
				if (i == M-1)
					maze[i][j].down = false;
				if (j == 0)
					maze[i][j].left = false;
				if (j == N-1)
					maze[i][j].right = false;
			}
		}
		Stack<cell> mazeStack;
		Stack<string> dirStack;
		int knockedwalls = 0;
		int currenti = M-1;
		int currentj = 0;
		mazeStack.Push(maze[currenti][currentj]);
		maze[currenti][currentj].visited= true;
		while (knockedwalls < (M*N-1)){ //Till we knock down M-N-1 walls, loop will go on.
			cell currentcell = mazeStack.top();
			int nowi = M-1-(currentcell.y_);
			int nowj = currentcell.x_;
			string randdir = giverandomdirection(maze[nowi][nowj]);
			if ((randdir == "up") && (maze[currenti-1][currentj].visited == false)){
				dirStack.Push("up");
				maze[currenti][currentj].uw = false;
				currenti--;
				maze[currenti][currentj].dw = false;
				knockedwalls++;
				mazeStack.Push(maze[currenti][currentj]);
				maze[currenti][currentj].visited=true;
			}
			else if ((randdir == "down") && (maze[currenti+1][currentj].visited == false)){
				dirStack.Push("down");
				maze[currenti][currentj].dw = false;
				currenti++;
				maze[currenti][currentj].uw = false;
				knockedwalls++;
				mazeStack.Push(maze[currenti][currentj]);
				maze[currenti][currentj].visited=true;
			}
			else if ((randdir == "right") && (maze[currenti][currentj+1].visited == false)){
				dirStack.Push("right");
				maze[currenti][currentj].rw = false;
				currentj++;
				maze[currenti][currentj].lw = false;
				knockedwalls++;
				mazeStack.Push(maze[currenti][currentj]);
				maze[currenti][currentj].visited=true;
			}
			else if ((randdir == "left") && (maze[currenti][currentj-1].visited == false)){
				dirStack.Push("left");
				maze[currenti][currentj].lw = false;
				currentj--;
				maze[currenti][currentj].rw = false;
				knockedwalls++;
				mazeStack.Push(maze[currenti][currentj]);
				maze[currenti][currentj].visited=true;
			}
			else if (((maze[currenti][currentj].up==false)||(maze[currenti-1][currentj].visited == true))&&
				((maze[currenti][currentj].down == false)||(maze[currenti+1][currentj].visited == true))&&
				((maze[currenti][currentj].right == false)||(maze[currenti][currentj+1].visited == true)) && 
				((maze[currenti][currentj].left == false)||(maze[currenti][currentj-1].visited == true)) ){
				string prevdir = dirStack.topAndPop();
				mazeStack.Pop();
				cell currentcellrn = mazeStack.top();
				int ci = M-1-(currentcellrn.y_);
				int cj= currentcellrn.x_;
				if (prevdir == "up") {
					maze[ci][cj].up= false;
					currenti++;
				}
				else if (prevdir == "down"){
					maze[ci][cj].down= false;
					currenti--;
				}
				else if (prevdir == "right") {
					maze[ci][cj].right= false;
					currentj--;
				}
				else if (prevdir == "left") {
					maze[ci][cj].left= false;
					currentj++;
				}
			}
		}// 1 maze is generated out of K
		// creating the output file for the first part of the homework
		string filename = "maze_"+to_string(k+1)+".txt";
		ofstream out;
		out.open(filename.c_str(),ios::app);
		out << M <<" " <<  N << endl;
		for (int i = M-1; i>=0;i--){
			for (int j = 0; j< N ; j++){
				out << "x=" << maze[i][j].x_ <<" y="<< maze[i][j].y_ <<" l="<< maze[i][j].lw
					<<" r=" << maze[i][j].rw << " u=" << maze[i][j].uw << " d=" << maze[i][j].dw << endl;
			}
		}
		out.close();
		if (k+1 == mazeid){
			mainmaze = maze;
		}
	} // K mazes are generated
	//SECOND PART OF THE HOMEWORK. PATH DISCOVERY IN A MAZE
	cell startcell, endcell;
	int currenti = M-1-y_entry;
	int currentj = x_entry;
	startcell = mainmaze[currenti][currentj];
	endcell = mainmaze[M-1-y_exit][x_exit];
	Stack<cell> PathStack;
	Stack<string> dirStackP;
	PathStack.Push(startcell);
	cell currentcell = PathStack.top();
	dirStackP.Push("start");
	while(!((currentcell.x_ == endcell.x_) && (currentcell.y_ == endcell.y_))){ //Till we reach the exit numbers(which were taken as input from user)
		int cui = M-1-(currentcell.y_);
		int cuj = currentcell.x_;
		string randdir = giverandomdirection2(mainmaze[cui][cuj]);
		int wallc = wallcount(mainmaze[cui][cuj]);
		string lastdir= dirStackP.top();
		bool opposite = oppositedir(randdir, lastdir);
		if ((randdir == "up") && (lastdir !="down")){
			dirStackP.Push("up");
			currenti--;
			PathStack.Push(mainmaze[currenti][currentj]);
			currentcell = PathStack.top();
		}
		else if ((randdir == "down")&& (lastdir!= "up") ){
			dirStackP.Push("down");
			currenti++;
			PathStack.Push(mainmaze[currenti][currentj]);
			currentcell = PathStack.top();
		}
		else if ((randdir == "right") &&(lastdir !="left")){
			dirStackP.Push("right");
			currentj++;
			PathStack.Push(mainmaze[currenti][currentj]);
			currentcell = PathStack.top();
		}
		else if ((randdir == "left")&&(lastdir != "right")){
			dirStackP.Push("left");
			currentj--;
			PathStack.Push(mainmaze[currenti][currentj]);
			currentcell = PathStack.top();
		}
		else if ((randdir == "no")||((wallc == 3) &&(opposite))){ //either no direction or 1 direction which we already came from
			string prevdir = dirStackP.topAndPop();
			PathStack.Pop();
			cell currentcell = PathStack.top();
			if (prevdir == "up") {
				currenti++;
			}
			else if (prevdir == "down"){
				currenti--;
			}
			else if (prevdir == "right") {
				currentj--;
			}
			else if (prevdir == "left") {
				currentj++;
			}
		}
	}
	// file creation for path discovery
	string ofilename= "maze_"+ to_string(mazeid) +"_path_"+ to_string(x_entry) + "_"+ to_string(y_entry) + "_"+to_string(x_exit) + "_"+to_string(y_exit) + ".txt";
	ofstream out2;
	out2.open(ofilename.c_str(),ios::app);
	Stack<cell> PrintStack;
	while (!PathStack.IsEmpty()){
		cell newcell = PathStack.topAndPop();
		PrintStack.Push(newcell);
	}
	while (!PrintStack.IsEmpty()){
		cell printcell = PrintStack.topAndPop();
		out2 << printcell.x_ << " "<< printcell.y_ << endl;
	}
	out2.close();
	return 0;
}
