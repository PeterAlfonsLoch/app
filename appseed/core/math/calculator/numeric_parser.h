#pragma once

namespace calculator
{

   class CLASS_DECL_CORE parser :
      virtual public ::object
   {
   public:


      scanner           m_scanner;
      spa(::calculator::element)      m_elementa;


      parser(sp(::base::application) papp);
      virtual ~parser();


      ::calculator::element * parse(const char * psz);

      ::calculator::element * expr(::calculator::element * pelement1);
      ::calculator::element * term(::calculator::element * pelement1);
      ::calculator::element * factor();

      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      ::calculator::element *new_node();
      int32_t precedence(token::e_type next, token::e_type current);
      double parse(::calculator::element *current_node);
      double node_traverse(::calculator::element *current_node, double value);
      double apply_traverse_operator(::calculator::element *current_node, double total);
      double apply_operator(::calculator::element *current_node, double total, double m_etype);

      
   };



} // namespace calculator