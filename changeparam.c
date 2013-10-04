#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")
#define BUF_LEN MAX_PATH * 11
#include <stdio.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
//int main(int argc, char *argv[]) {
    int i;
    TCHAR szPath[MAX_PATH];
    TCHAR szDir[MAX_PATH];
    TCHAR szFile[MAX_PATH+3];
    TCHAR szExt[3];
    TCHAR szCommand[BUF_LEN];
    TCHAR szError[1];
    TCHAR szDebug[1];
    TCHAR szArgs[BUF_LEN];

    TCHAR **pArgs = NULL;
    int nArgs = 0;

    TCHAR ag[BUF_LEN];
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(szPath, sizeof(szPath));
    ZeroMemory(szDir, sizeof(szDir));
/*
    ZeroMemory(szFile, sizeof(szFile));
    ZeroMemory(szExt, sizeof(szExt));
*/
    ZeroMemory(szCommand, sizeof(szCommand));
    ZeroMemory(szError, sizeof(szError));
    ZeroMemory(szDebug, sizeof(szDebug));
    ZeroMemory(szArgs, sizeof(szArgs));
    ZeroMemory(ag, sizeof(ag));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    GetModuleFileName(NULL, szPath, sizeof(szPath));
//    _wsplitpath(szPath, NULL, szDir, szFile, szExt);
    _wsplitpath(szPath, NULL, szDir, NULL, NULL);

/*
    wcscat(szFile, szExt);
    TerminateExeName(szFile);
*/

    wcscat(szDir, TEXT("changeparam.ini"));
    GetPrivateProfileString(TEXT("Settings"), TEXT("Command"), NULL, szCommand, sizeof(szCommand), szDir);
    GetPrivateProfileString(TEXT("Settings"), TEXT("Error"), NULL, szError, sizeof(szError), szDir);
    GetPrivateProfileString(TEXT("Settings"), TEXT("Debug"), NULL, szDebug, sizeof(szDebug), szDir);
    pArgs = CommandLineToArgvW(GetCommandLine(), &nArgs);

    for(i = 1; i  < 10; i++) {
        swprintf(ag, 3, TEXT("%%%d"), i);
        if(i >= nArgs){
            _InsStr(&szCommand, &ag, TEXT(""));
        }
        else {
            _InsStr(&szCommand, &ag, pArgs[i]);
        }
    }
    _InsStr(&szCommand, TEXT("\"\""), TEXT(""));
    c_trim(&szCommand);

    if(wcscmp(szDebug, TEXT("1")) == 0){
        MessageBoxW(NULL, szCommand, TEXT("実行パラメーター"), MB_OK);
    }
    if(!CreateProcess(
        NULL,
        szCommand,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)) {
        if(wcscmp(szError, TEXT("1")) == 0){
            MessageBoxW(NULL, TEXT("コマンド起動に失敗した"), TEXT("起動エラー"), MB_OK);   }
        return 0;
    }
    CloseHandle(pi.hThread);
//    WaitForSingleObject(pi.hProcess,INFINITE);
    CloseHandle(pi.hProcess);
    ExitThread(0);
    return 0;
//    exit(0);
}

int _InsStr(
    TCHAR *buff,
    TCHAR *target,
    TCHAR *repstr
    ) {
    TCHAR wbuf[BUF_LEN+1];
    TCHAR *ins;
    int t_len;

    if(buff == NULL || target == NULL || repstr == NULL){ return(0); }
    wcscpy(wbuf,buff);
    if(wcsstr(buff,target) == NULL) {
        return(0);
    }
    else {
        t_len = wcslen(target);
        ins = buff;
        while ((ins = wcsstr(ins,target)) != NULL) {
            wcscpy(wbuf,ins+t_len);
            wcscpy(ins,repstr);
            wcscat(buff,wbuf);
            ins += wcslen(repstr);
        }
    }
    return 1;
}

int c_trim(TCHAR *cpStr) {
    int i;
    TCHAR *cpStart;

    for (i = wcslen(cpStr)-1; i >= 0; i--) {
        if (cpStr[i] != TEXT(' ') && cpStr[i] != TEXT('　'))
            break;
        cpStr[i] = TEXT('\0');
    }

    cpStart = cpStr;
    while (*cpStart == TEXT(' ') || *cpStart == TEXT('　')) {
        cpStart++;
    }
    wmemmove(cpStr, cpStart, wcslen(cpStart) + 1);
    return 1;
}

/*
#include <Tlhelp32.h>
int TerminateExeName(const TCHAR* TrFileName) {
    PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        BOOL bResult = Process32First(hSnap, &pe);
        while(bResult) {
            bResult = Process32Next(hSnap, &pe);
            if (!wcscmp(pe.szExeFile, TrFileName)) {
                HANDLE hProcess = OpenProcess(
                    PROCESS_ALL_ACCESS,
                    FALSE,
                    pe.th32ProcessID);
                TerminateProcess(hProcess, 0);
                GetExitCodeProcess(hProcess, 0);
                CloseHandle(hProcess);
wprintf(TEXT("id: %u\t\t"), pe.th32ProcessID);
wprintf(TEXT("sz: %s\t\t"), pe.szExeFile);
wprintf(TEXT("tr: %s\n"), TrFileName);
            }
        }
        CloseHandle(hSnap);
    }
    return 0;
}
*/
