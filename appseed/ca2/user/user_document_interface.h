#pragma once


namespace user
{


   class document;


   class CLASS_DECL_ca2 document_interface :
      virtual public command_target,
      virtual public ::ca::data_container_base,
      virtual public ::ca::byte_serializable
   {
   public:

      mutex                            m_mutex;
      spa(document)                    m_documentptra;
      string                           m_strTitle;
      string                           m_strPathName;
      sp(document_template)            m_pdocumentemplate;
      spa(::user::view)                m_viewptra;
      bool                             m_bModified;
      bool                             m_bNew;
      bool                             m_bAutoDelete;     // TRUE => delete document when no more views
      bool                             m_bEmbedded;       // TRUE => document is being created by OLE


      document_interface();
      virtual ~document_interface() = 0;



      virtual void update_title();

      virtual void on_alloc(sp(::ca::application) papp);

      const string & get_title() const;
      virtual void set_title(const char * lpszTitle);
      const string & get_path_name() const;
      virtual void set_path_name(var varFile, bool bAddToMRU = TRUE);

      sp(document_template) get_document_template() const;
      virtual bool is_modified();
      virtual void set_modified_flag(bool bModified = TRUE);
      virtual void set_new(bool bNew = true);

      virtual bool is_new_document();

   // Operations
      void add_view(sp(::user::view) pview);
      void remove_view(sp(::user::view) pview);
      virtual ::count get_view_count() const;
      virtual sp(::user::view) get_view(index index = 0) const;


      template < class T >
      T * get_typed_view_count() const
      {
         ::count count = 0;
         for(index index = 0; index < m_viewptra.get_count(); index++)
         {
            T * pt = dynamic_cast < T * > (m_viewptra[index]);
            if(pt != NULL)
               count++;
         }
         return count;
      }

      template < class T >
      T * get_typed_view(index indexFind = 0) const
      {
         if(indexFind < 0 || indexFind >= m_viewptra.get_count())
            return NULL;
         ::count count = 0;
         for(index index = 0; index < m_viewptra.get_count(); index++)
         {
            T * pt = dynamic_cast < T * > (m_viewptra(index).m_p);
            if(pt != NULL)
            {
               if(indexFind == count)
                  return pt;
               else
                  count++;
            }
         }
         return NULL;
      }

      virtual sp(::user::view) get_typed_view(sp(::ca::type_info) info, index indexFind = 0);

      virtual void show_all_frames(UINT nCmdShow);


      class update
      {
      public:
         sp(::user::view)         m_pSender;
         LPARAM         m_lHint;
         ::ca::object *  m_pHint;
      };

      // Update Views (simple update - DAG only)
      void update_all_views(sp(::user::view) pSender, LPARAM lHint = 0L,
         ::ca::object* pHint = NULL);

      void send_update(sp(::user::view) pSender, LPARAM lHint = 0L,
         ::ca::object* pHint = NULL);

   // Overridables
      // Special notifications
      virtual void on_changed_view_list(single_lock * psl = NULL); // after add or remove ::user::view
      virtual void delete_contents(); // delete doc items etc

      // File helpers
      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(var varFile);
      virtual void on_close_document(single_lock * psl = NULL);
      virtual void report_save_load_exception(const char * lpszPathName, base_exception* e, bool bSaving, const char * nIDPDefault);

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

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      friend class document_template;

      virtual void write(::ca::byte_output_stream & ostream);
      virtual void read(::ca::byte_input_stream & istream);


   protected:
      void on_file_close();
      void on_file_save();
      void on_file_save_as();
      void on_file_send_mail();
      void on_update_file_send_mail(cmd_ui* pCmdUI);



   };


} // namespace user

