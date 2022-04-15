#ifndef DRAWTREE_HH
#define DRAWTREE_HH

#include <ostream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace
{
#define lChild _lchild  //ʹ��ǰ�� l_child_ ����Ϊ �Լ����ڵ�����ӵ�����
#define rChild _rchild //ʹ��ǰ�� r_child_ ����Ϊ �Լ����ڵ���Һ��ӵ�����
#define data   _key     //ʹ��ǰ�� data_ ����Ϊ �Լ����ڵ�����ݵı�����
#define MAXN (1000)      //������Ľڵ�����
#define PERID (2)        //��ӡ�����ڵ�ĺ�������
    unsigned int SUM;  //ͳ�Ƶ�ǰ�������ڼ����ڵ�

#ifdef _WIN32
    void clear() { system("cls"); }
#elif __linux__
    void clear() { system("clear"); }
#endif

    // ������ƶ��� (X,Y)
    std::string AXIS(int X, int Y) {
        std::stringstream ss;
        ss << "\033[" << Y << ";" << X << "H";
        return ss.str();
    }

    struct DrawNode {
        int x, y, dataSize;
    }axisArray[MAXN];

    


    //����ڵ���������ĳ���
    template <typename TreePtr>
    int dataSize(TreePtr const& root) {
        std::stringstream ss;
        ss << (root->data);
        return (ss.str()).length();
    }

    //�������, �������һ��ڵ�(������)
    //������ͨ��ȫ�ֱ���SUM����һ���ڵ����ݵ�����������
    //������ͨ���ݹ�����ж�
    //PERID �������ڵ�������
    template <typename TreePtr>
    void buildDrawTree(TreePtr const& root, int deep) {
        if (!root) return;  //�жϿսڵ�,�����Ľڵ��пպ��Ҳ�һ��,����ҲҪ��, ������֮ǰ���жϿսڵ���(root->height_== -1).

        if (root->lChild)  buildDrawTree(root->lChild, deep + 1);

        axisArray[SUM] = (struct DrawNode){ axisArray[SUM - 1].x + axisArray[SUM - 1].dataSize + PERID, deep, dataSize(root) };
        std::cout << AXIS(axisArray[SUM].x, axisArray[SUM].y) << root->data;
        ++SUM;

        if (root->rChild)  buildDrawTree(root->rChild, deep + 1);

    }

    template <typename TreePtr>
    void Draw(TreePtr const& t) {  //��������
        clear();  //����
        SUM = 1;
        int maxy = 0;

        buildDrawTree<TreePtr>(t, 2);   //ÿ����㻭����

        //���ڵ������,��Ϊ���Ľڵ㲻��̫��,���Ծ�д��n^2���㷨,�ȽϺ�ʵ��
        //ÿ���ڵ�ֻ��һ�����ڵ�,���Ի���ÿ���ڵ���Լ����ڵ�����߼���
        for (int i = 1; i < SUM; i++) {
            //x,y���ӽڵ������,p�Ǹ��ڵ��axisArray������±�, px,py�Ǹ��ڵ������;
            int x = axisArray[i].x, y = axisArray[i].y, p = 0, px = 0, py = y - 1;

            if (y == 1) continue; // �����û�и��ڵ�,����

            for (int j = 1; j < SUM; j++) {  //ѭ���Ҹ��ڵ�
                if (i == j) continue;
                if ((!p || abs(axisArray[j].x - x) < abs(px - x)) && axisArray[j].y + 1 == y)
                    p = j, px = axisArray[j].x;
            }

            int s = (2 * x + axisArray[i].dataSize) >> 1;
            std::cout << AXIS(s, py) << '+';
            if (s < px)
                for (int i = s + 1; i < px; i++) std::cout << AXIS(i, py) << '-';
            else
                for (int i = px + axisArray[p].dataSize; i < s; i++) std::cout << AXIS(i, py) << '-';
            maxy = std::max(maxy, y);
        }
        std::cout << AXIS(1, maxy + 1);  //��ӡ��ѹ���Ƶ����±�.
        // getchar();
    }
} // namespace
#endif

