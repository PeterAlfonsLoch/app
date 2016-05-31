#pragma once


class CLASS_DECL_ACE verisimple_exception:
   public call_stack
{
public:

   
   string m_strMessage;


   verisimple_exception(const string& strMessage = "");
   virtual ~verisimple_exception();


};



CLASS_DECL_ACE ::file::ostream & operator << (::file::ostream & dumpcontext,const verisimple_exception & e);