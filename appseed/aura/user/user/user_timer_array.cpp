#include "framework.h" // previously aura/user/user.h


namespace user
{



   timer_array::timer_array(sp(::aura::application) papp):
      element(papp),
      m_mutex(papp)
   {

   }


   timer_array::~timer_array()
   {

   }


   bool timer_array::unset(interaction * pui,uint_ptr uiId)
   {


      single_lock sl(&m_mutex,TRUE);


      index i = find(pui,uiId);
      if(i >= 0)
      {
         m_timera.remove_at(i);
         if(find_from(pui,0) < 0)
         {
            m_uiptra.remove(pui);
         }
         return true;
      }
      return false;
   }

   void timer_array::detach(smart_pointer_array < timer_item > & timera,interaction * pui)
   {


      single_lock sl(&m_mutex,TRUE);

      timera = m_timera;
      m_timera.remove_all();

      for(int32_t i = 0; i < timera.get_count();)
      {
         if(timera[i]->m_pui == pui)
         {
            i++;
         }
         else
         {
            m_timera.add(new timer_item(timera[i]));
            timera.remove_at(i);
         }
      }

   }


   void timer_array::unset(interaction * pui)
   {

      retry_single_lock sl(&m_mutex,millis(177),millis(184));

      index i = 0;

      while((i = find_from(pui,i)) >= 0)
      {
         m_timera.remove_at(i);
      }

      if(find_from(pui,0) < 0)
      {
         m_uiptra.remove(pui);
      }

   }

   index timer_array::find(interaction * pui,uint_ptr uiId)
   {


      retry_single_lock sl(&m_mutex,millis(177),millis(184));


      for(index i = 0; i < m_timera.get_count(); i++)
      {
         if(m_timera[i]->m_pui == pui && m_timera[i]->m_uiId == uiId)
         {
            return i;
         }
      }

      return -1;

   }

   index timer_array::find_from(interaction * pui,index iStart)
   {


      retry_single_lock sl(&m_mutex,millis(177),millis(184));


      for(index i = iStart; i < m_timera.get_count(); i++)
      {
         if(m_timera[i]->m_pui == pui)
         {
            return i;
         }
      }

      return -1;

   }

   void timer_array::dump(dump_context & dc) const
   {
      UNREFERENCED_PARAMETER(dc);
   }

   void timer_array::assert_valid() const
   {

   }



   void timer_array::check()
   {


      single_lock sl(&m_mutex,TRUE);

      if(m_iItem >= m_timera.get_count())
         m_iItem = m_timera.get_upper_bound();

      if(m_iItem < 0)
         m_iItem = 0;


      index iPreviousItem = m_iItem;

      for(; m_iItem < m_timera.get_count();)
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }
         m_iItem++;
      }

      m_iItem = 0;

      for(; m_iItem < MIN(iPreviousItem,m_timera.get_count());)
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }

         m_iItem++;
      }

   }


   uint_ptr timer_array::set(interaction * pui,uint_ptr uiId,UINT uiElapse)
   {


      single_lock sl(&m_mutex,TRUE);


      if(pui == NULL)
         return 0xffffffff;

      m_uiptra.add(pui);

      index i = find(pui,uiId);

      if(i >= 0)
      {

         m_timera[i].m_uiElapse = uiElapse;
         m_timera[i].m_uiLastSent = ::get_tick_count();

         return (UINT)i;

      }
      else
      {

         sp(timer_item) item(canew(timer_item(get_app())));

         item->m_pui = pui;
         item->m_uiId = uiId;
         item->m_uiElapse = uiElapse;
         item->m_uiLastSent = ::get_tick_count();

         return (UINT)m_timera.add(item);

      }

   }




















































} // namespace user























