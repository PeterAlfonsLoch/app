#pragma once

namespace userex
{

   class CLASS_DECL_ca pane_view :
      virtual public ::userbase::view,
      virtual public ::user::create_view
   {
   public:

      class menu
      {
      public:
         string   m_strMatter;
         id       m_id;
      };


      array_ptr_alloc < menu, menu & > m_menua;


      pane_view(::ca::application * papp);
      virtual ~pane_view();




      void on_create_view(view_data * pviewdata);


      void set_new_pane_info(id id, const char * pszMatter);
      void set_menu_info(id id, const char * pszMatter, class id idCommand);
   

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);

      
   };

} // namespace userex