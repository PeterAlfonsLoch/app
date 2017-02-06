#include "framework.h"


typedef struct _PROCESS_BASIC_INFORMATION64 {
   uint64_t  Reserved1;
   uint64_t  PebBaseAddress;
   uint64_t  Reserved2[2];
   uint64_t  UniqueProcessId;
   uint64_t  Reserved3;
} PROCESS_BASIC_INFORMATION64;

typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(HANDLE ProcessHandle, uint32_t ProcessInformationClass, PVOID ProcessInformation, uint32_t ProcessInformationLength, PDWORD ReturnLength);

PPEB GetPebAddress(HANDLE handleProcess);

CLASS_DECL_AURA string get_command_line(HANDLE handleProcess)
{

   PPEB ppeb = GetPebAddress(handleProcess);

   PRTL_USER_PROCESS_PARAMETERS pparam1 = NULL;

   if (!ReadProcessMemory(handleProcess, (PCHAR)&ppeb->ProcessParameters, &pparam1, sizeof(PRTL_USER_PROCESS_PARAMETERS), NULL) || pparam1 == NULL)
   {
      ::OutputDebugStringA("Could not read the address of ProcessParameters!\n");
      return "";
   }


   _UNICODE_STRING ustrCommandLine;

   if (!ReadProcessMemory(handleProcess, (PCHAR)&pparam1->CommandLine, &ustrCommandLine, sizeof(ustrCommandLine), NULL))
   {
      ::OutputDebugStringA("Could not read CommandLine!\n");
      return "";
   }

   /* allocate memory to hold the command line */
   WCHAR * commandLineContents = (WCHAR *)memory_alloc(ustrCommandLine.Length + sizeof(WCHAR));
   /* read the command line */
   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, NULL))
   {
      ::OutputDebugStringA("Could not read the command line string!\n");
      return "";
   }
   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
   string str = ::str::international::unicode_to_utf8(commandLineContents);
   memory_free_dbg(commandLineContents, 0);
   return str;
}






string get_display_error(uint32_t NTStatusMessage);

PPEB GetPebAddress(HANDLE handleProcess)
{
   _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
   PROCESS_BASIC_INFORMATION pbi;
   memset_dup(&pbi, 0, sizeof(pbi));
   DWORD dwInLen = sizeof(pbi);
   DWORD dwOutLen = 0xffffffff;
   uint32_t dwStatus = NtQueryInformationProcess(handleProcess, ProcessBasicInformation, &pbi, dwInLen, &dwOutLen);
   string strError = get_display_error(dwStatus);
   if ((dwStatus & 3) == 3)
   {
      return NULL;
   }
   return pbi.PebBaseAddress;
}


string get_display_error(uint32_t NTStatusMessage)
{

   return get_system_error_message(NTStatusMessage);

}



