#pragma once


namespace datetime
{


   class CLASS_DECL_ca2 element :
      virtual public ::element
   {
   public:

      element();
      ~element();

      token *     m_ptoken;
      element *   m_pparent;
      element *   m_pelement1;
      element *   m_pelement2;
      element *   m_pelement3;


      value get_value(sp(base_application) pcaapp, ::user::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const;
      string get_expression(sp(base_application) pcaapp, ::user::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const;
         



        
   };


} // namespace calculator



