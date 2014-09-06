#pragma once



namespace user
{


   template < class VIEW >
   inline sp(VIEW) impact::create_view(::user::document * pdoc,const RECT & rect, sp(::user::interaction) pwndParent,id id,sp(::user::interaction) pviewLast)
   {
      return create_view(System.type_info < VIEW >(), pdoc, rect, pwndParent, id, pviewLast);
   }


   template < class VIEW >
   inline sp(VIEW) impact::create_view(const RECT & rect,::user::interaction * pwndParent,id id,sp(::user::interaction) pviewLast)
   {

      return create_view < VIEW >(NULL, rect, pwndParent, id, pviewLast);

   }


   template < class VIEW >
   inline sp(VIEW) impact::create_view(::user::view_creator_data * pcreatordata, sp(::user::interaction) pviewLast)
   {

      VIEW * pview = create_view < VIEW >(pcreatordata->m_rectCreate, pcreatordata->m_pholder, pcreatordata->m_id, pviewLast);

      if (pview != NULL)
      {

         pcreatordata->m_pdoc = get_document();

      }

      return pview;

   }


   template < class DATA >
   DATA * impact::get_typed_data()
   {
      ASSERT(this != NULL);
      return m_spdocument->get_typed_data < DATA >();
   }

   template < class DOCUMENT >
   ::data::data * impact::get_typed_document_data()
   {
      ASSERT(this != NULL);
      return m_spdocument->get_typed_document_data < DOCUMENT >();
   }

   template < class DOCUMENT >
   DOCUMENT * impact::get_typed_document()
   {
      ASSERT(this != NULL);
      return m_spdocument->get_typed_document < DOCUMENT >();
   }


} //   namespace user




