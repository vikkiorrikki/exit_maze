#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<list>

using namespace std;

//как хранить лабиринт. точки, координаты
//алгоритм работы с лабиринтом

class Point {
public:
	Point() {
		x = y = 0;
		block = false;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setBlock(bool block) {
		//this->border = true;
		this->block = block;
	}
	void setStart(bool start) {
		this->start = start;
	}
	void setFinish(bool finish) {
		this->finish = finish;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	void Print() {
		cout << "X = " << x << "\tY = " << y << endl;
	}
private:
	int x;
	int y;
	//bool border; //граница лабиринта
	bool block; //препятствие лабиринта
	bool start = false;
	bool finish = false;
};

void AStar(Point start, Point finish) {
	priority_queue<Point> open_points;
	list<Point> close_points;


	//return путь start to finish
}

int main() {
	//string path = "d:\\projects\\git\\exit_maze\\ConsoleApplication1\\maze.txt";
	string path = "c:\\study\\github\\exit_maze_project\\Project1\\maze.txt";
	ifstream fmaze;
	fmaze.open(path);

	vector<Point> maze;

	if (!fmaze.is_open()) {
		cout << "File is not opened!" << endl;
	}
	else {
		cout << "File is opened!" << endl;

		char ch;
		Point pnt;

		for (int y = 0; fmaze.get(ch); y++)
		{
			for (int x = 0; ch != '\n'; x++)
			{
				if (ch == '*') {
					pnt.setX(x);
					pnt.setY(y);
					pnt.setBlock(true);
					pnt.setStart(false);
					pnt.setFinish(false);
					maze.push_back(pnt);
					fmaze.get(ch);
				}
				else {
					pnt.setX(x);
					pnt.setY(y);
					pnt.setBlock(false);
					if (pnt.getY() == 0) pnt.setStart(true);
					if (pnt.getY() == 5) pnt.setFinish(true);
					maze.push_back(pnt);
					fmaze.get(ch);
				}
			}
		}
	}
	for (int i = 0; i < maze.size(); i++) {
		maze[i].Print();
	}



	fmaze.close();
	system("pause");
	return 0;
}