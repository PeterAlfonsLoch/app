#pragma once


class CLASS_DECL_AURA verisimple_exception:
   public call_stack
{
public:

   
   string m_strMessage;


   verisimple_exception(const string& strMessage = "");
   virtual ~verisimple_exception();


};



CLASS_DECL_AURA ::file::output_stream & operator << (::file::output_stream & dumpcontext,const verisimple_exception & e);