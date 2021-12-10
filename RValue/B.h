#pragma once
#include <iostream>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 10240
class B {
public:
    B() {
        m_ins = ++instance;
        cout << m_ins << "\tB() object created.\n";

    };
    ~B() {
        cout << m_ins << "\t~B()\n";
        if (c)
        {
            delete c;
            c = nullptr;
            cout << m_ins << "\t\tc is deleted.\n";
        }
        else
            cout << m_ins << "\t\tc is empty.\n";
    };
    B(const B& T) {
        m_ins = ++instance;
        cout << m_ins << "\tB(const B & T)\n";
        if (T.c)
        {
            c = new char[BUFFER_SIZE];
            cout << m_ins << "\t\tc is allocated.\n";
            copy(T.c, T.c + BUFFER_SIZE, c);
            cout << m_ins << "\t\tc is copied from " << T.m_ins << "\n";
        }
    };
    B& operator = (const B& T)
    {
        cout << m_ins << "\toperator=(const B & T)\n";
        if (c)
        {
            delete[] c;
            c = nullptr;
            cout << m_ins << "\t\tc is deleted.\n";
        }
        if (T.c)
        {
            c = new char[BUFFER_SIZE];
            cout << m_ins << "\t\tc is allocated.\n";
            copy(T.c, T.c + BUFFER_SIZE, c);
            cout << m_ins << "\t\tc is copied from " << T.m_ins << "\n";
        }
        return *this;
    }
public:
    void alloc() {
        if (c)
            return;
        cout << m_ins << "\talloc()\n";
        c = new char[BUFFER_SIZE];
        cout << m_ins << "\t\tc is allocated.\n";
    }
private:
    char* c = nullptr;
    int m_ins = -1;
    static int instance;
};

int B::instance = -1;


B fun2()
{
    cout << "B fun()\n";
    B a;
    a.alloc();
    cout << "B fun() returnning\n";
    return a;
}

void testB()
{
    cout << "testB=========================================.\n";
    cout << "Call fun.\n";
    B a = fun2();
    cout << "define 4 instances.\n";
    B b, c, d, e;
    cout << "Assign.\n";
    b = a;
    cout << "Assign move.\n";
    c = move(a);
    cout << "Assign fun.\n";
    e = d = fun2();
    cout << "Exiting.\n";
}
