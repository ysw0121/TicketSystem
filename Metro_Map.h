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

	//******��ʽǰ����--------------------------------------------------------
	unordered_map<string, int>pot;
	unordered_map<int, string>pt;
	struct TO {
		int to;
		int endf=0;//�ж��ǲ�����·���յ㣬1Ϊ���յ�//  ʵ������
	};
	struct stat_edge {
		TO to;//��һ��վ����
		int val;//·�߳���
		int next;//ͬһ�����һ���ߵı��
		int lin_num;
		int lin[LINE_SUM];//������·
		
	};
	stat_edge edge[MAXN];//��
	int head[MAXN];//��һ����λ�ã���ֵ-1
	int cnt = 0,sub_cnt=0;
	void add_edge(string start, string end, int v,int i,int flag) {
		if (flag == 0) {
			edge[cnt].lin[edge[cnt].lin_num] = i;
			edge[cnt].lin_num++;
		}
		edge[cnt].to.to = pot[end]; //�յ�
		edge[cnt].val = v; //Ȩֵ
		edge[cnt].next = head[pot[start]];//��Ϊ�����һ���ߵı�ţ�Ҳ����������������ͬ����һ���ߵı��
		head[pot[start]] = cnt++;//������uΪ�����һ���ߵı��
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
						for (int k = 0; k < edge[j].lin_num; k++)cout << L[edge[j].lin[k]].number << "����  " << endl;
						cout <<i<< pt[i] << " " << edge[j].to<<pt[edge[j].to] << " " << edge[j].val << endl;
					}
				}
				return;*/
		//---------------------------------------------------------------------------------------------------

		cout << "\n\n-------------------------\\\\��ӭ�����Ͼ�������Ʊϵͳ�������������ѡ������ѡ����Ҫ���еķ���//------------------------\n" << endl;
		cout << "-----------------------------\\\\1.��ѯ·��     2.��ѯվ��    3.��ѯ�˳���������Ʊ   4.�˳�//----------------------------	\n" << endl;
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
				cout << "\n-------------------------------------\\�������������ѡ����Ҫ���еķ���/------------------------------------------\n" << endl;
				cout << "------------------------\\1.��ѯ·��     2.��ѯվ��    3.��ѯ�˳���������Ʊ   4.�˳�/------------------------------\n" << endl;
				cout << ">>>";
			}
			else {
				cout << "\n-----------------------------------û�и�ѡ���������ȷѡ��ѡ�����-------------------------------------------\n" << endl;
				cout << "------------------------1.��ѯ·��     2.��ѯվ��    3.��ѯ�˳���������Ʊ   4.�˳�------------------------------\n" << endl;
				cout << ">>>";
			}
			cin >> s;
		}
		cout << "\n--------------------------------------------- ^~ ллʹ�ã��ټ� ~^ -----------------------------------------------------" << endl;
		system("pause");
		return;
	}


