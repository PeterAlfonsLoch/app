#pragma once

namespace datetime
{

   class CLASS_DECL_ca parser :
      virtual public ::radix::object
   {
   public:

      
      scanner                       m_scanner;
      array_ptr_alloc < element >   m_elementa;


      parser(::ax::application * papp, ::user::str_context * pcontext);
      virtual ~parser();


      element * parse(const char * psz);

      element * expr(element * pelement1);
      element * term(element * pelement1);
      element * factor();


      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      element *new_node();
      int precedence(token::e_type next, token::e_type current);
      double parse(element *current_node);
      double node_traverse(element *current_node, double value);
      double apply_traverse_operator(element *current_node, double total);
      double apply_operator(element *current_node, double total, double m_etype);

      
   };



} // namespace datetime