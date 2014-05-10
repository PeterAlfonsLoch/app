/*
   Author   :   Nishant Sivakumar
   Date   :   June 9, 2005
   Info   :   Template class that makes it easy to use data allocated
            in a different process. Useful when making inter-process
            SendMessage/PostMessage calls.
   Contact   :   nish@voidnish.com
*/

//ProcessData.h

#pragma once

#ifdef WINDOWS

template<typename T> class process_data
{
public:
   /*
      If you pass in a dwProcessId of 0, the current process Id is used.
      For the other arguments, see MSDN documentation for OpenProcess and
      VirtualAllocEx.
   */
   process_data(uint32_t dwProcessId = 0, uint32_t dwDesiredAccess = PROCESS_ALL_ACCESS,
      uint32_t flAllocationType = MEM_COMMIT, uint32_t flProtect = PAGE_READWRITE)
   {
      m_hProcess = OpenProcess(dwDesiredAccess, FALSE,
         dwProcessId ? dwProcessId : GetCurrentProcessId());
      if(m_hProcess)
      {
         m_lpData = VirtualAllocEx(m_hProcess, NULL, sizeof T,
            flAllocationType, flProtect);
         ASSERT(m_lpData);
      }
      else
      {
//         TRACE("process_data::m_hProcess == NULL");
      }
   }

   ~process_data()
   {
      if(m_hProcess)
      {
         if(m_lpData)
         {
            VirtualFreeEx(m_hProcess, m_lpData, 0, MEM_RELEASE);
         }
         CloseHandle(m_hProcess);
      }
   }

   //WriteData is used to copy data to primitive::memory in the foreign process
   bool WriteData(const T& data)
   {
      return (m_hProcess && m_lpData) ? WriteProcessMemory(m_hProcess, m_lpData,
         (LPCVOID)&data, sizeof T, NULL) : FALSE;
   }

   //ReadData reads back data from primitive::memory in the foreign process
   bool ReadData(T* data)
   {
      return (m_hProcess && m_lpData) ? ReadProcessMemory(m_hProcess, m_lpData, (LPVOID)data, sizeof T, NULL) != FALSE : false;
   }

   //Templated ReadData that's used to read a specific data type from
   //a primitive::memory address located in the foreign process
   template<typename TSUBTYPE> bool ReadData(TSUBTYPE* data, LPCVOID lpData)
   {
      return m_hProcess ? ReadProcessMemory(m_hProcess, lpData, (LPVOID)data, sizeof TSUBTYPE, NULL) != FALSE : false;
   }

   //Gets the address of the allocated primitive::memory in the foreign process
   const T* get_data()
   {
      return (m_hProcess && m_lpData) ? (T*)m_lpData : NULL;
   }
private:
   HANDLE m_hProcess;
   LPVOID m_lpData;
};


#endif
