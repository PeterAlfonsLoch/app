#pragma once


namespace user
{


   class place_holder;


   class CLASS_DECL_ca view_creator_data
   {
   public:


      enum eflag
      {
         flag_hide_all_others_on_show,
      };


      id                               m_id;
      ::user::interaction *            m_pwnd;
      ::user::place_holder *           m_pholder;
      ::user::document_interface *     m_pdoc;
      id                               m_idSplit;
      bool                             m_bTabSplitSwap;
      int                              m_iExtendOnParent;
      flags < eflag >                  m_eflag;
      string                           m_strTitle;
      void *                           m_pviewdata;


      view_creator_data();


   };



   class CLASS_DECL_ca view_creator :
      virtual public view_container
   {
   public:




      class CLASS_DECL_ca view_map :
         public ::collection::map < id, id, ::user::view_creator_data *, ::user::view_creator_data * >
      {
      public:
      };


      view_map                      m_viewmap;
      class view_container *        m_pviewcontainer;


      view_creator();
      virtual ~view_creator();


      virtual count get_view_count();

      virtual void on_new_view_creator_data(::user::view_creator_data * pcreatordata);
      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_show_view();

      virtual void on_update(::document * pdocument, ::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual ::user::interaction * get_view();

      virtual id get_view_id();

      virtual ::user::view_creator_data * get(id id);

      virtual ::user::view_creator_data * allocate(id id);

      using ::ex1::request_interface::create;
      virtual ::user::view_creator_data * create(id id);

      virtual ::user::view_creator_data * ensure(id id);

      virtual void hide_all_except(id id);

      template < class T > T *
      get_typed_document()
      {
         T * pdoc;
         ::user::view_creator_data * pcreatordata;
         id key;
         POSITION pos = m_viewmap.get_start_position();
         while(pos != NULL)
         {
            m_viewmap.get_next_assoc(pos, key, pcreatordata);
            if(pcreatordata->m_pdoc != NULL)
            {
               pdoc = dynamic_cast < T * > (pcreatordata->m_pdoc);
               if(pdoc != NULL)
               {
                  return pdoc;
               }
            }
         }
         return NULL;
      }


   };


} // namespace user


