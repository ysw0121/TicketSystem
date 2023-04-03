#ifndef MY_MAP
#define MY_MAP
#include"lines.h"
#include<stdlib.h>
#include<Windows.h>
using namespace std;
const int MAXLINE = 30;
const int LINE_SUM = 10;
const int MAXN = 1500;
const int  MAXMAX = 9999;
const int MAXST = 300;
class mymap {

public:
	mylines L[MAXLINE];

	//******链式前向星--------------------------------------------------------
	unordered_map<string, int>pot;
	unordered_map<int, string>pt;
	struct TO {
		int to;
		int endf=0;//判断是不是线路的终点，1为是终点//  实际无用
	};
	struct stat_edge {
		TO to;//下一个站点标号
		int val;//路线长度
		int next;//同一点的下一个边的编号
		int lin_num;
		int lin[LINE_SUM];//哪条线路
		
	};
	stat_edge edge[MAXN];//边
	int head[MAXN];//第一条边位置，赋值-1
	int cnt = 0,sub_cnt=0;
	void add_edge(string start, string end, int v,int i,int flag) {
		if (flag == 0) {
			edge[cnt].lin[edge[cnt].lin_num] = i;
			edge[cnt].lin_num++;
		}
		edge[cnt].to.to = pot[end]; //终点
		edge[cnt].val = v; //权值
		edge[cnt].next = head[pot[start]];//以为起点上一条边的编号，也就是与这个边起点相同的上一条边的编号
		head[pot[start]] = cnt++;//更新以u为起点上一条边的编号
	}
	
		//---------------------------------------------------------------------------------------------------------------

public:

	void init() {
		L[0].createline("line1.txt");
		L[1].createline("line2.txt");
		L[2].createline("line3.txt");
		L[3].createline("line4.txt");
		L[4].createline("line10.txt");
		L[5].createline("lines1.txt");
		L[6].createline("lines3.txt");
		L[7].createline("lines7.txt");
		L[8].createline("lines8.txt");
		L[9].createline("lines9.txt");


		for (int i = 0; i < MAXN; i++)head[i] = -1, edge[i].lin_num = 0;
		int p = 0;
		
		for (int i = 0; i < LINE_SUM; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {
				int fla = 0;
				if (fla == 0) {
					pot[L[i].st[j].name] = p;
					pt[p] = L[i].st[j].name;
					p++;
				}
			}
		}
		for (int i = 0; i < LINE_SUM; i++) {
			for (int j = 0; j < L[i].stat_num - 1; j++) {
				add_edge(L[i].st[j].name, L[i].st[j + 1].name,  L[i].st[j].distance, i, 0);
				
				add_edge(L[i].st[j + 1].name, L[i].st[j].name, L[i].st[j + 1].sub_distance, i, 1);
			}
		}
		//----------------------------------  test  --------------------------------------------------------
				/*for (int i = 0; i < p; i++) {
					for (int j = head[i]; j != -1; j = edge[j].next) {
						for (int k = 0; k < edge[j].lin_num; k++)cout << L[edge[j].lin[k]].number << "号线  " << endl;
						cout <<i<< pt[i] << " " << edge[j].to<<pt[edge[j].to] << " " << edge[j].val << endl;
					}
				}
				return;*/
		//---------------------------------------------------------------------------------------------------

		cout << "\n\n-------------------------\\\\欢迎来到南京地铁售票系统，请输入下面的选项编号来选择你要进行的服务//------------------------\n" << endl;
		cout << "-----------------------------\\\\1.查询路线     2.查询站点    3.查询乘车方案及购票   4.退出//----------------------------	\n" << endl;
		string s;
		cout << ">>>";
		cin >> s;
		while (s != "4") {
			if (s == "1") {
				search_line();
				s = "0";
				Sleep(1300);
				system("cls");
			}
			if (s == "2") {
				search_station();
				s = "0";
				Sleep(1300);
				system("cls");
			}
			if (s == "3") {
				search_rout();
				s = "0";
				Sleep(1300);
				system("cls");
			}
			if (s == "0") {
				cout << "\n-------------------------------------\\请继续输入编号来选择你要进行的服务/------------------------------------------\n" << endl;
				cout << "------------------------\\1.查询路线     2.查询站点    3.查询乘车方案及购票   4.退出/------------------------------\n" << endl;
				cout << ">>>";
			}
			else {
				cout << "\n-----------------------------------没有该选项，请输入正确选项选择服务-------------------------------------------\n" << endl;
				cout << "------------------------1.查询路线     2.查询站点    3.查询乘车方案及购票   4.退出------------------------------\n" << endl;
				cout << ">>>";
			}
			cin >> s;
		}
		cout << "\n--------------------------------------------- ^~ 谢谢使用，再见 ~^ -----------------------------------------------------" << endl;
		system("pause");
		return;
	}


private:

