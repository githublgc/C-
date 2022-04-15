﻿#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    int* b = new int[n];//个位数 
    int* c = new int[n];//十位数
    int* d = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)//借助辅助空间
    {

        c[i] = a[i] / 10;//10 位,取10位要除以，不是%模！！
        b[i] = a[i] - c[i] * 10;//个位
    }
    //规定 相当于是个位十位反转，那么也可以考虑反转后排序，在对应反转回来
    // 后面开始B当十位，C当个位。
    for (int i = 0; i < n; i++)
    {
        d[i] = b[i] * 10 + c[i];//反转矩阵
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (d[j - 1] > d[j])
            {
                int temp1 = d[j];
                d[j] = d[j - 1];
                d[j - 1] = temp1;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        int p = d[i] / 10;
        a[i] = p + (d[i] - p * 10) * 10;
    }
    // 下面这种是不可行的情况
    //for (int i = 0; i < n; i++)
    //{
    //    for (int j = n - 1; j > i; j--)
    //    {
    //        if (b[j - 1] > b[j])//先比个位
    //        {
    //            int temp1 = a[n-i];
    //            a[n-i] = a[n-i +1];
    //            a[n-i+1] = temp1;
    //        }

    //        //if (b[j - 1] == b[j])//个位一样再比十位
    //        //{
    //        //    if (c[j - 1] > c[j])
    //        //    {
    //        //        int temp2 = a[j];
    //        //        a[j] = a[j - 1];
    //        //        a[j - 1] = temp2;
    //        //    }
    //        //}
    //    }
    //}
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
}