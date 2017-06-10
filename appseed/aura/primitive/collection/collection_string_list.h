#pragma once


class CLASS_DECL_AURA string_list :
   virtual public list < string >
{
public:


   string_list();
   virtual ~string_list();

   
   POSITION find(string searchValue, POSITION startAfter = NULL) const;


   void dump(dump_context &) const;
   void assert_valid() const;


};


