#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;
/*
Windows头文件中包含可以加载DLL的函数。
*/
typedef double(*ptrSub)(vector<double>, vector<double>, int);
/*
在调用DLL函数之前，要定义函数指针，用来调用函数。
可以看出，函数指针的类型与DLL中的要一致。
*/

HMODULE hMod = LoadLibrary(L"Dll_EMG_MODEL.dll");
/*
    调用LoadLibrary函数加载DLL文件。加载成功，hMod指针不为空。
    这里也可以是一个地址加文件名
*/
int main()
{
    if (hMod != NULL)
    {
        cout << "ddd" << endl;
        /*
        
        如果加载成功，则可通过GetProcAddress函数获取DLL中需要调用的函数的地址。
        获取成功，sum指针不为空。
        */
        ptrSub sum = (ptrSub)GetProcAddress(hMod, "sim_model_DLL");
        if (sum != NULL)
        {
            vector<double> xin10 = { 0.0174603,0.422222,1.1,1.69365,2.35873,3.0746,3.38889,3.87619,4.40159,4 };
            vector<double> cin7 = { 15, 21, 0.403, 2, 0.04, 0.04, 1.2 };
            int choice = 1;
            cout << sum(xin10, cin7, choice) << endl;
            /*获取地址成功后，通过sum调用函数功能。*/
        }
        FreeLibrary(hMod);
        /*在完成调用功能后，不在需要DLL支持，则可以通过FreeLibrary函数释放DLL。*/
    }
}