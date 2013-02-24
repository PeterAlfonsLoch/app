#pragma once

#undef new

namespace ca
{

   inline void * object::operator new(size_t nSize)
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

   inline void * object::operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
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


} // namespace ca


#define new DEBUG_NEW


