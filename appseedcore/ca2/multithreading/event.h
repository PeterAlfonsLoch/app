#pragma once

class CLASS_DECL_ca CEvent : 
   public sync_object < HANDLE >
{
private:

#if !core_level_1
   using sync_object < HANDLE > ::Unlock;
#endif

// Constructor
public:
   CEvent(BOOL bInitiallyOwn = FALSE, BOOL bManualReset = FALSE, LPCTSTR lpszNAme = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);

// Operations
public:
   BOOL SetEvent();
   BOOL PulseEvent();
   BOOL ResetEvent();
   BOOL Unlock();

// Implementation
public:
   virtual ~CEvent();
};
