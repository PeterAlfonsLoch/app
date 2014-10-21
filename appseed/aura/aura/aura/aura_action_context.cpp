#include "framework.h"


namespace action
{


   /*e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc)
   {


      switch(econtextSrc)
      {
      case context_this_set_text:
         switch (econtextDst)
         {
         case context_this_on_after_change_text:
            return context_this_set_text;
         default:
            break:
         }
      default:
         break;
      }

      return esource;

   }*/


   void context::add(object * pobject)
   {
      
      m_spdata->m_spa.add(pobject);

   }


   index context::find(object * pobject)
   {

      for (index i = 0; i < m_spdata->m_spa.get_count(); i++)
      {

         if (m_spdata->m_spa[i] == pobject)
            return i;

      }

      return -1;

   }


   bool context::contains(object * pobject)
   {

      return find(pobject) >= 0;

   }



} // namespace action





