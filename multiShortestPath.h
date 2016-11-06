#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<queue>
#include <algorithm>
using namespace std;

class Node {//����relaxMap��
public:
	int key;
	int costTillNow = INT_MAX;//���ýڵ�Ϊֹ��cost���ɳڵ�ʱ����õ�
	bool isPassed = false;//�Ƿ�ɨ���
	vector<int> prev;//ǰ��ڵ㡣��Ϊ�Ƕ������·��������ǰ��ڵ�����ж��

	Node(int k):key(k) {};
};

//dijkstra�㷨�е����ȶ��еıȽϺ�������Ϊqueue�д洢����Nodeָ�����ʽ��
//��������ȽϺ�������д��Node����
struct cmp {
	bool operator()(const Node * a, const Node * b) {
		return a->costTillNow > b->costTillNow;
	}
};

class multiShortestPath
{
private:
	map<int, vector<pair<int,int>> > adjMap;//�ڽӱ�,pair<des,cost>,�ڽӱ���Ҫ�����Ǽ�¼�ߣ������Ժ����ĳ���ߵ�Ȩֵ
	map<int, Node*> relaxMap;//dijkstra�㷨��������Ҫά�������нڵ㣬���������ɳڲ������Ұѽڵ�ͱ߷ֿ��ˣ�Node�в���������next�����Ĵ���ߵĳ�Ա���������еı߶������洢��adjMap����
	
	int source;//��¼�������ֵ����displayʹ��
	int destination;//��¼Ŀ�ĵص�ֵ����displayʹ��
	vector<int> path;//��¼·������displayʹ��
	void dfs(int nodeKey);//��dfs��������������·��
public:
	void makeMap(string path);//�����ڽӱ��relaxMap
	void dijkstra(int src, int des);
	void display();

	~multiShortestPath();//�ͷ�relaxMapռ�õ��ڴ�
};