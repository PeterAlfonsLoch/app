#pragma once


namespace user
{




   class CLASS_DECL_AXIS view_creator :
      virtual public view_container
   {
   public:


      class CLASS_DECL_AXIS create_exception
      {
      public:


         id       m_id;


         create_exception(id id) : m_id(id) {}


      };


      class CLASS_DECL_AXIS view_map :
         public map < id, id, ::user::view_creator_data *, ::user::view_creator_data * >
      {
      public:
      };


      view_map                      m_viewmap;
      class view_container *        m_pviewcontainer;


      view_creator();
      virtual ~view_creator();


      virtual ::count get_view_count();

      virtual void on_new_view_creator_data(::user::view_creator_data * pcreatordata);
      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_show_view();

      virtual void on_update(sp(::user::document) pdocument, sp(::user::impact) pSender, LPARAM lHint, object* pHint);

      virtual ::user::interaction * get_view();

      virtual id get_view_id();

      virtual ::user::view_creator_data * get(id id);

      virtual ::user::view_creator_data * allocate(id id);

      using ::request_interface::create;
      virtual ::user::view_creator_data * create_impact(id id,LPCRECT lpcrectCreate);

      virtual ::user::view_creator_data * ensure_impact(id id, LPCRECT lpcrectCreate);

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


