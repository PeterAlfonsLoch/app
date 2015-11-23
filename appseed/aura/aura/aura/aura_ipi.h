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
      //string_map < sp(::aura::ipc::tx) >     m_txmodules;
      ::aura::ipc::rx                        m_rx;
      stringa                                m_straModule;

      ipi(::aura::application * papp,const string & strApp);

      void defer_add_module(const string & strModule);


      template<typename T,typename... Args>
      int_map < var > ecall(const string & strApp,int_array iaExcludePid, const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return ecall(strApp,iaExcludePid, strObject,strMember,va);

      }

      virtual int_map < var > ecall(const string & strApp,int_array iaExcludePid,const string & strObject,const string & strMember,var_array & va);

      template<typename T,typename... Args>
      int_map < var > call(const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return call(strApp,strObject,strMember,va);

      }

      virtual int_map < var > call(const string & strApp,const string & strObject,const string & strMember,var_array & va);


      template<typename T,typename... Args>
      int_map < var > scall(bool bAutoLaunch, const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return scall(bAutoLaunch, strApp,strObject,strMember,va);

      }

      virtual int_map < var > scall(bool bAutoLaunch,const string & strApp,const string & strObject,const string & strMember,var_array & va);

      template<typename T,typename... Args>
      var call(const string & strApp,int iPid, const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return call(strApp,iPid, strObject,strMember,va);

      }

      virtual var call(const string & strApp,int iPid, const string & strObject,const string & strMember,var_array & va);

      ::aura::ipc::tx & tx(const string & strApp, int iPid);

      int_array get_pid(const string & strApp);

      virtual string key(const string &strApp, int iPid);

      string str_from_va(var_array & va);

      virtual void on_call(const string & strObject,const string & strMember,var_array & va);

      virtual void on_receive(::aura::ipc::rx * prx,const char * pszMessage);

      virtual bool start(const string & strApp);

      virtual bool connect(const string & strApp, int iPid);

      virtual void on_new_instance(const string & strModule, int iPid);

      

   };


} // namespace aura


