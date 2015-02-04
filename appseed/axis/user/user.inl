#pragma once



namespace aura
{


   template < class VIEW >
   inline VIEW * impact::create_view(::aura::document * pdoc,const RECT & rect, ::user::interaction * pwndParent,id id, ::user::interaction * pviewLast)
   {
      return dynamic_cast < VIEW * > (create_view(System.type_info < VIEW >(), pdoc, rect, pwndParent, id, pviewLast));
   }


   template < class VIEW >
   inline VIEW * impact::create_view(const RECT & rect,::user::interaction * pwndParent,id id,::user::interaction * pviewLast)
   {

      return dynamic_cast < VIEW * > (create_view < VIEW >(NULL,rect,pwndParent,id,pviewLast));

   }


   template < class VIEW >
   inline VIEW * impact::create_view(::user::view_creator_data * pcreatordata, ::user::interaction * pviewLast)
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


} //   namespace aura











#ifdef WINDOWSEX


namespace base
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_AXIS system_interaction_impl:
      virtual public ::user::interaction
   {
   public:

      system_interaction_impl(::aura::application * papp);

      void install_message_handling(::message::dispatch * pdispath);

      DECL_GEN_SIGNAL(_001MessageHub);


   };


} // namespace base



#endif




#endif // __cplusplus




