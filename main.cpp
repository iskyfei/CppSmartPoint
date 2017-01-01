//
//  main.cpp
//  test
//
//  Created by sky on 2016/12/31.
//  Copyright © 2016年 sky. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "smartPtr1.h"
//#include "smartPtr2.h"

using namespace std;

class CTest
{
public:
    CTest(int n)
    :m_n(n)
    {
        cout << "CTest(" << m_n << ") \n";
    }
    ~CTest()
    {
        cout << "~CTest(" << m_n << ") \n";
    }
    
    void Print()
    {
        cout << m_n << "\n";
    }
    int m_n;
};

int main(int argc, const char * argv[]) {
    
    {
        CRefPtr<CTest> p1(new CTest(1));
        CRefPtr<CTest> p2(new CTest(2));
        p1->Print();
        p1 = p2;
        CRefPtr<CTest> p3= CRefPtr<CTest>(new CTest(3));
        p3->Print();
        p3 = p2;
        p3->Print();
        cout << "p3 count:"<<p3.get_ref_count()<< "\n";
    }
    system("pause");
    

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
