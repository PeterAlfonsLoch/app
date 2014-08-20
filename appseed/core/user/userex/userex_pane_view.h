#pragma once


namespace userex
{


   class CLASS_DECL_CORE pane_view :
      virtual public ::user::impact,
      virtual public ::user::view_creator
   {
   public:

      class menu :
         virtual public element
      {
      public:
         string   m_strMatter;
         id       m_id;
      };


      smart_pointer_array < menu > m_menua;


      pane_view(sp(::axis::application) papp);
      virtual ~pane_view();




      void on_create_view(::user::view_creator_data * pcreatordata);


      void set_new_pane_info(id id, const char * pszMatter);
      void set_menu_info(id id, const char * pszMatter, class id idCommand);
   

      bool on_simple_update(cmd_ui * pcmdui);
      bool on_simple_action(id id);

   };


} // namespace userex


