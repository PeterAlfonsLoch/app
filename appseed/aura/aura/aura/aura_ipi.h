#pragma once


namespace aura
{


   class CLASS_DECL_AURA ipi:
      virtual public object,
      virtual public ::aura::ipc::rx::receiver
   {
   public:


      string                                 m_strApp;
      string_map < ::aura::ipc::tx >         m_txmap;
      ::aura::ipc::rx                        m_rx;

      ipi(::aura::application * papp,const string & strApp);


      template<typename T,typename... Args>
      var call(const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return call(strApp,strObject,strMember,va);

      }

      virtual var call(const string & strApp,const string & strObject,const string & strMember,var_array & va);

      ::aura::ipc::tx & tx(const string & strApp);

      virtual string key(const string &strApp);

      string str_from_va(var_array & va);

      virtual void on_call(const string & strObject,const string & strMember,var_array & va);

      virtual void on_receive(::aura::ipc::rx * prx,const char * pszMessage);

      virtual void start_app(const string & strApp);

      virtual bool defer_start_app(const string & strApp, bool bShouldAutoLaunch = true);

   };


} // namespace aura


