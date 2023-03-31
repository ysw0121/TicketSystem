#ifndef LINES
#define LINES
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<cstring>
#include<list>
using namespace std;
const int STATNUM = 100;
class mylines {
public:
	struct station {
		string name;
		int cond=0;//��¼��ѯ״̬
		int distance=0;//����һվ����
		int sub_distance = 0;//����һվ����
	};
	string number;
	int stat_num = 0;
	station st[STATNUM];

	////------------------------------------------------------------------------------------
	////******��ʽǰ����--------------------------------------------------------
	//map<string, int>head;
	//struct stat_edge {
	//	string to;//��һ��վ����
	//	int val;//·�߳���
	//	int next;//ͬһ�����һ���ߵı��
	//	int lin;//������·
	//};
	//stat_edge edge[1000];//��
	////head[1000] ;//��һ����λ��
	//int cnt = 0;
	//void add_edge(string start, string end, int v) {
	//	edge[cnt].to = end; //�յ�
	//	edge[cnt].val = v; //Ȩֵ
	//	edge[cnt].next = head[start];//��uΪ�����һ���ߵı�ţ�Ҳ����������������ͬ����һ���ߵı��
	//	head[start] = cnt++;//������uΪ�����һ���ߵı��
	//}//---------------------------------------------------------------------------------------------------------------

public:
	station* createline(string filename) {
		if (filename == "line1.txt")number = "1";
		if (filename == "line2.txt")number = "2";
		if (filename == "line3.txt")number = "3";
		if (filename == "line4.txt")number = "4";
		if (filename == "line10.txt")number = "10";
		if (filename == "lines1.txt")number = "S1";
		if (filename == "lines3.txt")number = "S3";
		if (filename == "lines7.txt")number = "S7";
		if (filename == "lines8.txt")number = "S8";
		if (filename == "lines9.txt")number = "S9";

		ifstream in_file(filename, ios::in);
		if (!in_file)cout << "--------------�ļ���ʧ��----------------" << endl;
		int i = 0;
		st[i].sub_distance = 0;
		st[i].cond = 0;
		in_file >> st[i].name >> st[i].distance;
		while (!in_file.fail()) {
			i++;
			in_file>> st[i].name >> st[i].distance;
			st[i].sub_distance = st[i-1].distance;
			st[i].cond = 0;
		}

		st[i].distance = 0;
		stat_num = i+1;
		in_file.close();
		return st;
	}

	

};
#endif