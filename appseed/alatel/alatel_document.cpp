#include "StdAfx.h"

namespace alatel
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   }

   BOOL document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;


      // ensure 10-alarm-tel

      string strProfile("by_weekday");

      int i = 1;
      while(true)
      {
         stringa stra;
         string strAlarm;
         data_get(strProfile, "name", stra);
         if(stra.get_size() >= 10)
            break;
         while(true)
         {
            strAlarm.Format("Alarm %d", i);
            if(!stra.contains_ci(strAlarm))
               break;
            i++;
         }
         stra.add(strAlarm);
         data_set(strProfile, "name", stra);

         int_array iaHour;
         data_get(strProfile, "hour", iaHour);
         iaHour.add(0);
         data_set(strProfile, "hour", iaHour);

         int_array iaMinute;
         data_get(strProfile, "minute", iaMinute);
         iaMinute.add(0);
         data_set(strProfile, "minute", iaMinute);

         int_array iaSecond;
         data_get(strProfile, "second", iaSecond);
         iaSecond.add(0);
         data_set(strProfile, "second", iaSecond);
      }

      update_all_views(NULL, 22);



      stringa wstra;
      data_get("SongDirectorySet", 0, wstra);



      update_all_views(NULL, 0);

      string str;
      str = "<alatel>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 10 de abril de 2008</span>\n";
      str += "<h1>Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>";
      str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
      str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
      str += "<br />";
      str += "<span>Você conhece o ca2?</span>";
      str += "<br />";
      str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
      str += "<br />";
      str += "<input type=\"text\" />";
      str += "</body>\n";
      str += "</alatel>\n";

	   return TRUE;
   }

   document::~document()
   {
   }


   //BEGIN_MESSAGE_MAP(document, ::userbase::document)
	   //{{AFX_MSG_MAP(document)
		   // NOTE - the ClassWizard will add and remove mapping macros here.
	   //}}AFX_MSG_MAP
   //END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // document diagnostics

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context& dc) const
   {
	   ::userbase::document::dump(dc);
   }
   #endif //_DEBUG

   void document::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
      update_all_views(NULL, 123);
      return TRUE;
   }


   index document::create_alarm(const char * pszProfile)
   {
      stringa stra;
      data_get(pszProfile, "name", stra);
      int i = stra.get_size() + 1;
      string strAlarm;
      while(true)
      {
         strAlarm.Format("Alarm %d", i);
         if(!stra.contains_ci(strAlarm))
            break;
         i++;
      }
      stra.add(strAlarm);
      data_set(pszProfile, "name", stra);

      int_array iaHour;
      data_get(pszProfile, "hour", iaHour);
      iaHour.add(0);
      data_set(pszProfile, "hour", iaHour);

      int_array iaMinute;
      data_get(pszProfile, "minute", iaMinute);
      iaMinute.add(0);
      data_set(pszProfile, "minute", iaMinute);

      int_array iaSecond;
      data_get(pszProfile, "second", iaSecond);
      iaSecond.add(0);
      data_set(pszProfile, "second", iaSecond);

      update_all_views(NULL, 22);

      return stra.get_upper_bound();
   }
   count document::get_alarm_count(const char * pszProfile)
   {
      stringa stra;
      data_get(pszProfile, "name", stra);
      return stra.get_count();
   }

   bool document::remove_alarm(const char * pszProfile, index iIndex)
   {
      stringa stra;
      data_get(pszProfile, "name", stra);
      stra.remove_at(iIndex);
      data_set(pszProfile, "name", stra);

      int_array iaHour;
      data_get(pszProfile, "hour", iaHour);
      iaHour.remove_at(iIndex);
      data_set(pszProfile, "hour", iaHour);

      int_array iaMinute;
      data_get(pszProfile, "minute", iaMinute);
      iaMinute.remove_at(iIndex);
      data_set(pszProfile, "minute", iaMinute);

      int_array iaSecond;
      data_get(pszProfile, "second", iaSecond);
      iaSecond.remove_at(iIndex);
      data_set(pszProfile, "second", iaSecond);

      update_all_views(NULL, 22);

      return true;
   }

   bool document::set_alarm_name(const char * pszProfile, index iIndex, const char * pszName)
   {

      stringa stra;
      data_get(pszProfile, "name", stra);
      stra[iIndex] = pszName;
      data_set(pszProfile, "name", stra);
      return true;
   }

   bool document::set_alarm_hour(const char * pszProfile, index iIndex, int iHour)
   {
      int_array ia;
      data_get(pszProfile, "hour", ia);
      ia[iIndex] = iHour;
      data_set(pszProfile, "hour", ia);
      return true;
   }

   bool document::set_alarm_minute(const char * pszProfile, index iIndex, int iMinute)
   {
      int_array ia;
      data_get(pszProfile, "minute", ia);
      ia[iIndex] = iMinute;
      data_set(pszProfile, "minute", ia);
      return true;
   }

   bool document::set_alarm_second(const char * pszProfile, index iIndex, int iSecond)
   {
      int_array ia;
      data_get(pszProfile, "second", ia);
      ia[iIndex] = iSecond;
      data_set(pszProfile, "second", ia);
      return true;
   }

   var document::get_alarm_name(const char * pszProfile, index iIndex)
   {
      stringa stra;
      data_get(pszProfile, "name", stra);
      return stra[iIndex];
   }

   var document::get_alarm_hour(const char * pszProfile, index iIndex)
   {
      int_array ia;
      data_get(pszProfile, "hour", ia);
      return ia[iIndex];
   }

   var document::get_alarm_minute(const char * pszProfile, index iIndex)
   {
      int_array ia;
      data_get(pszProfile, "minute", ia);
      return ia[iIndex];
   }

   var document::get_alarm_second(const char * pszProfile, index iIndex)
   {
      int_array ia;
      data_get(pszProfile, "second", ia);
      return ia[iIndex];
   }


} // namespace alatel