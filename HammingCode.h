#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>
#define MAX 100
using namespace std;

//判断是否是2的幂次方
int is2n(string bin)
{
    int count = 0;
    for (int i = 0; i < bin.size(); i++)
    {
        if (bin[i] == '1')
            count++;
    }
    return count == 1 ? 1 : 0;
}
//求数对应的十六进制符号
char hexNumber(int num)
{
    char hex;
    if (num >= 0 && num <= 9)
        return num + '0';
    else
    {
        switch (num)
        {
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            cout << "error" << endl;
            return '#';
        }
    }
}
//将十进制串转成二进制
string dec2Bin(int dec)
{
    string bin = "";
    while (dec)
    {
        int remainer = dec % 2;
        bin.insert(0, to_string(remainer));
        dec = dec / 2;
    }
    return bin;
}

//二进制串转十六进制
string bin2hex(string bin)
{
    string hex = "";//十六进制串

    //前面补0
    int cnt = 0;//补0的个数
    if (bin.size() % 4 != 0)
    {
        cnt = 4 - (bin.size() % 4);
    }

    for (int i = 0; i < cnt; i++)
        bin.insert(0, "0");

    //二进制转十六进制
    for (int i = 0; i < bin.size(); i += 4)
    {
        int sum = 0;

        for (int j = 0; j < 4; j++)
        {
            sum += (bin[i + j] - '0') * pow(2, 3 - j);//注意求的时候从右往左，因此用3-j
            //cout<<i+j<<"\t"<<(bin[i+j]-'0')*pow(2,3-j)<<endl;
        }
        hex.push_back(hexNumber(sum));
    }
    return hex;
}

//海明码编码
string Hamming(string data)
{
    string code;//海明码
    vector<vector<int>>check(MAX);//记录有关信息位

    /*确定海明码位数*/
    int r = 0;//校验位个数
    int m = data.size();//数据位的个数
    while (m + r + 1 > pow(2, r))
    {
        r++;
    }
    int n = m + r;//海明码位数

    //设定初始海明码，校验位设为0
    code = data;
    for (int i = 0; i < n; i++)
    {
        if (is2n(dec2Bin(i + 1)))
        {
            code.insert(i, "0");
        }
    }
    //cout<<"code"<<code<<endl;

    /*找出有关信息位*/
    //遍历校验位
    for (int i = 0; i < r; i++)
    {
        int checkNumber = pow(2, i);//校验位序号

        //遍历非校验位
        for (int j = checkNumber + 1; j <= n; j++)
        {
            string binData = dec2Bin(j);//j转成二进制

            if (!is2n(binData))
            {
                //对于校验位i,二进制数据位倒数第i位是1，则加入check[i]
                reverse(binData.begin(), binData.end());
                if (binData[i] == '1')
                {
                    check[i].push_back(j);
                }
            }
        }
    }

    /*对上面得到的有关信息位做偶校验*/
    for (int i = 0; i < r; i++)
    {
        int count = 0;
        for (int j = 0; j < check[i].size(); j++)
        {
            int num = check[i][j];
            if (code[num - 1] == '1')
                count++;
        }
        if (count % 2 == 0)
            code[pow(2, i) - 1] = '0';
        else
            code[pow(2, i) - 1] = '1';
    }
    return code;
}
//检错并纠正
string Correct(string code)
{
    vector<vector<int>>check(MAX);//记录有关信息位

    int r = 0;//校验位个数
    int n = code.size();//海明码位数
    while (n + 1 > pow(2, r))
    {
        r++;
    }

    /*找出有关信息位*/
    //遍历校验位
    for (int i = 0; i < r; i++)
    {
        int checkNumber = pow(2, i);//校验位序号

        //遍历非校验位
        for (int j = checkNumber + 1; j <= n; j++)
        {
            string binData = dec2Bin(j);//j转成二进制

            if (!is2n(binData))
            {
                //对于校验位i,二进制数据位倒数第i位是1，则加入check[i]
                reverse(binData.begin(), binData.end());
                if (binData[i] == '1')
                {
                    check[i].push_back(j);
                }
            }
        }
    }

    /*ri XOR 有关信息位=0 -> c+=0
      ri XOR 有关信息位=1 -> c+=i
    */
    int c = 0;
    for (int i = 0; i < r; i++)
    {
        int count = 0;//计算1的个数
        int checkNum = pow(2, i);

        if (code[checkNum - 1] == '1')
            count++;

        for (int j = 0; j < check[i].size(); j++)
        {
            int num = check[i][j];
            if (code[num - 1] == '1')
                count++;
        }

        if (count % 2 != 0)
            c += checkNum;
    }
    if (c == 0)
    {
        cout << endl << "Correct." << endl;
        return "";
    }
    else
    {
        cout << endl << "Error in " << "bit " << c << "." << endl;
        code[c - 1] == 1 ? code[c - 1] = '0' : code[c - 1] = '1';
    }
    return code;
}

void HammingMain()
{
    string data;
    cout << "Please choose ( 1:Encoding 2:Error-Correcting 3:Quit )" << endl;
    int choice;
    while (cin >> choice)
    {
        string res;
        switch (choice)
        {
        case 1:
            cout << "Please input the codeword you are sending" << endl;
            cin >> data;
            res = Hamming(data);
            cout << "Hamming code in hexadecimal : " << bin2hex(res) << endl;
            break;
        case 2:
            cout << "Please input the Hamming code you received" << endl;
            cin >> data;
            res = Correct(data);
            if (res != "")
                cout << "The right Hamming code is " << res << "." << endl;
            break;
        case 3:
            return;
        default:
            cout << "Wrong number" << endl;
        }
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Please choose ( 1:Encoding 2:Error-Correcting 3:Quit )" << endl;
    }
}

