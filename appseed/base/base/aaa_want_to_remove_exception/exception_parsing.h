#pragma once


class CLASS_DECL_BASE parsing_exception:
   virtual public simple_exception
{
public:


   parsing_exception(sp(::axis::application) papp,const string & strMessage);
   virtual ~parsing_exception();


};


CLASS_DECL_BASE bool get_avoid_parsing_exception();
CLASS_DECL_BASE bool throw_parsing_exception(const string & strMessage);


class CLASS_DECL_BASE avoid_parsing_exception
{
public:

   int_ptr m_iBefore;

   avoid_parsing_exception();
   virtual ~avoid_parsing_exception();

};