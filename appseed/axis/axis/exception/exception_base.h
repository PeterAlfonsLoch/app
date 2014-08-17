#pragma once


#undef delete


class string;

namespace exception
{

   class CLASS_DECL_AXIS base :
      virtual public ::exception::exception,
      virtual public call_stack
   {
   public:


      base(sp(::axis::application) papp,uint32_t uiSkip = 4 /* -1 for disable call stack*/);   // sets m_bAutoDelete = TRUE
      explicit base(sp(::axis::application) papp,bool bAutoDelete,uint32_t uiSkip = 4 /* -1 for disable call stack*/);   // sets m_bAutoDelete = bAutoDelete
      // Implementation (setting m_bAutoDelete to FALSE is advanced)
      virtual ~base();


      void Delete();  // use to delete exception in 'catch' block


      virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);
      virtual string get_message(PUINT pnHelpContext = NULL);


      virtual int32_t ReportError(UINT nType = MB_OK, const char * pszMessageID = NULL);


      void operator delete(void * pbData);
      void operator delete(void * pbData, const char * lpszFileName, int32_t nLine);

      virtual const char * getMessage() const throw();

   };





} // namespace exception



