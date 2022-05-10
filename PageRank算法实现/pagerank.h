#include<iostream>
#include<fstream>
#include<list>//����
#include<algorithm>
using namespace std;

int count1 = 0;//��¼�ڵ�����

int count2 = 0;//��¼��Ч�ڵ������г��Ȼ���ȣ�
bool* valid;//�������ȵĽڵ�
bool* valid1;//�ж��г��ȵĽڵ�
bool* blackhole;//��ǽ�������޳��ȵĺڶ��ڵ�
int* counttoNode;//���ڵ�ָ��ڵ�ĸ���

int count3 = 0;//��¼�ֿ���Ŀ
int blocksize = 2000;//ÿ��Ĵ�С

//��ΪPageRank��ѭԭ���ӹ�ϵ�Ĳ�����1 - �¸��ʽ���N�����������ɢ��
//double beta = 0.85;//һ��0.8-0.9������ֵ0.85
double beta = 0.85;
//double sigma = 0.0000000000001;//�ж��Ƿ���������ֵ
double sigma = 0.000001;



double* Wtn;//��t=nʱ��ʱ�Ľڵ�Ȩ��
double* Wtn1;//����������t=n+1ʱ�ĸ���Ȩ��

int m=30;//��Ϊ���ݼ��е�һ��tonode��ID

void countallnode()
{
	//ͨ���������NodeID����ȡ����
	ifstream in("data.txt");
	int fromNode, toNode;
	while (!in.eof())
	{
		in >> fromNode >> toNode;
		if (fromNode > count1)
		{
			count1 = fromNode;
		}
		if (toNode > count1)
		{
			count1 = toNode;
		}
	}
	cout << "�ڵ�����Ϊ��" << count1 << endl;
	cout << endl;
	
}

//��ԭ�ļ��ֿ鱣��
void blockSaving()
{
	count3 = count1 / blocksize + 1;
	cout << "ÿ���СΪ"<< blocksize <<"���ݹ��ɷ�Ϊ" << count3 << "��" << endl;
	cout << "��ʼ�ֿ�" << endl;
	ofstream* out = new ofstream[count3];
	char buf[100];
	for (int i = 0; i < count3; i++)
	{
		sprintf_s(buf, "block%d.txt", i);
		out[i].open(buf);
	}
	ifstream in("data.txt");
	int fromNode, toNode;
	int current = -1;//ͷ�ڵ㣬���ڵ�һ���ڵ�֮ǰ
	int count6 = 0;//��¼��ǰ��¼�˶��������ж��Ƿ�Ҫ������һ�����¼����
	list<int> LinkList;
	while (!in.eof())
	{
		in >> fromNode >> toNode;
		if (current != fromNode)
			//��ȡ��ǰ�ڵ���ɣ��Ƚ�ԭ�ڵ�д����� 
		{
			int t;
			while (!LinkList.empty())
			{
				t = LinkList.front();
				out[current / blocksize] << current << " " << counttoNode[current - 1] << " " << t << endl;
				LinkList.pop_front();
			}
			current = fromNode;
			count6 = 0;
		}
		 
		count6++;
		LinkList.push_back(toNode);//����д������β��
	}
	cout << "��ɷֿ�" << endl;
	cout << endl;
	
}

bool Isend()
{
	double New = 0.0, Old = 0.0;
	bool flag = false;//��־λ������Ƿ���Խ�������
	for (int i = 0; i < count1; i++)
	{
		Old =Old+Wtn1 [i];
	}
	for (int i = 0; i < count1; i++)
	{
		if (valid[i]==false&&valid1[i]==false)
		{
			Wtn1[i] = 0;//��Ч�ڵ���º��Ȩ�ػ���Ϊ0
			continue;
		}
		else
		{
			Wtn1[i] += (1 - Old) / count2;
			if (Wtn[i] - Wtn1[i] > sigma || Wtn1[i] - Wtn[i] > sigma)//����ǰ�����ֵsigma�Ա�
			{
				flag = true;//��ֵ�ϴ����ñ�־λ���ٴ�ѭ��
			}
			Wtn[i] = Wtn1[i];//����һ�ֵ������ݸ���
			Wtn1[i] = 0;
			New =New+ Wtn1[i];
		}
	}
	
	return flag;
}

//��������б�sortʵ��������ȡǰ100�����
struct ScoreList
{
	int NodeId;
	double Score;
};
bool Compare(ScoreList r1, ScoreList r2)//��ӱȽϺ���ʵ��sort����
{
	return r1.Score > r2.Score;
}

ScoreList* L;//�������������б�
void topRankCount()
{
	L = new ScoreList[count1];
	for (int i = 0; i < count1; i++)
	{
		L[i].NodeId = i;
		L[i].Score = Wtn[i];
	}
	sort(L, L + count1, Compare);//����
	//sort(p, p + count1);��������
	cout << "�ڵ��������" << endl;
	cout << endl;

}

