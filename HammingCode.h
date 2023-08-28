#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>
#define MAX 100
using namespace std;

//�ж��Ƿ���2���ݴη�
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
//������Ӧ��ʮ�����Ʒ���
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
//��ʮ���ƴ�ת�ɶ�����
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

//�����ƴ�תʮ������
string bin2hex(string bin)
{
    string hex = "";//ʮ�����ƴ�

    //ǰ�油0
    int cnt = 0;//��0�ĸ���
    if (bin.size() % 4 != 0)
    {
        cnt = 4 - (bin.size() % 4);
    }

    for (int i = 0; i < cnt; i++)
        bin.insert(0, "0");

    //������תʮ������
    for (int i = 0; i < bin.size(); i += 4)
    {
        int sum = 0;

        for (int j = 0; j < 4; j++)
        {
            sum += (bin[i + j] - '0') * pow(2, 3 - j);//ע�����ʱ��������������3-j
            //cout<<i+j<<"\t"<<(bin[i+j]-'0')*pow(2,3-j)<<endl;
        }
        hex.push_back(hexNumber(sum));
    }
    return hex;
}

//���������
string Hamming(string data)
{
    string code;//������
    vector<vector<int>>check(MAX);//��¼�й���Ϣλ

    /*ȷ��������λ��*/
    int r = 0;//У��λ����
    int m = data.size();//����λ�ĸ���
    while (m + r + 1 > pow(2, r))
    {
        r++;
    }
    int n = m + r;//������λ��

    //�趨��ʼ�����룬У��λ��Ϊ0
    code = data;
    for (int i = 0; i < n; i++)
    {
        if (is2n(dec2Bin(i + 1)))
        {
            code.insert(i, "0");
        }
    }
    //cout<<"code"<<code<<endl;

    /*�ҳ��й���Ϣλ*/
    //����У��λ
    for (int i = 0; i < r; i++)
    {
        int checkNumber = pow(2, i);//У��λ���

        //������У��λ
        for (int j = checkNumber + 1; j <= n; j++)
        {
            string binData = dec2Bin(j);//jת�ɶ�����

            if (!is2n(binData))
            {
                //����У��λi,����������λ������iλ��1�������check[i]
                reverse(binData.begin(), binData.end());
                if (binData[i] == '1')
                {
                    check[i].push_back(j);
                }
            }
        }
    }

    /*������õ����й���Ϣλ��żУ��*/
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
//�������
string Correct(string code)
{
    vector<vector<int>>check(MAX);//��¼�й���Ϣλ

    int r = 0;//У��λ����
    int n = code.size();//������λ��
    while (n + 1 > pow(2, r))
    {
        r++;
    }

    /*�ҳ��й���Ϣλ*/
    //����У��λ
    for (int i = 0; i < r; i++)
    {
        int checkNumber = pow(2, i);//У��λ���

        //������У��λ
        for (int j = checkNumber + 1; j <= n; j++)
        {
            string binData = dec2Bin(j);//jת�ɶ�����

            if (!is2n(binData))
            {
                //����У��λi,����������λ������iλ��1�������check[i]
                reverse(binData.begin(), binData.end());
                if (binData[i] == '1')
                {
                    check[i].push_back(j);
                }
            }
        }
    }

    /*ri XOR �й���Ϣλ=0 -> c+=0
      ri XOR �й���Ϣλ=1 -> c+=i
    */
    int c = 0;
    for (int i = 0; i < r; i++)
    {
        int count = 0;//����1�ĸ���
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

