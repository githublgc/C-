﻿#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        int temp1 = a[i] / 10;//1号是十位数,变为新的个位数
        int temp2 = a[i] - 10 * temp1;//2号是个位数，变成新的十位数
        a[i] = temp2 * 10 + temp1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j - 1] > a[j])
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        int temp3 = a[i] / 10;//现在的十位其实是原来的个位
        int temp4 = a[i] - 10 * temp3;//个位变回原来十位 
        a[i] = temp4 * 10 + temp3;

    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
}