	void output_line(string s) {//用户查询用
		int h = 0;
		h = atoi(s.c_str()) - 1;
		if (h < 0 || h >= 10) {
			cout << "--------------------您所查询的路线不存在，请重新输入------------------------" << endl;
			cout << "\n" << endl;
			return;
		}
		cout << "您所查询的是" << L[h].number << "号线：\n" << endl;
		cout << "		";
		for (int i = 0; i < L[h].stat_num; i++) {
			if (i != L[h].stat_num - 1) {
				cout << L[h].st[i].name << "—>";
				if (i % 5 == 4 && i != L[h].stat_num - 2)cout << endl, cout << "		";
			}
			else cout << L[h].st[i].name << endl;
		}
		cout << endl;
		if (s == "0")return;
	}

	void search_line() {
		cout << endl;
		cout << "南京地铁当前运行的路线：\n\n\t1. 一号线  2. 二号线 3. 三号线 4. 四号线  5. 十号线  6. S1号线  7. S3号线  8. S7号线 9. S8号线  10. S9号线\n" << endl;
		Sleep(1000);
		cout << "-------------------请输入您想查询的线路的编号，如需结束请输入 0 --------------------" << endl;
		string s;
		cout << ">>>";
		cin >> s;
		while (s != "0") {
			output_line(s);
			Sleep(1200);
			cout << "\n" << endl;
			cout << "\n------------------您可以继续查询其他线路，如需结束请输入 0 ---------------------\n" << endl;
			cout << ">>>";
			cin >> s;
		}
		if (s == "0")return;
	}

