// SharingByName.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
void Read(void* p);
void Write(void* p);
int Error(const char* msg)
{
    printf("%s (%u) \n",msg, ::GetLastError());
    return 1;

}
int main()
{
    HANDLE hMemMap = ::CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 1 << 16, L"MySharedMemory");
    if (!hMemMap)
    {
        return Error("Failed to create shared memory!");
    }

    void* p = ::MapViewOfFile(hMemMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (!p)
        return Error("Failed in MapViewOfFile");
    printf("Address: 0x%p", p);

    BOOL quit = FALSE;

    while (!quit)
    {
        printf(" 1 = read 2 = write 0 = quit: ");
        int selection = _getch();
        printf("%c\n", selection);
        switch (selection) {
        case '1':
            Read(p);
            break;
        case '2':
            Write(p);
            break;
        case '0':
            quit = TRUE;
            break;
        }

 
        
    }
    ::UnmapViewOfFile(p);
    ::CloseHandle(hMemMap);
    return 0;
}

void Read(void* p)
{
    printf("%s \n", (const char*)p);
}
void Write(void* p)
{
    printf(" >> ");
    char text[256];
    //getchar();
    fgets(text,ARRAYSIZE(text),stdin);
    strcpy_s((char*)p, _countof(text), text);


}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
