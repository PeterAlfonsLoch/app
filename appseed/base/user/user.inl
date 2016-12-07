#pragma once



namespace user
{


   template < class VIEW >
   inline VIEW * impact::create_view(::user::document * pdoc,const RECT & rect, ::user::interaction * pwndParent,id id, ::user::interaction * pviewLast)
   {
      return dynamic_cast < VIEW * > (create_view(System.type_info < VIEW >(), pdoc, rect, pwndParent, id, pviewLast));
   }


   template < class VIEW >
   inline VIEW * impact::create_view(const RECT & rect,::user::interaction * pwndParent,id id,::user::interaction * pviewLast)
   {

      return dynamic_cast < VIEW * > (create_view < VIEW >(get_document(),rect,pwndParent,id,pviewLast));

   }


   template < class VIEW >
   inline VIEW * impact::create_view(::user::view_creator_data * pcreatordata, ::user::interaction * pviewLast)
   {

      VIEW * pview = create_view < VIEW >(get_document(), pcreatordata->m_rectCreate, pcreatordata->m_pholder, pcreatordata->m_id, pviewLast);

      return pview;

   }


   template < class DATA >
   DATA * impact::get_typed_data()
   {
      ASSERT(this != NULL);
      return m_pdocument->get_typed_data < DATA >();
   }

   template < class DOCUMENT >
   ::data::data * impact::get_typed_document_data()
   {
      ASSERT(this != NULL);
      return m_pdocument->get_typed_document_data < DOCUMENT >();
   }

   template < class DOCUMENT >
   DOCUMENT * impact::get_typed_document()
   {
      ASSERT(this != NULL);
      return m_pdocument->get_typed_document < DOCUMENT >();
   }


   template < typename T >
   inline void interaction::redraw_add(T * p)
   {

      get_wnd()->m_pimpl->redraw_add(dynamic_cast < ::object * > (p));

   }

   template < typename T >
   inline void interaction::redraw_remove(T * p)
   {

      get_wnd()->m_pimpl->redraw_remove(dynamic_cast < ::object * > (p));

   }

   inline bool interaction::has_redraw()
   {

      return get_wnd()->m_pimpl->has_redraw();

   }

} //   namespace aura