	void output_station(string s) {
		int flag = 0;


		struct tep {
			int cnt = 1;
			string name;
			string LIN[20];
		};
		tep p[99];
		int q = 1;
		int q1[99] = { 0 };//记录每一选项的换乘线路的条数

		for (int i = 0; i < LINE_SUM ; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {

				int index = L[i].st[j].name.find(s);
				int len = L[i].st[j].name.length();
				//直接匹配------------------------------------------------------------------------------------------------------//-
				if ((s == L[i].st[j].name || s + "站" == L[i].st[j].name) && s != "南京" && s != "南京南") {                                                                                                                //
					flag = 1;
					if (L[i].st[j].cond == 0) {
						cout << "\n" << endl;
						cout << "您查找的  " << L[i].st[j].name << "站位于：" << L[i].number << "号线";
						for (int k = i + 1; k < LINE_SUM; k++) {
							for (int m = 0; m < L[k].stat_num; m++) {
								if (L[i].st[j].name == L[k].st[m].name) {
									cout << "、" << L[k].number << "号线";
									L[k].st[m].cond = 1;
								}
							}
						}
						cout << "\n" << endl;
					}
				}																																						//
//------------------------------------------------------------------------------------------------------------------
// 关键词匹配-----------------------------------------------------------------------------------------------------
				if (s != L[i].st[j].name && index%2==0) {
					flag = 1;
					if (L[i].st[j].cond == 0) {
						p[q].cnt = q;
						p[q].name = L[i].st[j].name;
						p[q].LIN[q1[q]] = L[i].number;
						if (q == 1)cout << "\n您可能要查找 ： ";
						cout << q << "." << L[i].st[j].name << "站   ";
						//内部查找--------------------------------------------
						for (int k = i + 1; k < LINE_SUM; k++) {
							for (int m = 0; m < L[k].stat_num; m++) {
								if (L[i].st[j].name == L[k].st[m].name) {
									q1[q]++;
									p[q].LIN[q1[q]] += L[k].number;
									L[k].st[m].cond = 1;
								}
							}
						}
						//------------------------------------------------------------
						L[i].st[j].cond = 1;
						q++;

					}
				}
			}
		}
		if (q > 1) {
			cout << endl;
			cout << "\n------------------请选择你想要查询的站，输入对应编号，可在此多次查询，如需结束请输入99--------------------" << endl;
			cout << ">>>";
			//int temp=0;
			string temp;
			//getline(cin, temp);
			cin >> temp;
			while (temp != "99") {
				if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//注意q最后++
					cout << "\n>>>>>>>>>>>不在选项范围内，请重新输入，如需结束请输入99\n" << endl;
				}
				else {
					for (int i = 1; i < q; i++) {
						if (atoi(temp.c_str()) == i) {
							cout << "\n您查询的 " << p[i].name << "站  位于";
							for (int j = 0; j <= q1[i]; j++) {
								cout << p[i].LIN[j] << "号线";
								if (j != q1[i])cout << "、";
							}
							cout << endl;
							break;
						}
						else continue;
					}
					cout << "\n--------------------------------您可以继续查询其他选项，如需结束请输入 99---------------------------------------\n" << endl;
				}
				cout << ">>>";
				cin >> temp;
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------
		if (flag == 0)cout << "\n>>>>>>>>>查无此站，请重新输入\n" << endl;
		for (int i = 0; i < LINE_SUM; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {
				L[i].st[j].cond = 0;//归零，后续再使用
			}
		}
	}

	void search_station() {
		cout << "\n-------------------请输入您想查询的站点，如需结束请输入 0 --------------------\n" << endl;
		cout << "\n****************     如需查看路线，请输入r  \n" << endl;
		string s;
		cout << ">>>";
		cin >> s;
		while (s != "0") {
			if (s == "r") {
				search_line();
			}
			else {
				output_station(s);
			}
			Sleep(1000);
			cout << "\n";
			cout << "------------------您可以继续查询其他站点，如需结束请输入 0 ---------------------\n" << endl;
			cout << "\n****************     如需查看路线，请输入r  \n" << endl;
			cout << ">>>";
			cin >> s;
		}
	}

	int ticket_price(unsigned int len) {//票价计算
		if (len >= 0 && len <= 10000) return 2;
		else if (len > 10000 && len <= 16000)return 3;
		else if (len > 16000 && len <= 22000)return 4;
		else if (len > 22000 && len <= 30000)return 5;
		else if (len > 30000 && len <= 38000)return 6;
		else if (len > 38000 && len <= 48000)return 7;
		else if (len > 48000 && len <= 58000)return 8;
		else if (len > 58000 && len <= 70000)return 9;
		else if (len > 70000) {
			return 10 + (len - 70000) / 14000;
		}
	}

	int visit[200];
	vector <string>rout;
	int val=0;
	int count = 0;
	int min = 21474836;

	string user_head;
	int times=0;

	void min_routine(int start, int end,int len) {//路线规划
		int temp=edge[start].next;
		int temp1 = edge[temp].next;
		const int tem = start;	
		if (start == end) {
			if (min > len) {
				min = len;
				if (min < 1.3*len) {
					count++;
					cout << "第" << count << "条路线： ";
					cout << user_head << "—>";
					
					for (int j = 0; j < rout.size(); j++) {
						if (j != rout.size() - 1)cout << rout[j] << "—>"; 
						else cout << rout[j]<<endl;
					}

					cout <<"\n\n" << endl;
				}
			}
			return;
		}
		else{
				for (int i = head[start]; i != -1; i = edge[i].next) {
					int t = edge[i].to.to;
					if (!visit[t]) {
						rout.push_back(pt[t]);
						visit[t] = 1;
						min_routine(t, end, len + edge[i].val);
						rout .pop_back();
						visit[t] = 0;
					}
				}
		}
	}


	void search_rout() {
		while (true) {
		loop1:	cout << "\n-------------------------------------------请输入您的始发站，如需退出请输入 0-----------------------------------------\n" << endl;

			string start, end;
			string s;

			cout << ">>>";
			cin >> s;
			if (s == "0")return;
			else {
				int flag = 0;
				string p[99];
				int q = 1;
				for (int i = 0; i < LINE_SUM - 1; i++) {
					for (int j = 0; j < L[i].stat_num; j++) {
						int index = L[i].st[j].name.find(s);
						int len = L[i].st[j].name.length();
						//直接匹配------------------------------------------------------------------------------------------------------//
						if (s == L[i].st[j].name) {                                                                                                                //
							flag = 1;
							start = s;
							break;
						}																																						//
		//------------------------------------------------------------------------------------------------------------------
		// 关键词匹配-----------------------------------------------------------------------------------------------------
						if (s != L[i].st[j].name && index%2==0) {
							flag = 1;
							for (int k = 1; k <= q; k++) {
								if (p[k] == L[i].st[j].name) {
									flag = 2; break;
								}
							}
							if (L[i].st[j].cond == 0 && flag != 2) {
								if (q == 1)cout << "\n您可能要选择 ： ";
								cout << q << "." << L[i].st[j].name << "站   ";
								L[i].st[j].cond = 1;
								p[q] = L[i].st[j].name;
								q++;
							}
						}
					}
				}
				if (q > 1) {
					cout << endl;
					cout << "\n------------------------请选择你想要的始发站，输入对应编号---------------------------" << endl;
					cout << ">>>";
					string temp;
					cin >> temp;
					while (true) {
						if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//注意q最后++
							cout << "\n>>>>>>>>>>>>>不在选项范围内，请重新输入\n" << endl;
							cout << ">>>";
						}
						else {
							for (int i = 1; i < q; i++) {
								if (atoi(temp.c_str()) == i) {
									start = p[i];
									break;
								}
								else continue;
							}
							break;
						}
						cin >> temp;
					}
				}
				//--------------------------------------------------------------------------------------------------------------------------
				if (flag == 0) { cout << "\n>>>>>>>>>查无此站，请重新输入\n" << endl; goto loop1;; }
				for (int i = 0; i < LINE_SUM; i++) {
					for (int j = 0; j < L[i].stat_num; j++) {
						L[i].st[j].cond = 0;//归零，后续再使用
					}
				}
			}
			//***********************************************************************************************************************
		loop2:		cout << "\n-------------------------------------------请输入您的终点站，如需退出请输入 0-----------------------------------------\n" << endl;
				cout << ">>>";
				cin >> s;
				if (s == "0")return;
				else {
					int flag = 0;
					string p[99];
					int q = 1;
					for (int i = 0; i < LINE_SUM - 1; i++) {
						for (int j = 0; j < L[i].stat_num; j++) {
							int index = L[i].st[j].name.find(s);
							int len = L[i].st[j].name.length();
							//直接匹配------------------------------------------------------------------------------------------------------//
							if (s == L[i].st[j].name) {                                                                                                                //
								flag = 1;
								end = s;
								break;
							}																																						//
			//------------------------------------------------------------------------------------------------------------------
			// 关键词匹配-----------------------------------------------------------------------------------------------------
							if (s != L[i].st[j].name && index%2==0) {
								flag = 1;
								for (int k = 1; k <= q; k++) {
									if (p[k] == L[i].st[j].name) {
										flag = 2; break;
									}
								}
								if (L[i].st[j].cond == 0 && flag != 2) {
									if (q == 1)cout << "\n您可能要选择 ： ";
									cout << q << "." << L[i].st[j].name << "站   ";
									L[i].st[j].cond = 1;
									p[q] = L[i].st[j].name;
									q++;
								}
							}
						}
					}
					if (q > 1) {
						cout << endl;
						cout << "\n--------------------------请选择你想要的终点站，输入对应编号--------------------------" << endl;
						cout << ">>>";
						string temp;
						cin >> temp;
						while (true) {
							if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//注意q最后++
								cout << "\n>>>>>>>>>>>>>不在选项范围内，请重新输入\n" << endl;
								cout << ">>>";
							}
							else {
								for (int i = 1; i < q; i++) {
									if (atoi(temp.c_str()) == i) {
										end = p[i];
										break;
									}
									else continue;
								}
								break;
							}
							cin >> temp;
						}
					}
					//--------------------------------------------------------------------------------------------------------------------------
					if (flag == 0) {
						cout << "\n>>>>>>>>>查无此站，请重新输入\n" << endl; goto loop2;
					}
					for (int i = 0; i < LINE_SUM; i++) {
						for (int j = 0; j < L[i].stat_num; j++) {
							L[i].st[j].cond = 0;//归零，后续再使用
						}
					}
				}
			//*********************************************************************************************************************************
			if (start == end) {
				cout << "\n>>>>>>>>>>>>>>>>  您可以直接进站后出站，或者根据您的心情乘坐\n" << endl;
				cout << "\n>>>>>>>>>>>>>>>>  始发站与终点站重合，根据规定，票价2元\n" << endl;
			}
			else { 
				cout << "\n>>>>>>>>>>>您可以选择的路线如下，#--  其中最后一条路线为距离最短路线  --#\n" << endl;
				cout << "\n******************请注意：若有多条路线，前面的路线通常较长，请谨慎选择！！\n\n" << endl;
				user_head = start;
				min_routine(pot[start], pot[end], 0);
				cout <<"\n>>>>>>>>>>最短里程："<<min << "米，票价：" << " " << ticket_price(min) << " 元\n" << endl;
			}
			memset(visit, 0, sizeof(visit));
			min = 21474836;
			count = 0;
	
		loop:cout << "\n----------------------------------------是否继续？继续则输入y，否则输入n-------------------------------------------\n" << endl;
			cout << ">>>";
			cin >> s;
			if (s == "y")continue;
			else if (s == "n")return;
			else {
				cout << "\n>>>>>>>>>>>>>>>>>>非法输入！请正确输入\n" << endl;
				goto loop;
			}
		}
	}

	

};
#endif