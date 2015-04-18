#pragma once


namespace aura
{


   class CLASS_DECL_AURA ipi:
      virtual public object,
      virtual public small_ipc_rx_channel::receiver
   {
   public:


      string                                 m_strApp;
      string_map < small_ipc_tx_channel >    m_txmap;
      small_ipc_rx_channel                   m_rx;

      ipi(::aura::application * papp,const string & strApp);


      template<typename T,typename... Args>
      var call(const string & strApp,const string & strObject,const string & strMember,const T & t,Args... args)
      {

         var_array va;

         va.add(t,args...);

         return call(strApp,strObject,strMember,va);

      }

      virtual var call(const string & strApp,const string & strObject,const string & strMember,var_array & va);

      small_ipc_tx_channel & tx(const string & strApp);

      virtual string key(const string &strApp);

      string str_from_va(var_array & va);

      virtual void on_call(const string & strObject,const string & strMember,var_array & va);

      virtual void on_receive(small_ipc_rx_channel * prxchannel,const char * pszMessage);

   };


} // namespace aura







