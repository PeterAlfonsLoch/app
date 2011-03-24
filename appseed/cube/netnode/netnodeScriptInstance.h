#pragma once

class CLASS_DECL_CA2_CUBE netnodeScriptInstance :
   public netnodeScriptImpl
{
public:
   netnodeScriptInstance(netnodeScript * pscript);
   virtual ~netnodeScriptInstance();

   void destroy();

   string m_strDebugRequestUri;
   string m_strDebugThisScript;

};