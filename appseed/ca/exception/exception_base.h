#pragma once


#undef delete


class string;


class CLASS_DECL_ca base_exception :
   virtual public ::ca::exception,
   virtual public call_stack
{
public:


   base_exception(::ca::application * papp, uint32_t uiSkip = 4 /* -1 for disable call stack*/);   // sets m_bAutoDelete = TRUE
   explicit base_exception(::ca::application * papp, bool bAutoDelete, uint32_t uiSkip = 4 /* -1 for disable call stack*/);   // sets m_bAutoDelete = bAutoDelete
   // Implementation (setting m_bAutoDelete to FALSE is advanced)
   virtual ~base_exception();


   void Delete();  // use to delete exception in 'catch' block


   virtual bool get_error_message(string & str, PUINT pnHelpContext = ::null());
   virtual string get_message(PUINT pnHelpContext = ::null());


   virtual int32_t ReportError(UINT nType = MB_OK, const char * pszMessageID = ::null());


   void operator delete(void * pbData);
   void operator delete(void * pbData, const char * lpszFileName, int32_t nLine);


};





