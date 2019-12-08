#include<iostream>
#include<fstream>
#include<string>
#include<vector>
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
	bool getStart() {
		return this->start;
	}
	void setFinish(bool finish) {
		this->finish = finish;
	}
	bool getFinish() {
		return this->finish;
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

class Node {
public:
	Node() {}
	Node(Point& start, Node* parent) {
		this->pnt = start;
		this->parent = parent;
	}

	void setG(float g) { this->g = g; }
	void setH(float h) { this->h = h; }
	void setF(float f) { this->f = f; }
	float getG() { return this->g; }
	float getH() { return this->h; }
	float getF() { return this->f; }

	void computeF() {
		this->f = this->g + this->h;
	}
	static float computeH(Point& start, Point& goal) {
		return abs(start.getX() - goal.getX()) + abs(start.getY() - goal.getY());
	}
	void setParent(Node* parent) {
		this->parent = parent;
	}
	Node* getParent() {
		return this->parent;
	}
	void setPoint(Point pnt) {
		this->pnt = pnt;
	}
	Point getPoint() {
		return this->pnt;
	}

	static list<Node> getNeighbours(Point goal, vector<Point> &points) {
		list<Node> neighboursNodes;

		return neighboursNodes;
	}

	~Node()
	{
		this->parent = nullptr;
	}

private:
	Point pnt;
	Node* parent;
	float g;
	float h;
	float f;
};

//закидывать в открытый список по приоритету соседей текущей ноды. для этого: в список берем соседей, исключая препятствия, рассчитываем для них ghf -> в опенед insert по приоритету f, исключая уже взятые в клозд и опенд. 
//далее каррент нода с наименьшим приоритетом, для неё тоже самое
//в конце просто из finish по родительским узлам строим маршрут до старт (отдельной фукнцией)

list<Node> AStar(Point& start, Point& finish, vector<Point> &points) {
	list<Node> opened;
	list<Node> closed;

	Node startNode(start, nullptr);
	startNode.setG(0.0f);            // сколько пройти пришлось до этого узла
	startNode.setH(Node::computeH(start, finish)); // сколько приблизительно еще идти
	startNode.computeF(); //общий приблизительный путь

	opened.push_back(startNode);

	while (!opened.empty()) {
		Node currentNode(opened.front()); //узел на рассмотрении

		if (currentNode.getPoint().getFinish() == true) { //если текущая нода == цель
			return getPathToStartFromFinish(&currentNode);
		}

		closed.push_back(currentNode); //текущий узел рассмотрен
		opened.pop_front();

		auto neighbours = currentNode.getNeighbours(finish, points); //ищем соседей

		for (auto currentNeighbour : neighbours) { //проходимся по каждому соседу
			auto closeNodeIter = find(closed.begin(), closed.end(), currentNeighbour); // если он закрыт, пропускаем его и переходим к следующ
			if (closeNodeIter != closed.end()) continue;

			//ищем соседа в опенд листе
			auto openNodeIter = find(opened.begin(), opened.end(), currentNeighbour);
			if (openNodeIter == opened.end()) {
				//insert(opened, currentNeigbour); написать
			}
			else if (openNodeIter->getG() > currentNeighbour.getG()) {
				openNodeIter->setParent(&closed.back());
				openNodeIter->setG(currentNeighbour.getG());
				openNodeIter->computeF();
			}
		}
		
	}

	//return путь start to finish
}

list<Node> getPathToStartFromFinish(Node* node) { //строим путь до старта от финишной ноды
	list<Node> path;
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

	Point start;
	Point goal;
	for (int i = 0; i < maze.size(); i++)
	{
		if (maze[i].getStart == true) start = maze[i];
		if(maze[i].getFinish == true) goal = maze[i];
	}
	AStar(start, goal, maze);

	system("pause");
	return 0;
}