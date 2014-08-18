#pragma once


namespace user
{


   class CLASS_DECL_AXIS document :
      virtual public command_target,
      virtual public ::data::data_container_base,
      virtual public ::file::serializable,
      virtual public ::user::server,
      virtual public ::database::client
   {
   public:


      mutex                            m_mutex;
      spa(document)                    m_documentptra;
      string                           m_strTitle;
      string                           m_strPathName;
      sp(impact_system)                m_pdocumentemplate;
      spa(::user::impact)              m_viewptra;
      bool                             m_bModified;
      bool                             m_bNew;
      bool                             m_bAutoDelete;     // TRUE => delete document when no more views
      bool                             m_bEmbedded;       // TRUE => document is being created by OLE
      document_data_map                m_datamap;


      document(sp(::base::application) papp);
      virtual ~document();




      virtual void update_title();

      virtual void on_create(sp(::create_context) pcreatecontext);

      const string & get_title() const;
      virtual void set_title(const char * lpszTitle);
      const string & get_path_name() const;
      virtual void set_path_name(var varFile, bool bAddToMRU = TRUE);

      sp(impact_system) get_document_template() const;
      virtual bool is_modified();
      virtual void set_modified_flag(bool bModified = TRUE);
      virtual void set_new(bool bNew = true);

      virtual bool is_new_document();

      // Operations
      void add_view(sp(::user::impact) pview);
      void remove_view(sp(::user::impact) pview);
      virtual ::count get_view_count() const;
      virtual sp(::user::impact) get_view(index index = 0) const;


      template < class T >
      T * get_typed_view_count() const
      {
         ::count count = 0;
         for (index index = 0; index < m_viewptra.get_count(); index++)
         {
            T * pt = dynamic_cast <T *> (m_viewptra[index]);
            if (pt != NULL)
               count++;
         }
         return count;
      }

      template < class T >
      T * get_typed_view(index indexFind = 0) const
      {
         if (indexFind < 0 || indexFind >= m_viewptra.get_count())
            return NULL;
         ::count count = 0;
         for (index index = 0; index < m_viewptra.get_count(); index++)
         {
            T * pt = dynamic_cast <T *> (m_viewptra(index).m_p);
            if (pt != NULL)
            {
               if (indexFind == count)
                  return pt;
               else
                  count++;
            }
         }
         return NULL;
      }

      virtual sp(::user::impact) get_typed_view(sp(type) info, index indexFind = 0);

      virtual void show_all_frames(UINT nCmdShow);


      class update
      {
      public:
         sp(::user::impact)         m_pSender;
         LPARAM         m_lHint;
         ::object *  m_pHint;
      };

      // Update Views (simple update - DAG only)
      void update_all_views(sp(::user::impact) pSender, LPARAM lHint = 0L,
         ::object* pHint = NULL);

      void send_update(sp(::user::impact) pSender, LPARAM lHint = 0L,
         ::object* pHint = NULL);

      // Overridables
      // Special notifications
      virtual void on_changed_view_list(single_lock * psl = NULL); // after add or remove ::user::impact
      virtual void delete_contents(); // delete doc items etc

      // File helpers
      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(var varFile);
      virtual void on_close_document(single_lock * psl = NULL);
      virtual void report_save_load_exception(const char * lpszPathName, ::exception::base* e, bool bSaving, const char * nIDPDefault);

      // advanced overridables, closing down frame/doc, etc.
      virtual bool can_close_frame(sp(::user::frame_window) pFrame);
      virtual bool save_modified(); // return TRUE if ok to continue
      virtual void pre_close_frame(sp(::user::frame_window) pFrame);


      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      // implementation helpers
      virtual bool do_save(var varFile, bool bReplace = true);
      virtual bool do_file_save();
      virtual void update_frame_counts(single_lock * psl = NULL);
      virtual void disconnect_views();
      virtual void send_initial_update();

      // overridables for implementation
      virtual HMENU GetDefaultMenu(); // get menu depending on state
      virtual HACCEL GetDefaultAccelerator();
      virtual void on_idle();
      virtual void on_final_release();

      virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);

      friend class impact_system;

      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & istream);


      void on_file_close();
      void on_file_save();
      void on_file_save_as();
      void on_file_send_mail();
      void on_update_file_send_mail(cmd_ui* pCmdUI);









//      virtual void on_alloc(sp(::base::application) papp);

//      virtual void dump(dump_context &) const;
  //    virtual void assert_valid() const;

//      virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);

      template < class DOCUMENT >
      DOCUMENT * get_typed_document()
      {
         ASSERT(this != NULL);
         return dynamic_cast < DOCUMENT * >(this);
      }

      template < class DATA >
      DATA * get_typed_data()
      {
         ASSERT(this != NULL);
         return m_spadata.get < DATA >();
      }

      template < class DOCUMENT >
      ::data::data * get_typed_document_data()
      {
         ASSERT(this != NULL);
         return get_data(get_typed_document < DOCUMENT > ());
      }

      template < class DOCUMENT >
      ::data::data * get_data(DOCUMENT * pthis)
      {
         ASSERT(this == pthis);
         if (this != pthis)
            return NULL;
         return m_datamap[pthis];
      }

      template < class DOCUMENT >
      void set_typed_document_data(::data::data * pdata)
      {
         ASSERT(this != NULL);
         set_data(get_typed_document < DOCUMENT >(), pdata);
      }

      template < class DOCUMENT >
      void set_data(DOCUMENT * pthis, ::data::data * pdata)
      {
         ASSERT(this == pthis);
         if (this != pthis)
            return;
         m_spadata.remove_type(pdata);
         m_datamap[pthis] = pdata;
         m_spadata.add(pdata);
      }

   };


} // namespace user




