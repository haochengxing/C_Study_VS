#pragma once
#include <iostream>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 10240
class A {
public:
    A() {
        m_ins = ++instance;
        cout << m_ins << "\tA() object created.\n";

    };
    ~A() {
        cout << m_ins << "\t~A()\n";
        if (c)
        {
            delete c;
            c = nullptr;
            cout << m_ins << "\t\tc is deleted.\n";
        }
        else
            cout << m_ins << "\t\tc is empty.\n";
    };
    A(const A& T) {
        m_ins = ++instance;
        cout << m_ins << "\tA(const A & T)\n";
        if (T.c)
        {
            c = new char[BUFFER_SIZE];
            cout << m_ins << "\t\tc is allocated.\n";
            copy(T.c, T.c + BUFFER_SIZE, c);
            cout << m_ins << "\t\tc is copied from " << T.m_ins << "\n";
        }
    };
    //右值引用
    A(A&& T) {
        m_ins = ++instance;
        cout << m_ins << "\tA(A && T)\n";
        c = T.c;
        T.c = nullptr;
        cout << m_ins << "\t\tc is moved from " << T.m_ins << "\n";
    };
    A& operator = (const A& T)
    {
        cout << m_ins << "\toperator=(const A & T)\n";
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
    //右值引用
    A& operator = (A&& T)
    {
        cout << m_ins << "\toperator=(A && T)\n";
        if (c)
        {
            delete[] c;
            c = nullptr;
            cout << m_ins << "\t\tc is deleted.\n";
        }
        c = T.c;
        T.c = nullptr;
        cout << m_ins << "\t\tc is moved from " << T.m_ins << "\n";
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

int A::instance = -1;

A fun()
{
    cout << "A fun()\n";
    A a;
    a.alloc();
    cout << "A fun() returnning\n";
    return a;
}

void testA()
{
    cout << "testA=========================================.\n";
    cout << "Call fun.\n";
    A a = fun();
    cout << "define 4 instances.\n";
    A b, c, d, e;
    cout << "Assign.\n";
    b = a;
    cout << "Assign move.\n";
    c = move(a);
    cout << "Assign fun.\n";
    e = d = fun();
    cout << "Exiting.\n";
}
