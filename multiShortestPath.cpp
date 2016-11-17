#include"multiShortestPath.h"


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

		//初始化relaxMap
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
	
	make_heap(que.begin(), que.end(), cmp());//建堆
	
    //dijkstra核心算法
	//bool breakFlag = false;
	while (!que.empty() ) {// ||!breakFlag
		map<int,Node*> S;//已经扫描过的节点集合

		pop_heap(que.begin(), que.end(), cmp());//与que.pop_back()搭配使用
		S.insert(pair<int,Node*>(que.back()->key,que.back()));//出队节点进入集合S,便于以后检索
		que.pop_back();//最小元素出队
		

		//遍历出队节点的邻接节点，更新节点costTillNow
		for (auto &it : S) {//这层循环遍历出队节点
			for (auto &iter : adjMap[it.second->key])//这层循环遍历出队节点的邻接节点
			{
				//两个if完成松弛操作
				if ((it.second->costTillNow + iter.second) < relaxMap[iter.first]->costTillNow)
				{
					relaxMap[iter.first]->costTillNow = it.second->costTillNow + iter.second;//松弛节点,下一个节点的costTillNow = 当前节点的costTillNow + 二者之间边的cost
					relaxMap[iter.first]->prev.clear();
					relaxMap[iter.first]->prev.push_back(it.first);//指向前节点,记录路径，这里是求多条路径的关键点，用vector来存储多个前向节点
				}
				else if ((it.second->costTillNow + iter.second )== relaxMap[iter.first]->costTillNow)
				{
					relaxMap[iter.first]->prev.push_back(it.first);
				}
			}
		}
		make_heap(que.begin(), que.end(), cmp());//松弛之后重置堆
	}//end of while
}

void multiShortestPath::display()
{
	cout << "所有的最短路径：" << endl;
	dfs(destination);
}


multiShortestPath::~multiShortestPath()
{
	for (auto &it : relaxMap)
	{
		delete it.second;
	}
}
