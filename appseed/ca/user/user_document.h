#pragma once


class CLASS_DECL_ca document :
   public user::document_interface
{
public:


   document(::ca::application * papp);


   virtual void on_alloc(::ca::application * papp);

   const string & get_title() const;
   virtual void set_title(const char * lpszTitle);
   const string & get_path_name() const;
   virtual void set_path_name(var varFile, BOOL bAddToMRU = TRUE);

   document_template * get_document_template() const;
   virtual BOOL is_modified();
   virtual void set_modified_flag(BOOL bModified = TRUE);
   virtual void set_new(bool bNew = true);

   virtual bool is_new_document();

// Operations
   void add_view(::view * pview);
   void remove_view(::view * pview);
   virtual count get_view_count() const;
   virtual ::view * get_view(index index = 0) const;


   template < class T >
   T * get_typed_view_count() const
   {
      count count = 0;
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
      count count = 0;
      for(index index = 0; index < m_viewptra.get_count(); index++)
      {
         T * pt = dynamic_cast < T * > (m_viewptra[index]);
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

   virtual ::view * get_view(const ::ca::type_info info, index indexFind = 0);

   virtual void show_all_frames(UINT nCmdShow);


   class update
   {
   public:
      ::view *         m_pSender;
      LPARAM         m_lHint;
      ::radix::object *  m_pHint;
   };

   // Update Views (simple update - DAG only)
   void update_all_views(::view * pSender, LPARAM lHint = 0L,
      ::radix::object* pHint = NULL);

   void send_update(::view * pSender, LPARAM lHint = 0L,
      ::radix::object* pHint = NULL);

// Overridables
   // Special notifications
   virtual void on_changed_view_list(); // after add or remove ::view
   virtual void delete_contents(); // delete doc items etc

   // File helpers
   virtual BOOL on_new_document();
   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);
   virtual void on_close_document();
   virtual void report_save_load_exception(const char * lpszPathName, base_exception* e, BOOL bSaving, const char * nIDPDefault);

   // advanced overridables, closing down frame/doc, etc.
   virtual BOOL can_close_frame(frame_window* pFrame);
   virtual BOOL save_modified(); // return TRUE if ok to continue
   virtual void pre_close_frame(frame_window* pFrame);

protected:
   string               m_strTitle;
   string               m_strPathName;
   document_template *    m_pdocumentemplate;
   comparable_array < ::view * > m_viewptra;
   BOOL                 m_bModified;
   bool                 m_bNew;

public:
   BOOL m_bAutoDelete;     // TRUE => delete document when no more views
   BOOL m_bEmbedded;       // TRUE => document is being created by OLE

#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif //_DEBUG
   virtual ~document() = 0;

   // implementation helpers
   virtual bool do_save(const char * pszPathName, bool bReplace = true);
   virtual bool do_file_save();
   virtual void update_frame_counts();
   virtual void disconnect_views();
   virtual void send_initial_update();

   // overridables for implementation
   virtual HMENU GetDefaultMenu(); // get menu depending on state
   virtual HACCEL GetDefaultAccelerator();
   virtual void on_idle();
   virtual void on_final_release();

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

   friend class document_template;

   virtual void write(ex1::byte_output_stream & ostream);
   virtual void read(ex1::byte_input_stream & istream);


protected:
   void on_file_close();
   void on_file_save();
   void on_file_save_as();
   void on_file_send_mail();
   void on_update_file_send_mail(cmd_ui* pCmdUI);
};


