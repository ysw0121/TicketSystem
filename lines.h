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
		int cond=0;//记录查询状态
		int distance=0;//到下一站距离
		int sub_distance = 0;//到上一站距离
	};
	string number;
	int stat_num = 0;
	station st[STATNUM];

	////------------------------------------------------------------------------------------
	////******链式前向星--------------------------------------------------------
	//map<string, int>head;
	//struct stat_edge {
	//	string to;//下一个站点标号
	//	int val;//路线长度
	//	int next;//同一点的下一个边的编号
	//	int lin;//哪条线路
	//};
	//stat_edge edge[1000];//边
	////head[1000] ;//第一条边位置
	//int cnt = 0;
	//void add_edge(string start, string end, int v) {
	//	edge[cnt].to = end; //终点
	//	edge[cnt].val = v; //权值
	//	edge[cnt].next = head[start];//以u为起点上一条边的编号，也就是与这个边起点相同的上一条边的编号
	//	head[start] = cnt++;//更新以u为起点上一条边的编号
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
		if (!in_file)cout << "--------------文件打开失败----------------" << endl;
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