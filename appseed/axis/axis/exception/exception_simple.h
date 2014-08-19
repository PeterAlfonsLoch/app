#pragma once




class CLASS_DECL_AXIS simple_exception : 
   virtual public ::exception::base
{
public:
   
   simple_exception(sp(::axis::application) papp);
   simple_exception(sp(::axis::application) papp, const char * pszMessage);
   virtual ~simple_exception();


   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


class CLASS_DECL_AXIS verisimple_exception :
   public call_stack
{
public:

   string m_strMessage;

   verisimple_exception(const string& strMessage = "");
   virtual ~verisimple_exception();

   


};