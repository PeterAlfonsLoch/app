#pragma once




class CLASS_DECL_ca simple_exception : 
   public base_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   bool m_bInitialized;
   bool m_bLoaded;
   char m_szMessage[128];
   UINT m_nResourceID;


   simple_exception();
   simple_exception(const char * pszMessage);
   explicit simple_exception(bool bAutoDelete);
   virtual ~simple_exception();

   virtual bool GetErrorMessage(string & str, PUINT pnHelpContext = NULL);


   void InitString();      // used during ca2 API initialization

};
