#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <lm.h>
#include <sddl.h>     
#include <locale.h>
#include <string.h>

int wmain(int argc, wchar_t* argv[])
{
    wchar_t server_name = NULL;
    wchar_t user_name[20]; 
    user_name[19] = 0;
    USER_INFO_1* ui;
    NET_API_STATUS ret_status; 
    printf("Input user name: ");
    int dummy;
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), user_name, strlen(user_name), &dummy, 0); 
    user_name[dummy - 2] = 0;   
    ret_status = NetUserGetInfo(
        server_name, 
        user_name, 
        1, 
        (LPBYTE*)&ui); 
    if (ret_status != NERR_Success)
    {
        printf("Net user get info failed.\n");
        return ret_status;
    }
    wprintf(L"\nUser name:  ");
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ui->usri1_name, wcslen(ui->usri1_name), &dummy, 0);
    printf("\nUser comment: ");
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ui->usri1_comment, wcslen(ui->usri1_comment), &dummy, 0);
    
    if (ui->usri1_password != NULL) {
        printf("\n");
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ui->usri1_password, wcslen(ui->usri1_password), &dummy, 0);
    }
    ui->usri1_password_age /= 86400;
    wprintf(L"\nPassword age (days): %d\n", ui->usri1_password_age);
    wprintf(L"Privilege level: %d\n", ui->usri1_priv);
    NetApiBufferFree(ui);
    return 0;
}