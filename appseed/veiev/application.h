#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV application :
      public ::tesseract::application
   {
   public:


      ::veiev::list *                           m_pveievlist;
      ::veiev::second_command_view *            m_pmainview;
      ::veiev::right_pane_view *                m_prightpaneview;
      ::veiev::right_view *                     m_prightview;
      ::veiev::tree *                           m_pveievtree;
      ::userbase::single_document_template *    m_ptemplate_html;
      ::userbase::single_document_template *    m_ptemplateVeiev;



      application(void);
      virtual ~application(void);

      bool initialize_instance();


      virtual void on_request(::ca::create_context * pcreatecontext);

   };

} // namespace veiev