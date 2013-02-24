#pragma once


namespace calculator
{




#define INITIALIZE_TABLE(table, function) if(table[0] == 0) function(table)

/*
var:
a(ad)*
a = a-z, A-Z, _
d = 0-9
operators:
+ -
* /
=
numbers:
0-9
*/


   class CLASS_DECL_ca scanner :
      virtual public ::ca::object
   {
   public:
      
      
      const char * input;
      const char * next_input;
      class token * m_ptoken;


      scanner(::ca::application * papp);
      virtual ~scanner();

      

      void initialize(const char * psz);
      void peek();
      void next();
      token * look_ahead();

   };



} // namespace calculator