#pragma once


namespace veriview
{
   class address_view;
   class pane_view;

   class CLASS_DECL_CA2_CUBE main_document : public ::userbase::document
   {
   public:
      main_document(::ca::application * papp);
      virtual ~main_document();

      address_view *       m_paddressview;
      pane_view *     m_ppaneview;

      string get_url();

      bool on_open_document(var varFile);
   };

} // namespace html