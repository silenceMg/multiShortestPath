#include"PBM.h"


void multiShortestPath::dfs(int nodeKey)
{
	if (nodeKey == source)
	{
		for (int i = path.size()-1;i>=0;i--)
		{
			if (i != 0)
				cout << path[i] << "->";
			else
				cout << path[i]<<endl;
		}
		return;
	}
	for (auto &it : relaxMap[nodeKey]->prev)
	{
		path.push_back(it);
		dfs(it);
		path.pop_back();
	}
}


void multiShortestPath::makeMap(string path)
{
	fstream fs(path);
	if (!fs.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	int NodeNum, edgeNum, tmp_src, tmp_des, tmp_cost;
	fs >> NodeNum >> edgeNum;

	for (int i = 1; i <= edgeNum; ++i)
	{
		fs >> tmp_src >> tmp_des >> tmp_cost;
		if (adjMap.find(tmp_src) != adjMap.end())
		{
			adjMap[tmp_src].push_back(pair<int, int>(tmp_des, tmp_cost));
		}
		else
		{
			adjMap[tmp_src] = vector<pair<int, int>>{ pair<int, int>(tmp_des, tmp_cost) };
		}

		//��ʼ��relaxMap
		if (relaxMap.find(tmp_src) == relaxMap.end())
		{
			relaxMap[tmp_src] = new Node(tmp_src);
		}
		if (relaxMap.find(tmp_des) == relaxMap.end())
		{
			relaxMap[tmp_des] = new Node(tmp_des);
		}

	}

	fs.close();
}



void multiShortestPath::dijkstra(int src, int des)
{
	source = src;
	destination = des;
	path.push_back(des);

	vector<Node*> que;
	relaxMap[src]->costTillNow = 0;
	
	for (auto &it : relaxMap)
	{
		que.push_back(it.second);
	}
	
	make_heap(que.begin(), que.end(), cmp());//����
	
    //dijkstra�����㷨
	//bool breakFlag = false;
	while (!que.empty() ) {// ||!breakFlag
		map<int,Node*> S;//�Ѿ�ɨ����Ľڵ㼯��

		pop_heap(que.begin(), que.end(), cmp());//��que.pop_back()����ʹ��
		S.insert(pair<int,Node*>(que.back()->key,que.back()));//���ӽڵ���뼯��S,�����Ժ����
		que.pop_back();//��СԪ�س���
		

		//�������ӽڵ���ڽӽڵ㣬���½ڵ�costTillNow
		for (auto &it : S) {//���ѭ���������ӽڵ�
			for (auto &iter : adjMap[it.second->key])//���ѭ���������ӽڵ���ڽӽڵ�
			{
				//����if����ɳڲ���
				if ((it.second->costTillNow + iter.second) < relaxMap[iter.first]->costTillNow)
				{
					relaxMap[iter.first]->costTillNow = it.second->costTillNow + iter.second;//�ɳڽڵ�,��һ���ڵ��costTillNow = ��ǰ�ڵ��costTillNow + ����֮��ߵ�cost
					relaxMap[iter.first]->prev.clear();
					relaxMap[iter.first]->prev.push_back(it.first);//ָ��ǰ�ڵ�,��¼·���������������·���Ĺؼ��㣬��vector���洢���ǰ��ڵ�
				}
				else if ((it.second->costTillNow + iter.second )== relaxMap[iter.first]->costTillNow)
				{
					relaxMap[iter.first]->prev.push_back(it.first);
				}
			}
		}
		make_heap(que.begin(), que.end(), cmp());//�ɳ�֮�����ö�
	}//end of while
}

void multiShortestPath::display()
{
	cout << "���е����·����" << endl;
	dfs(destination);
}


multiShortestPath::~multiShortestPath()
{
	for (auto &it : relaxMap)
	{
		delete it.second;
	}
}