#pragma once


namespace filemanager
{


   class operation:
      virtual public ::object
   {
   public:


      e_operation                m_eoperation;
      ::file::listing            m_stra;
      double_array               m_daRead;
      double_array               m_daSize;
      ::file::path               m_str;
      ::file::path               m_strBase;
      double                     m_dSize;
      double                     m_dRead;
      ::file::buffer_sp          m_fileSrc;
      ::file::buffer_sp          m_fileDst;
      int32_t                    m_iFile;
      bool                       m_bReplaceAll;
      char *                     m_pchBuffer;
      int32_t                    m_iBufferSize;
      sp(::user::interaction)    m_oswindowCallback;
      UINT                       m_uiCallbackMessage;
      WPARAM                     m_wparamCallback;


      operation(::aura::application * papp);
      virtual ~operation();
      
      virtual bool set_copy(::file::listing & stra,const ::file::path & pszDestBase,const ::file::path & pszSrcBase,bool bExpand);
      virtual bool set_move(::file::listing & stra,const ::file::path & psz);
      virtual bool set_delete(::file::listing & stra);

      //   virtual double size();
      //   virtual double progress();

      int32_t get_item_count();
      string get_item_message(int32_t iItem);
      double get_item_progress(int32_t iItem);
      double get_item_read(int32_t iItem);
      double get_item_size(int32_t iItem);

      void expand(::file::listing & straExpanded,::file::patha & straExpand);

      virtual bool start();
      virtual bool step();
      //   virtual bool mark();
      virtual bool finish();
      virtual bool make_duplicate_name(::file::path & str,const ::file::path & psz);


      virtual bool initialize();
      virtual bool open_src_dst(const ::file::path & pszSrc,::file::path & strDst,const ::file::path & pszDir);

      virtual void set_operation(e_operation eoperation);
      virtual e_operation get_operation();

   };


} // namespace filemanager














