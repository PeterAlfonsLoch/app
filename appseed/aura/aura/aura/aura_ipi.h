#pragma once


namespace aura
{


   class CLASS_DECL_AURA ipi:
      virtual public object,
      virtual public ::aura::ipc::rx::receiver
   {
   public:


      string                                 m_strApp;
      string_map < sp(::aura::ipc::tx) >     m_txmap;
      string_to_string                       m_to_p;
      string_to_string                       m_from_p;
      ::aura::ipc::rx                        m_rx;
      ::aura::ipc::rx                        m_rxProcess;

      ipi(::aura::application * papp,const string & strApp);

      template<typename T,typename... Args>
      var pcall(const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return pcall(strApp,strObject,strMember,va);

      }

      virtual var pcall(const string & strApp,const string & strObject,const string & strMember,var_array & va);

      template<typename T,typename... Args>
      var call(const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return call(strApp,strObject,strMember,va);

      }

      virtual var call(const string & strApp,const string & strObject,const string & strMember,var_array & va);

      ::aura::ipc::tx & tx(const string & strApp);
      ::aura::ipc::tx & ptx(const string & strApp);

      virtual string key(const string &strApp);

      virtual string process_key(const string &strModule, int iPid);

      virtual string process_key();

      string str_from_va(var_array & va);

      virtual void on_call(const string & strObject,const string & strMember,var_array & va);

      virtual void on_receive(::aura::ipc::rx * prx,const char * pszMessage);

      virtual void start_app(const string & strApp);

      virtual bool defer_start_app(const string & strApp, bool bShouldAutoLaunch = true);

   };


} // namespace aura


