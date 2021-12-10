#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <string>

void test()
{
    std::string str = "Hello";
    std::vector<std::string> v;
    //���ó���Ŀ������캯�����½��ַ����飬��������
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\""<< std::endl;
    //�����ƶ����캯�����Ϳ�str���Ϳպ���ò�Ҫʹ��str
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"" << std::endl;
    std::cout << "The contents of the vector are \"" << v[0] << "\", \"" << v[1] << "\"\n" << std::endl;





    std::string A("abc");
    std::string&& Rval = std::move(A);
    std::string B(Rval);    // this is a copy , not move.
    std::cout << A << std::endl;   // output "abc"
    std::string C(std::forward<std::string>(Rval));  // move.
    std::cout << A << "\n" << std::endl;       /* output "" */




    std::cout << "-------������ֵ--------" << std::endl;
    int a = 5;
    int& add_a(a);

    std::cout << "   a  =" << a << "    " << "    &a = " << &a << std::endl;
    std::cout << "add_a =" << add_a << "    " << "&add_a = " << &add_a << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::cout << "-------������ֵ--------" << std::endl;
    int b = 10;
    int&& add_b(b + 1);
    std::cout << "   b  =" << b << "    " << "    &b = " << &b << std::endl;
    std::cout << "add_b =" << add_b << "    " << "&add_b = " << &add_b << std::endl;
    add_b++;
    std::cout << "add_b++ =" << add_b << "    " << "&add_b++ = " << &add_b << std::endl;
    std::cout << "-----------------------" << std::endl;
   
}