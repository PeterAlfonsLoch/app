//#include "framework.h"


namespace aura
{


   live_signal::live_signal()
   {

   }

   live_signal::live_signal(const live_signal & signal)
   {

      operator = (signal);

   }

   void live_signal::keep(object * pliveobject)
   {

      if(pliveobject != NULL)
      {

         m_ptraLive.add(pliveobject);

      }

   }

   void live_signal::unkeep(object * pliveobject)
   {

      if(pliveobject != NULL)
      {

         m_ptraLive.remove(pliveobject);

      }

   }

   void live_signal::on_keep_alive()
   {

      for(int32_t i = 0; i < m_ptraLive.get_count(); i++)
      {

         try
         {

            m_ptraLive.element_at(i)->keep_alive();

         }
         catch(...)
         {

         }

      }

   }

   bool live_signal::is_alive()
   {

      return true;

      for(int32_t i = 0; i < m_ptraLive.get_count(); i++)
      {

         try
         {

            if(!m_ptraLive.element_at(i)->is_alive())
               return false;

         }
         catch(...)
         {

            return false;

         }

      }

      return true;

   }

   live_signal & live_signal::operator = (const live_signal & signal)
   {

      if(this != &signal)
      {
         m_ptraLive = signal.m_ptraLive;
      }

      return *this;

   }


} // namespace core


