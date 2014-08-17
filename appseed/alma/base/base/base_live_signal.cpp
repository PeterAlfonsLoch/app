#include "framework.h"


namespace base
{


   live_signal::live_signal()
   {

   }

   live_signal::live_signal(const live_signal & signal)
   {

      operator = (signal);

   }

   void live_signal::keep(live_object * pliveobject)
   {

      if(pliveobject != NULL)
      {

         add(pliveobject);

      }

   }

   void live_signal::unkeep(live_object * pliveobject)
   {

      if(pliveobject != NULL)
      {

         remove(pliveobject);

      }

   }

   void live_signal::on_keep_alive()
   {

      for(int32_t i = 0; i < this->get_count(); i++)
      {

         try
         {

            this->element_at(i)->keep_alive();

         }
         catch(...)
         {

         }

      }

   }

   bool live_signal::is_alive()
   {

      return true;

      for(int32_t i = 0; i < this->get_count(); i++)
      {

         try
         {

            if(!this->element_at(i)->is_alive())
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
         ::comparable_array < live_object * >::operator = ((::comparable_array < live_object * >) (signal));
      }

      return *this;

   }


} // namespace core


