#pragma once


namespace datetime
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



   class CLASS_DECL_ca2 scanner
   {
   public:
      
      
      const char *            input;
      const char *            next_input;

      class token *           m_ptoken;
      ::user::str_context *   m_pstrcontext;


      scanner(::user::str_context * pstrcontext);
      ~scanner();

      void initialize(const char * psz);
      void peek();
      void next();
      token * look_ahead();

   };


} // namespace calculator