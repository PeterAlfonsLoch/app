#pragma once

#undef new

namespace radix
{

   inline void * PASCAL object::operator new(size_t nSize)
   {
      void * p = ::operator new(nSize);
      /*try
      {
         if(::ca::get_thread_state() != NULL)
         {
            ::ca::get_thread_state()->m_heapitema.add_item(p, nSize);
         }
      }
      catch(...)
      {
      }*/
      return p;
   }


#ifdef DEBUG

   inline void * PASCAL object::operator new(size_t nSize, const char * lpszFileName, int nLine)
   {
      void * p = ::operator new(nSize, ___CLIENT_BLOCK, lpszFileName, nLine);
      /*try
      {
         if(::ca::get_thread_state() != NULL)
         {
            ::ca::get_thread_state()->m_heapitema.add_item(p, nSize);
         }
      }
      catch(...)
      {
      }*/
      return p;
   }

#endif


} // namespace radix


#define new DEBUG_NEW


