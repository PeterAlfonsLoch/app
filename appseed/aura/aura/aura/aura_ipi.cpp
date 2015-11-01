
namespace aura
{



   ipi::ipi(::aura::application * papp,const string & strApp):
      ::object(papp),
      m_rx(papp)
   {
      
      m_strApp          = strApp;

      m_rx.m_preceiver  = this;

	   if(!m_rx.create(key(strApp)))
         throw ::resource_exception(papp);

   }


   var ipi::call(const string & strApp,const string & strObject,const string & strMember,var_array & va)
   {

      ::aura::ipc::tx & txc = tx(strApp);

      txc.send("call " + strObject + "." + strMember + " : " + str_from_va(va),584);

      return ::var();

   }


   void ipi::start_app(const string & strApp)
   {

      defer_start_app(strApp);

   }

   bool ipi::defer_start_app(const string & strApp,bool bShouldAutoLaunch)
   {

      if(m_txmap[strApp].is_null())
      {

         m_txmap[strApp] = canew(::aura::ipc::tx(get_app()));

      }

#ifndef METROWIN

      if(bShouldAutoLaunch)
      {

         ::aura::app_launcher launcher(strApp);

         return m_txmap[strApp]->open(key(strApp),&launcher);

      }
      else 

#endif

      if(m_txmap[strApp]->is_tx_ok())
      {

         return true;

      }
      else
      {

         ::aura::app_launcher launcher("");

         launcher.m_iStart = 0;

         return m_txmap[strApp]->open(key(strApp), &launcher);

      }

   }


   ::aura::ipc::tx & ipi::tx(const string & strApp)
   {

      if(m_txmap[strApp].is_null())
      {

         m_txmap[strApp] = canew(::aura::ipc::tx(get_app()));

      }

      if(!m_txmap[strApp]->is_tx_ok())
      {

         start_app(strApp);

      }

      return *m_txmap[strApp];

   }


   string ipi::key(const string &strApp)
   {

      string strKey;

#ifdef WINDOWS

#ifdef METROWIN

      string strAppId(strApp);

      strAppId.replace("\\","_");

      strAppId.replace("/","_");

      strAppId.replace("-","_");

      strKey = "core_" + strAppId;

#else

      strKey = "::ca2::fontopus::cgcl-1984-11-15::m-1951-04-22::cx-1977-02-04::votagus::" + strApp;

#endif

#else

   #ifdef LINUX
   
      strKey = ::file::path(getenv("HOME")) / ".ca2/Application Support/ca2/ipi" / strApp;

   #else
      
      strKey = ::file::path(getenv("HOME")) / "Library/Application Support/ca2/ipi" / strApp;

   #endif

#endif

      return strKey;


   }


   string ipi::str_from_va(var_array & va)
   {

      if(va.get_count() <= 0)
      {

         return ";";

      }

      string str;

      for(var & v : va)
      {

         str += v.get_string();

         str += ";";

      }

      return str;

   }

   void ipi::on_receive(::aura::ipc::rx * prx,const char * pszMessage)
   {
      
      string str(pszMessage);

      if(!::str::begins_eat(str,"call "))
         return;

      strsize iFind = str.find(":");

      string str1;
      string strObject;
      string strMember;
      stringa stra;
      var_array va;


      if(iFind < 0 || iFind > 3)
      {
         if(iFind > 3)
         {
            str1 = str.Left(iFind);
         }
         else
         {
            str1 = str;
         }

         str1.trim();

         strsize iFind2 = str1.find(".");

         if(iFind2 < 0)
         {

            return;

         }

         strObject = str1.Left(iFind2);
         strMember = str1.Mid(iFind2 + 1);
         if(iFind < 0)
         {
            on_call(strObject,strMember,va);
            return;
         }
      }
      else
      {
         return;
      }

      str1 = str.Mid(iFind + 1);

      stra.explode(";",str1);

      if(stra.has_elements())
      {

         stra.remove_last();

      }

      stra.trim();

      va = stra;

      on_call(strObject,strMember,va);

   }


   void ipi::on_call(const string & strObject,const string & strMember,var_array & va)
   {

   }


} // namespace aura


