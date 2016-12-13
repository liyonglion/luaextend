#ifndef __LY_OS__H
#define __LY_OS__H
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#if defined(WINDOW)
#include <winsock2.h>
#include <windows.h>
//#include <MsRdc.h>
#include <process.h>
#include <tlhelp32.h>
#include <io.h>
#pragma comment(lib, "ws2_32.lib")
#endif

int getPageSize();

#if defined(WINDOW)
#define getuid() -1
#define geteuid() -1
#define getgid() -1
#define getegid() -1


#define getpid() _getpid()

DWORD getppid()
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    
    if( hSnapshot == INVALID_HANDLE_VALUE ){
        return -1;
    }

    ZeroMemory( &pe32, sizeof( pe32 ) );
    pe32.dwSize = sizeof( pe32 );
    if( !Process32First( hSnapshot, &pe32 ) ){
        CloseHandle( hSnapshot );
        return -1;
    }

    do{
        if( pe32.th32ProcessID == pid ){
            ppid = pe32.th32ParentProcessID;
            break;
        }
    }while( Process32Next( hSnapshot, &pe32 ) );

    if( hSnapshot != INVALID_HANDLE_VALUE ) CloseHandle( hSnapshot );
    return ppid;
}

int GetFullPath(const char *path,char *pbuffer,size_t pbuffer_size){
    char *ppart = NULL;
    return !GetFullPathName(path, pbuffer_size, pbuffer, &ppart);
}

#elif defined(LINUX)

int GetFullPath(const char *path,char *pbuffer,size_t pbuffer_size){
    memset(pbuffer, 0, pbuffer_size);
    return !realpath(path, pbuffer);
}

#endif

int isDir(const char *path);

#define STATSTRING "LIONSTAT"
#define FDSTRING "LIONFD"
#endif

