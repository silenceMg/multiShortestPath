#include"PBM.h"

int main()
{
	multiShortestPath m;
	m.makeMap("case0.txt");
	m.dijkstra(1,6);//输入参数不能是图外的点，否则会报错
	m.display();
	cin.get();
	return 0;
}