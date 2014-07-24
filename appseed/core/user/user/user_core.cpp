#include "framework.h"


namespace user
{


   core::core(sp(::base::application) papp) :
      element(papp),
      ::base::departament(papp)
   {

   }


   core::~core()
   {

   }

   bool core::initialize()
   {

      if (!::base::departament::initialize())
         return false;

      if (Application.is_system())
      {

         System.factory().cloneable_small < int_biunique >();
         System.factory().creatable_small < edit_plain_text >();
         System.factory().cloneable_small < XfplayerViewLine >();
         System.factory().creatable_small < place_holder >();
         System.factory().creatable_small < place_holder_container >();


         System.factory().cloneable_small < split_layout >();
         System.factory().cloneable_small < split_bar >();
         System.factory().cloneable_small < split_view::Pane >();
         System.factory().cloneable_small < simple_frame_window >();
         System.factory().creatable_small < MetaButton >();
         System.factory().creatable_small < BaseButtonControl >();
         System.factory().creatable_small < menu_list_view >();
         System.factory().cloneable_small < simple_child_frame >();
         System.factory().cloneable_small < simple_main_frame >();
         System.factory().creatable_small < simple_button >();


         System.factory().cloneable_small < ::user::document >();
         System.factory().cloneable_small < split_view >();
         System.factory().cloneable_small < edit_plain_text_view >();

         System.factory().creatable_small < tree >();


         System.factory().creatable_small < simple_list_view >();
         System.factory().creatable_small < simple_document >();
         System.factory().creatable_small < simple_printer_list_view >();
         System.factory().creatable_small < simple_combo_list >();
         System.factory().creatable_small < simple_edit_plain_text >();

         System.factory().creatable_small < simple_edit_plain_text >();

         System.factory().creatable_small < menu_item >(System.type_info < menu_base_item >());
         System.factory().creatable_small < menu >(System.type_info < menu_base >());


         System.factory().creatable_small < SimplePushButton >();

         System.factory().creatable_small < MetaControlBox >();


         // menu
         System.factory().creatable_small < menu_document >();
         System.factory().creatable_small < menu_frame >();
         System.factory().creatable_small < menu_view >();


      }

      return true;

   }


} // namespace user














