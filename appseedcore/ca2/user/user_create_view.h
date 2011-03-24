#pragma once

namespace user
{

   class CLASS_DECL_ca create_view :
      virtual public ::radix::object
   {
   public:
      class CLASS_DECL_ca view_data
      {
      public:
         view_data();

         enum eflag
         {
            flag_hide_all_others_on_show,
         };

         id                         m_id;
         ::user::interaction *      m_pwnd;
         document *                 m_pdoc;
         id                         m_idSplit;
         bool                       m_bTabSplitSwap;
         int                        m_iExtendOnParent;
         flags < eflag >            m_eflag;
         string                     m_strTitle;
      };

      class CLASS_DECL_ca view_map :
         public ::collection::map < id, id, view_data *, view_data * >
      {
      public:
      };

      int get_view_count();
      view_map m_viewmap;
      

      virtual void on_create_view(view_data * pviewdata);
      virtual void on_show_view();

      virtual ::user::interaction * get_view_uie();

      virtual id get_view_id();

      virtual view_data * get(id id);

      virtual view_data * create(id id);

      virtual view_data * ensure(id id);

      virtual void hide_all_except(id id);

      class get_view * m_pgetview;
   };

} // namespace user