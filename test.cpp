#include"PBM.h"

int main()
{
	multiShortestPath m;
	m.makeMap("case0.txt");
	m.dijkstra(1,6);//�������������ͼ��ĵ㣬����ᱨ��
	m.display();
	cin.get();
	return 0;
}