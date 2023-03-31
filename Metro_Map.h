#ifndef MY_MAP
#define MY_MAP
#include"lines.h"
#include<stdlib.h>
#include<Windows.h>
using namespace std;
const int MAXLINE = 30;
int LINE_SUM = 10;
class mymap {
	
public:
	mylines L[MAXLINE];

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
		cout << "\n\n-------------------------\\\\欢迎来到南京地铁售票系统，请输入下面的选项编号来选择你要进行的服务//------------------------\n" << endl;
		cout << "-----------------------------\\\\1.查询路线     2.查询站点    3.查询乘车方案及购票   4.退出//----------------------------	\n" << endl;
		string s;
		cout << ">>>";
		cin >> s;
		while (s != "4") {
			if (s == "1") {
				search_line(); s = "0";
			}

			if (s == "2"){
				search_station(); s = "0";
		    }

			//else if (s == "3")continue;

			

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
		//if (s == "4") {
			cout << "\n----------------------------------谢谢使用，再见--------------------------------------" << endl;
			return;
		//}
	}

private:

	void output_line(string s) {//用户查询用
		int h = 0;
		h = atoi(s.c_str()) - 1;
		if(h<0||h>=10){
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
		while (s!="0") {
			output_line(s);
			Sleep(1200);
			cout << "\n"<<endl;
			cout << "\n------------------您可以继续查询其他线路，如需结束请输入 0 ---------------------\n" << endl;
			cout << ">>>";
			cin >> s;
		}
		if(s=="0")return;
	}

	void output_station(string s) {
		int flag = 0;
		

		struct tep{
			int cnt=1;
			string name;
			string LIN[20];
		};
		tep p[99];
		int q = 1;
		int q1[99] = { 0 };//记录每一选项的换乘线路的条数

		for (int i = 0; i < LINE_SUM - 1; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {

				int index = L[i].st[j].name.find(s);
				int len = L[i].st[j].name.length();
//直接匹配------------------------------------------------------------------------------------------------------//-
				if ((s == L[i].st[j].name||s+"站"==L[i].st[j].name)&&s!="南京"&&s!="南京南") {                                                                                                                //
					flag = 1;
					if (L[i].st[j].cond == 0) {
						cout << "\n" << endl;
						cout << "您查找的  " << L[i].st[j].name << "站位于：" << L[i].number << "号线";
						for (int k = i + 1; k < LINE_SUM ; k++) {
							for (int m = 0; m < L[k].stat_num; m++) {
								if (L[i].st[j].name == L[k].st[m].name) {
									cout << "、" << L[k].number << "号线";
									L[k].st[m].cond = 1;
								}
							}
						}
						cout <<"\n" << endl;
					}
				}																																						//
//------------------------------------------------------------------------------------------------------------------
// 关键词匹配-----------------------------------------------------------------------------------------------------
				if (s != L[i].st[j].name&&index !=-1) {
					flag = 1;
					if (L[i].st[j].cond == 0) {
						p[q].cnt = q;
						p[q].name = L[i].st[j].name;
						p[q].LIN[q1[q]] = L[i].number;
						if(q==1)cout << "\n您可能要查找 ： "; 
						cout<<q<< "." << L[i].st[j].name << "站   ";
						//内部查找--------------------------------------------
						for (int k = i+1; k < LINE_SUM ; k++) {
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
		if (q > 1 ) {
			cout << endl;
			cout << "\n------------------请选择你想要查询的站，输入对应编号，可在此多次查询，如需结束请输入99--------------------" << endl;
			cout << ">>>";
			//int temp=0;
			string temp;
			//getline(cin, temp);
			cin >> temp;
			while (temp !="99") {
				if (atoi(temp.c_str())>=q || atoi(temp.c_str()) <= 0) {//注意q最后++
					cout << "\n>>>>>>>>>>>不在选项范围内，请重新输入，如需结束请输入99\n" << endl;
				}
				else {
					for (int i = 1; i < q; i++) {
						if (atoi(temp.c_str()) ==i) {
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
		if(flag==0)cout << "\n>>>>>>>>>查无此站，请重新输入\n" << endl;
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

	void init_map() {

	}

	void routine(string start, string end) {//路线规划

	}

	int ticket_price(int len) {//票价计算
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

};
#endif