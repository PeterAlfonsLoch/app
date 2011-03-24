#pragma once

namespace i2com
{

/*class CLASS_DECL_CA2_CUBE msn_socket :
   public CAsyncSocket
{
public:
   msn_socket(::ca::application * papp);
   virtual ~msn_socket();

   enum e_state
   {
      StateDispatch,
      state_login,
   };

   string m_strRead;
   string m_strServer;

   virtual void OnReceive(int nErrorCode);
   virtual void OnSend(int nErrorCode);
   virtual void OnOutOfBandData(int nErrorCode);
   virtual void OnAccept(int nErrorCode);
   virtual void OnConnect(int nErrorCode);
   virtual void OnClose(int nErrorCode);

   void get(const char * lpcsz, const char * lpcszHeaders);

   void netnodeSend();

   void send_line(const char * pszLine);

   void login(const char * pszUser, const char * pszPassword);
   
   e_state   m_estate;
   string m_strUser; //
   string m_strPassword; // insecure, please in near future change by a Password Manager
};
*/

} // namespace i2com