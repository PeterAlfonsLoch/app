
namespace aura
{



   ipi::ipi(::aura::application * papp,const string & strApp):
      ::object(papp),
      m_rx(papp)
   {

      m_pmutex = new mutex(papp);

      m_strApp          = strApp;

      defer_add_module(System.file().module());

      ::file::path p = module_path_from_pid(System.os().get_pid());

      defer_add_module(p);

      m_rx.m_preceiver  = this;

	   if(!m_rx.create(key(strApp, System.os().get_pid())))
         throw ::resource_exception(papp);

   }


   var ipi::call(const string & strApp,int iPid, const string & strObject,const string & strMember,var_array & va)
   {

      ::aura::ipc::tx & txc = tx(strApp,iPid);

      txc.send("call " + strObject + "." + strMember + " : " + str_from_va(va),584);

      return ::var();

   }

   int_map < var > ipi::scall(bool bAutoLaunch, const string & strApp,const string & strObject,const string & strMember,var_array & va)
   {

      int_map < var > map;

      int_array iaPid = get_pid(strApp);

      if(iaPid.get_count() <= 0)
      {

         if(!bAutoLaunch)
         {

            return map;

         }

         start(strApp);

         iaPid = get_pid(strApp);

      }

      for(int iPid : iaPid)
      {

         map[iPid] = call(strApp,iPid,strObject,strMember,va);

      }

      return map;

   }

   int_map < var > ipi::call(const string & strApp,const string & strObject,const string & strMember,var_array & va)
   {

      int_map < var > map;

      int_array iaPid = get_pid(strApp);

      for(int iPid : iaPid)
      {

         map[iPid] = call(strApp, iPid, strObject, strMember, va);

      }

      return map;

   }


   int_map < var > ipi::ecall(const string & strApp,int_array iaExcludePid, const string & strObject,const string & strMember,var_array & va)
   {

      int_map < var > map;

      int_array iaPid = get_pid(strApp);

      iaPid -= iaExcludePid;

      for(int iPid : iaPid)
      {

         map[iPid] = call(strApp,iPid,strObject,strMember,va);

      }

      return map;

   }


   bool ipi::start(const string & strApp)
   {

      synch_lock sl1(m_pmutex);

      mutex * pmutex = m_mapAppMutex[strApp];

      if(pmutex == NULL)
      {

         pmutex = new mutex(get_app());

         m_mapAppMutex[strApp] = pmutex;

      }

      sl1.unlock();

      synch_lock sl(pmutex);

      int_array iaPid = get_pid(strApp);

      if(iaPid.get_count() > 0)
      {

         return true;

      }

      ::aura::app_launcher launcher(strApp);

      int iPid = -1;

      {

         int_array ia = get_pid(strApp);

         if(ia.get_count() <= 0)
         {

            launcher.start();

            int iStep = 0;

            while(iStep < 8)
            {

               iStep++;

               ia = get_pid(strApp);

               if(ia.get_count() > 0)
               {

                  goto started;

               }

               Sleep(iStep * 784);

            }

            return false;

         }

         started:

         iPid = ia[0];

      }

      string strKey = strApp + ":" + ::str::from(iPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = canew(::aura::ipc::tx(get_app()));

      }

      return m_txmap[strKey]->open(key(strApp,iPid));


   }


   bool ipi::connect(const string & strApp, int iPid)
   {

      string strKey = strApp + ":" + ::str::from(iPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = canew(::aura::ipc::tx(get_app()));

      }

      if(m_txmap[strKey]->is_tx_ok())
      {

         return true;

      }
      else
      {

         return m_txmap[strKey]->open(key(strApp, iPid));

      }

   }


   ::aura::ipc::tx & ipi::tx(const string & strApp, int iPid)
   {

      string strKey = strApp + ":" + ::str::from(iPid);

      if(m_txmap[strKey].is_null())
      {

         m_txmap[strKey] = canew(::aura::ipc::tx(get_app()));

      }

      if(!m_txmap[strKey]->is_tx_ok())
      {

         connect(strApp, iPid);

      }

      return *m_txmap[strKey];

   }


   string ipi::key(const string &strApp, int iPid)
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

      strKey = "::ca2::fontopus::cgcl-1984-11-15::m-1951-04-22::cx-1977-02-04::votagus::" + strApp + ":" + iPid;

#endif

#else

   #ifdef LINUX

      strKey = ::file::path(getenv("HOME")) / ".ca2/Application Support/ca2/ipi" / strApp / ::str::from(iPid);

   #else

      strKey = ::file::path(getenv("HOME")) / "Library/Application Support/ca2/ipi" / strApp / ::str::from(iPid);

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

      if(strObject == "application")
      {

         if(strMember == "on_exclusive_instance_local_conflict")
         {

            Application.on_exclusive_instance_local_conflict(va[0],va[1]);

         }
         else if(strMember == "on_new_instance")
         {

            on_new_instance(va[0], va[1]);

         }

      }

   }

   void ipi::on_new_instance(const string & strModule, int iPid)
   {

      defer_add_module(strModule);

      Application.on_new_instance(strModule, iPid);

   }


   int_array ipi::get_pid(const string & strApp)
   {

      int_array iaPid;

      #ifdef LINUX


         iaPid = app_get_pid(strApp);


      #else

#if defined(METROWIN)

      iaPid.add(1);

#else

      stringa stra;

      ::file::path pathModule;

      #ifdef LINUX

      pathModule = "/tmp/ca2/config/ipi";

      #else

      pathModule = "C:/ca2/config/ipi";

      #endif

      pathModule /= strApp + ".module_list";

      string strModuleList = file_as_string_dup(pathModule);

      stra.add_lines(strModuleList);

      stringa stra2;

      for(auto & str : stra)
      {

         if(str.has_char())
         {

            stra2.add_unique_ci(str);

         }

      }


      for(auto & str : stra2)
      {

         if(str.has_char())
         {

            iaPid.add(module_path_get_pid(str));

         }

      }

#endif
#endif
      return iaPid;

   }


   void ipi::defer_add_module(const string & strModule)
   {

      ::file::path pathModule;

      m_straModule.remove_all();

#ifdef LINUX

	pathModule = "/tmp/ca2/config/ipi";

#else

      pathModule = "C:/ca2/config/ipi";

#endif

      pathModule /= m_strApp + ".module_list";

      string strModuleList = file_as_string_dup(pathModule);

      m_straModule.add_lines(strModuleList);

      stringa straUnique;

      forallref(m_straModule)
      {

         straUnique.add_unique_ci(item);

      }

      m_straModule = straUnique;

      ::file::path pathThisModule = System.file().module();

      m_straModule.add_unique_ci(strModule);

      strModuleList = m_straModule.implode("\n");

      file_put_contents_dup(pathModule,strModuleList);

   }

} // namespace aura


