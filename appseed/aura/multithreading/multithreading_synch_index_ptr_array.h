#pragma once


class CLASS_DECL_AXIS synch_index_ptr_array:
   virtual protected ptr_array < index >
{
public:

   
   ::mutex * m_pmutex;


   synch_index_ptr_array(mutex * pmutex) { m_pmutex = pmutex; }
   virtual ~synch_index_ptr_array() {}

   void reg(index *pi)
   {
      synch_lock sl(m_pmutex);
      add(pi);
   }

   void on_removed(index i)
   {

      synch_lock sl(m_pmutex);

      for(index iPointer = 0; iPointer < get_count(); iPointer++)
      {
         if(*element_at(iPointer) > i)
         {

            (*element_at(iPointer))--;

         }
      }

   }

   void unreg(index *pi)
   {
      synch_lock sl(m_pmutex);
      remove(pi);
   }
#undef new
   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new AXIS_NEW

};





