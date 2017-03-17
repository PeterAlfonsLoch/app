#pragma once


namespace ftp
{


   class CLASS_DECL_AURA output : 
      virtual public client_socket::notification
   {
   public:


      output(::aura::application * papp);
      virtual ~output();
      
      virtual void OnInternalError(const string& strErrorMsg, const string& strFileName, DWORD dwLineNr);
      virtual void OnSendCommand(const command& strComamnd, const stringa& straArguments);
      virtual void OnResponse(const reply & Reply);

      virtual void WriteLine(const string & cszLine, const string & strStatus);

   };



} //  namespace ftp

