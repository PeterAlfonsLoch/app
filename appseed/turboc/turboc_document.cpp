#include "framework.h"


namespace turboc
{


   document::document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

   }


   document::~document()
   {

   }


   void document::assert_valid() const
   {

	   ::aura::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

	   ::aura::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::aura::document::on_new_document();

   }


   bool document::on_open_document(var varFile)
   {

      view * pview = get_typed_view < view >();

      if(pview->m_dibImage.load_from_file(varFile))
      {
         get_typed_view < view >()->m_strImage = varFile;
         get_typed_view < view >()->m_strHelloMultiverse = "image:"+ get_typed_view < view >()->m_strImage + ":" + get_typed_view < view >()->m_strHelloMultiverse;
      }
      else if(get_typed_view < edit_view >() != NULL)
      {

         string str = Application.file().as_string(varFile);

         str = str.Left(84);

         get_typed_view < edit_view >()->_001SetText(str,::action::source_user);

      }
      else if(get_typed_view < pane_view >() != NULL)
      {

         get_typed_view < pane_view >()->set_cur_tab_by_id(::turboc::PaneViewHelloMultiverse);
      }

      return true;

   }


   int64_t document::add_ref()
   {

      return  ::aura::document::add_ref();

   }

   int64_t document::dec_ref()
   {

      return  ::aura::document::dec_ref();

   }



} // namespace turboc

















