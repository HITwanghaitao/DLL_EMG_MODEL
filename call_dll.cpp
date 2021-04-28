#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;
/*
Windowsͷ�ļ��а������Լ���DLL�ĺ�����
*/
typedef double(*ptrSub)(vector<double>, vector<double>, int);
/*
�ڵ���DLL����֮ǰ��Ҫ���庯��ָ�룬�������ú�����
���Կ���������ָ���������DLL�е�Ҫһ�¡�
*/

HMODULE hMod = LoadLibrary(L"Dll_EMG_MODEL.dll");
/*
    ����LoadLibrary��������DLL�ļ������سɹ���hModָ�벻Ϊ�ա�
    ����Ҳ������һ����ַ���ļ���
*/
int main()
{
    if (hMod != NULL)
    {
        cout << "ddd" << endl;
        /*
        
        ������سɹ������ͨ��GetProcAddress������ȡDLL����Ҫ���õĺ����ĵ�ַ��
        ��ȡ�ɹ���sumָ�벻Ϊ�ա�
        */
        ptrSub sum = (ptrSub)GetProcAddress(hMod, "sim_model_DLL");
        if (sum != NULL)
        {
            vector<double> xin10 = { 0.0174603,0.422222,1.1,1.69365,2.35873,3.0746,3.38889,3.87619,4.40159,4 };
            vector<double> cin7 = { 15, 21, 0.403, 2, 0.04, 0.04, 1.2 };
            int choice = 1;
            cout << sum(xin10, cin7, choice) << endl;
            /*��ȡ��ַ�ɹ���ͨ��sum���ú������ܡ�*/
        }
        FreeLibrary(hMod);
        /*����ɵ��ù��ܺ󣬲�����ҪDLL֧�֣������ͨ��FreeLibrary�����ͷ�DLL��*/
    }
}