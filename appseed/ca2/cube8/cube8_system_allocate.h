#pragma once

#undef new

namespace radix
{

   inline void * PASCAL object::operator new(size_t nSize)
   {
      void * p = ::operator new(nSize, _AFX_CLIENT_BLOCK, NULL, 0);
      try
      {
         if(::ax::get_thread_state() != NULL)
         {
            ::ax::get_thread_state()->m_heapitema.add_item(p, nSize);
         }
      }
      catch(...)
      {
      }
      return p;
   }

   inline void * PASCAL object::operator new(size_t nSize, const char * lpszFileName, int nLine)
   {
      void * p = ::operator new(nSize, _AFX_CLIENT_BLOCK, lpszFileName, nLine);
      try
      {
         if(::ax::get_thread_state() != NULL)
         {
            ::ax::get_thread_state()->m_heapitema.add_item(p, nSize);
         }
      }
      catch(...)
      {
      }
      return p;
   }

} // namespace radix

#define new DEBUG_NEW