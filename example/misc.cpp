// Copyright (c) 2014 Yasser Asmi
// Released under the MIT License (http://opensource.org/licenses/MIT)

#include "jvar.h"
#include <vector>

#ifdef _MSC_VER
#include <Windows.h>
#define getTickCount  GetTickCount
#endif

using namespace std;
using namespace jvar;

/**
 * \example misc.cpp
 * This example shows misc functionality in jvar that jvar is built
 * on top of but can also be used directly.
 */

void showFormat()
{
    int a = 45;
    string s;
    string s2;

    s2 = formatr("%08d", a);
    printf("%s\n", s2.c_str());

    format(s, "[%s] was built before...another string is being built now with hex 0x%x", s2.c_str(), a);

    printf("%s\n", s.c_str());
}


void showArray()
{
    ulongint start;
    const int cnt = 100000000;

    // BArray
    start = getTickCount();
    BArray arr(sizeof(long int), NULL);
    for (int i = 0; i < cnt; i++)
    {
        *(long int*)arr.append(NULL) = i;
    }
    printf("BArray time=%lu\n", getTickCount() - start);

    // ObjArray
    start = getTickCount();
    ObjArray<long int> arrt;
    for (int i = 0; i < cnt; i++)
    {
        *arrt.append() = i;
    }
    printf("ObjArray time=%lu\n", getTickCount() - start);

    // Stl
    start = getTickCount();

    std::vector<long int> v;
    for (int i = 0; i < cnt; i++)
    {
        v.push_back(i);
    }
    printf("STL time=%lu\n", getTickCount() - start);

    // Printed:
    // BArray time=801
    // ObjArray time=783
    // STL time=2283
}


void bugreport()
{
    // Test that shows an issue when using GCC5's libstd ABI
    jvar::Variant inputData;
    std::string message = "[\"{\\\"msg\\\":\\\"connect\\\",\\\"session\\\":\\\"pjwLzc25gD\\\",\\\"version\\\":\\\"1\\\",\\\"support\\\":[\\\"1\\\",\\\"pre2\\\",\\\"pre1\\\"]}\"]";

    if (inputData.parseJson(message.c_str()))
    {
        for (int i=0; i<inputData.length(); i++)
	{
             jvar::Variant packet;
             packet.parseJson(inputData[i].toString().c_str());
             printf("input = %s\n", inputData.toString().c_str());
             printf("msg = %s\n", packet["msg"].toString().c_str());
	}
    }

    printf("success\n");
}

int main(int argc, char** argv)
{
    showFormat();
    showArray();
//    bugreport();
}
