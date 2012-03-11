#pragma once


namespace html
{


   class CLASS_DECL_ca2 data :
      virtual public gen::signalizable,
      public ca::data
   {
   public:


      class CLASS_DECL_ca2 image :
         virtual public ::radix::object
      {
      public:
         index      m_iIndex;
         string   m_strPath;
         ::visual::dib_sp      m_spdib;

         image(::ca::application * papp);
         virtual bool load_image();
      };


      class CLASS_DECL_ca2 load_image
      {
      public: 
         image * m_pimage;
         data * m_pdocument;
      };


      class CLASS_DECL_ca2 layout_state
      {
      public:
         int   m_iBody;
         int   m_y;
         int   m_cy;
         int   m_x;
         int   m_cx;
         bool  m_bLastBlockX;
         bool  m_bLastBlockY;
         bool  m_bHasChar;
         //base_array < impl::table *, impl::table *> m_tableptraStack;
         //base_array < impl::table_row *, impl::table_row *> m_tablerowptraStack;
         void reset();
      };

      ::user::form_callback *    m_pcallback;
      ::user::interaction *      m_pguie;
      ::ca::graphics *           m_pdc;
      rect                       m_rect;
      string                     m_strTitle;
      layout_state               m_layoutstate;
      
      base_array < impl::table *, impl::table * > 
                                 m_tableptra;

      array_app_alloc < image, image & > 
                                 m_imagea;

      array_ptr_alloc < font, font >  
                                 m_fonta;

      comparable_array < ::user::interaction *, ::user::interaction * >   
                                 m_focusptra;
      
      style_sheet_array          m_stylesheeta;
      string                     m_strPathName;
      user::LPWndArray           m_uiptra;
      tag *                      m_ptag;
      elemental                  m_elemental;
      bool                       m_bImplemented;


      bool                       m_bImplement;
      bool                       m_bLayout;

      
      http::cookies *            m_pcookies;
      ::fontopus::user *         m_puser;
      string                     m_strUser;
      string                     m_strPassword;
      string                     m_strLicense;

      gen::property_set          m_propertyset;
      gen::property_set          m_propset;
      string                     m_strSource;

      ::user::form *             m_pform;
      bool                       m_bEdit;
      elemental *                m_pElementalSelStart;
      elemental *                m_pElementalSelEnd;



      data(::ca::application * papp);
      virtual ~data();

      virtual bool open_document(var varFile);
      virtual bool open_link(const char * pszPath);

      virtual void OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

      virtual ::user::form * get_form();
      virtual ::user::interaction* get_frame();


      //virtual bool is_in_use();
   
      void load(const char *);
      void implement(::ca::graphics * pdc);
      void layout(::ca::graphics * pdc);
      void _001OnDraw(::ca::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnKeyDown)

      int get_image_index(const char * pszUrl);
      void load_image_asynch(image * pimage);
      static UINT AFX_CDECL LoadImageProc(LPVOID lpParam);
      bool load_image(image * pimage);

      void on_image_loaded(image * pimage);


      elemental * get_element_by_name(id id);
      elemental * get_element_by_id(id id);

      void delete_contents();
      void delete_implementation();

      virtual bool contains(::user::interaction * pui);

      virtual bool on_create_interaction(::user::interaction * pui);


      font * get_font(elemental * pelemental);

   protected:


      int create_font(elemental * pelemental);


   private:


      data(const data & ) :
         ::ca::data(NULL),
         m_elemental(NULL)
      {
      }


   };


} // namespace html