private:

	void output_line(string s) {//�û���ѯ��
		int h = 0;
		h = atoi(s.c_str()) - 1;
		if (h < 0 || h >= 10) {
			cout << "--------------------������ѯ��·�߲����ڣ�����������------------------------" << endl;
			cout << "\n" << endl;
			return;
		}
		cout << "������ѯ����" << L[h].number << "���ߣ�\n" << endl;
		cout << "		";
		for (int i = 0; i < L[h].stat_num; i++) {
			if (i != L[h].stat_num - 1) {
				cout << L[h].st[i].name << "��>";
				if (i % 5 == 4 && i != L[h].stat_num - 2)cout << endl, cout << "		";
			}
			else cout << L[h].st[i].name << endl;
		}
		cout << endl;
		if (s == "0")return;
	}

	void search_line() {
		cout << endl;
		cout << "�Ͼ�������ǰ���е�·�ߣ�\n\n\t1. һ����  2. ������ 3. ������ 4. �ĺ���  5. ʮ����  6. S1����  7. S3����  8. S7���� 9. S8����  10. S9����\n" << endl;
		Sleep(1000);
		cout << "-------------------�����������ѯ����·�ı�ţ�������������� 0 --------------------" << endl;
		string s;
		cout << ">>>";
		cin >> s;
		while (s != "0") {
			output_line(s);
			Sleep(1200);
			cout << "\n" << endl;
			cout << "\n------------------�����Լ�����ѯ������·��������������� 0 ---------------------\n" << endl;
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
		int q1[99] = { 0 };//��¼ÿһѡ��Ļ�����·������

		for (int i = 0; i < LINE_SUM ; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {

				int index = L[i].st[j].name.find(s);
				int len = L[i].st[j].name.length();
				//ֱ��ƥ��------------------------------------------------------------------------------------------------------//-
				if ((s == L[i].st[j].name || s + "վ" == L[i].st[j].name) && s != "�Ͼ�" && s != "�Ͼ���") {                                                                                                                //
					flag = 1;
					if (L[i].st[j].cond == 0) {
						cout << "\n" << endl;
						cout << "�����ҵ�  " << L[i].st[j].name << "վλ�ڣ�" << L[i].number << "����";
						for (int k = i + 1; k < LINE_SUM; k++) {
							for (int m = 0; m < L[k].stat_num; m++) {
								if (L[i].st[j].name == L[k].st[m].name) {
									cout << "��" << L[k].number << "����";
									L[k].st[m].cond = 1;
								}
							}
						}
						cout << "\n" << endl;
					}
				}																																						//
//------------------------------------------------------------------------------------------------------------------
// �ؼ���ƥ��-----------------------------------------------------------------------------------------------------
				if (s != L[i].st[j].name && index%2==0) {
					flag = 1;
					if (L[i].st[j].cond == 0) {
						p[q].cnt = q;
						p[q].name = L[i].st[j].name;
						p[q].LIN[q1[q]] = L[i].number;
						if (q == 1)cout << "\n������Ҫ���� �� ";
						cout << q << "." << L[i].st[j].name << "վ   ";
						//�ڲ�����--------------------------------------------
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
			cout << "\n------------------��ѡ������Ҫ��ѯ��վ�������Ӧ��ţ����ڴ˶�β�ѯ���������������99--------------------" << endl;
			cout << ">>>";
			//int temp=0;
			string temp;
			//getline(cin, temp);
			cin >> temp;
			while (temp != "99") {
				if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//ע��q���++
					cout << "\n>>>>>>>>>>>����ѡ�Χ�ڣ����������룬�������������99\n" << endl;
				}
				else {
					for (int i = 1; i < q; i++) {
						if (atoi(temp.c_str()) == i) {
							cout << "\n����ѯ�� " << p[i].name << "վ  λ��";
							for (int j = 0; j <= q1[i]; j++) {
								cout << p[i].LIN[j] << "����";
								if (j != q1[i])cout << "��";
							}
							cout << endl;
							break;
						}
						else continue;
					}
					cout << "\n--------------------------------�����Լ�����ѯ����ѡ�������������� 99---------------------------------------\n" << endl;
				}
				cout << ">>>";
				cin >> temp;
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------
		if (flag == 0)cout << "\n>>>>>>>>>���޴�վ������������\n" << endl;
		for (int i = 0; i < LINE_SUM; i++) {
			for (int j = 0; j < L[i].stat_num; j++) {
				L[i].st[j].cond = 0;//���㣬������ʹ��
			}
		}
	}

	void search_station() {
		cout << "\n-------------------�����������ѯ��վ�㣬������������� 0 --------------------\n" << endl;
		cout << "\n****************     ����鿴·�ߣ�������r  \n" << endl;
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
			cout << "------------------�����Լ�����ѯ����վ�㣬������������� 0 ---------------------\n" << endl;
			cout << "\n****************     ����鿴·�ߣ�������r  \n" << endl;
			cout << ">>>";
			cin >> s;
		}
	}

	int ticket_price(unsigned int len) {//Ʊ�ۼ���
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

	void min_routine(int start, int end,int len) {//·�߹滮
		int temp=edge[start].next;
		int temp1 = edge[temp].next;
		const int tem = start;	
		if (start == end) {
			if (min > len) {
				min = len;
				if (min < 1.3*len) {
					count++;
					cout << "��" << count << "��·�ߣ� ";
					cout << user_head << "��>";
					
					for (int j = 0; j < rout.size(); j++) {
						if (j != rout.size() - 1)cout << rout[j] << "��>"; 
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
		loop1:	cout << "\n-------------------------------------------����������ʼ��վ�������˳������� 0-----------------------------------------\n" << endl;

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
						//ֱ��ƥ��------------------------------------------------------------------------------------------------------//
						if (s == L[i].st[j].name) {                                                                                                                //
							flag = 1;
							start = s;
							break;
						}																																						//
		//------------------------------------------------------------------------------------------------------------------
		// �ؼ���ƥ��-----------------------------------------------------------------------------------------------------
						if (s != L[i].st[j].name && index%2==0) {
							flag = 1;
							for (int k = 1; k <= q; k++) {
								if (p[k] == L[i].st[j].name) {
									flag = 2; break;
								}
							}
							if (L[i].st[j].cond == 0 && flag != 2) {
								if (q == 1)cout << "\n������Ҫѡ�� �� ";
								cout << q << "." << L[i].st[j].name << "վ   ";
								L[i].st[j].cond = 1;
								p[q] = L[i].st[j].name;
								q++;
							}
						}
					}
				}
				if (q > 1) {
					cout << endl;
					cout << "\n------------------------��ѡ������Ҫ��ʼ��վ�������Ӧ���---------------------------" << endl;
					cout << ">>>";
					string temp;
					cin >> temp;
					while (true) {
						if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//ע��q���++
							cout << "\n>>>>>>>>>>>>>����ѡ�Χ�ڣ�����������\n" << endl;
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
				if (flag == 0) { cout << "\n>>>>>>>>>���޴�վ������������\n" << endl; goto loop1;; }
				for (int i = 0; i < LINE_SUM; i++) {
					for (int j = 0; j < L[i].stat_num; j++) {
						L[i].st[j].cond = 0;//���㣬������ʹ��
					}
				}
			}
			//***********************************************************************************************************************
		loop2:		cout << "\n-------------------------------------------�����������յ�վ�������˳������� 0-----------------------------------------\n" << endl;
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
							//ֱ��ƥ��------------------------------------------------------------------------------------------------------//
							if (s == L[i].st[j].name) {                                                                                                                //
								flag = 1;
								end = s;
								break;
							}																																						//
			//------------------------------------------------------------------------------------------------------------------
			// �ؼ���ƥ��-----------------------------------------------------------------------------------------------------
							if (s != L[i].st[j].name && index%2==0) {
								flag = 1;
								for (int k = 1; k <= q; k++) {
									if (p[k] == L[i].st[j].name) {
										flag = 2; break;
									}
								}
								if (L[i].st[j].cond == 0 && flag != 2) {
									if (q == 1)cout << "\n������Ҫѡ�� �� ";
									cout << q << "." << L[i].st[j].name << "վ   ";
									L[i].st[j].cond = 1;
									p[q] = L[i].st[j].name;
									q++;
								}
							}
						}
					}
					if (q > 1) {
						cout << endl;
						cout << "\n--------------------------��ѡ������Ҫ���յ�վ�������Ӧ���--------------------------" << endl;
						cout << ">>>";
						string temp;
						cin >> temp;
						while (true) {
							if (atoi(temp.c_str()) >= q || atoi(temp.c_str()) <= 0) {//ע��q���++
								cout << "\n>>>>>>>>>>>>>����ѡ�Χ�ڣ�����������\n" << endl;
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
						cout << "\n>>>>>>>>>���޴�վ������������\n" << endl; goto loop2;
					}
					for (int i = 0; i < LINE_SUM; i++) {
						for (int j = 0; j < L[i].stat_num; j++) {
							L[i].st[j].cond = 0;//���㣬������ʹ��
						}
					}
				}
			//*********************************************************************************************************************************
			if (start == end) {
				cout << "\n>>>>>>>>>>>>>>>>  ������ֱ�ӽ�վ���վ�����߸��������������\n" << endl;
				cout << "\n>>>>>>>>>>>>>>>>  ʼ��վ���յ�վ�غϣ����ݹ涨��Ʊ��2Ԫ\n" << endl;
			}
			else { 
				cout << "\n>>>>>>>>>>>������ѡ���·�����£�#--  �������һ��·��Ϊ�������·��  --#\n" << endl;
				cout << "\n******************��ע�⣺���ж���·�ߣ�ǰ���·��ͨ���ϳ��������ѡ�񣡣�\n\n" << endl;
				user_head = start;
				min_routine(pot[start], pot[end], 0);
				cout <<"\n>>>>>>>>>>�����̣�"<<min << "�ף�Ʊ�ۣ�" << " " << ticket_price(min) << " Ԫ\n" << endl;
			}
			memset(visit, 0, sizeof(visit));
			min = 21474836;
			count = 0;
	
		loop:cout << "\n----------------------------------------�Ƿ����������������y����������n-------------------------------------------\n" << endl;
			cout << ">>>";
			cin >> s;
			if (s == "y")continue;
			else if (s == "n")return;
			else {
				cout << "\n>>>>>>>>>>>>>>>>>>�Ƿ����룡����ȷ����\n" << endl;
				goto loop;
			}
		}
	}

	

};
#endif