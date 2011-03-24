#pragma once


namespace ca
{
   class CLASS_DECL_ca lock :
      virtual public ::radix::object
   {
   public:
      lock(::radix::object * pobject, bool bLock = true);
      virtual ~lock();

      virtual bool Lock(DWORD dwTimeout = INFINITE);
      virtual bool Unlock();

   protected:
      bool              m_bLocked;
      ::radix::object *     m_pobject;
   };
}


