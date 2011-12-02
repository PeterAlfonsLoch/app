#pragma once

namespace datetime
{

      class CLASS_DECL_ca element
      {
      public:

         element();
         ~element();

         token *     m_ptoken;
         element *   m_pparent;
         element *   m_pelement1;
         element *   m_pelement2;
         element *   m_pelement3;


         value get_value(::ax::application * pcaapp, ::user::str_context * pcontext, int & iPath, int & iPathCount) const;
         string get_expression(::ax::application * pcaapp, ::user::str_context * pcontext, int & iPath, int & iPathCount) const;
         



        
      };



} // namespace calculator