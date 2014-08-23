#pragma once


class CLASS_DECL_AXIS verisimple_exception:
   public call_stack
{
public:

   
   string m_strMessage;


   verisimple_exception(const string& strMessage = "");
   virtual ~verisimple_exception();


};



CLASS_DECL_AXIS ::file::output_stream & operator << (::file::output_stream & dumpcontext,const verisimple_exception & e);