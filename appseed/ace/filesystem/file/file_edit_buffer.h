#pragma once


namespace file
{


   class CLASS_DECL_ACE edit_buffer:
      public ::file::buffer_sp,
      public ::data::tree
   {
   public:


      enum EItemType
      {
         ItemTypeUndefined,
         ItemTypeDelete,
         ItemTypeEdit,
         ItemTypeInsert,
         ItemTypeGroup
      };

      class Item:
         public ::data::item
      {
      public:

         file_position_t m_dwPosition;


         Item();

         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual file_position_t get_position(bool bForward);

         virtual BYTE * get_data() ;
         virtual EItemType get_type();
         virtual memory_size_t get_extent();
         virtual memory_size_t get_file_extent();
         virtual BYTE * reverse_get_data();
         virtual EItemType reverse_get_type();
         virtual memory_size_t reverse_get_extent() ;
         virtual memory_size_t reverse_get_file_extent() ;
         virtual memory_size_t get_extent(bool bForward);
         virtual EItemType get_type(bool bForward);
         virtual memory_size_t get_file_extent(bool bForward);
         virtual BYTE * get_data(bool bForward);
         virtual memory_offset_t get_delta_length() ;

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new ACE_NEW


      };

      class DeleteItem: public Item
      {
      public:


         memory m_memstorage;


         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual EItemType get_type();
         virtual memory_size_t get_extent() ;
         virtual memory_size_t get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type() ;
         virtual memory_size_t reverse_get_extent();
         virtual memory_size_t reverse_get_file_extent();
         virtual BYTE * reverse_get_data();

         virtual memory_offset_t get_delta_length() ;
      };

      class InsertItem: public Item
      {
      public:


         memory m_memstorage;


         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual EItemType get_type() ;
         virtual memory_size_t get_extent() ;
         virtual memory_size_t get_file_extent() ;
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type() ;
         virtual memory_size_t reverse_get_extent() ;
         virtual memory_size_t reverse_get_file_extent() ;
         virtual BYTE * reverse_get_data();
         virtual memory_offset_t get_delta_length();

      };

      class EditItem: public Item
      {
      public:


         memory m_memstorage;
         memory m_memstorageReverse;


         virtual EItemType get_type();
         virtual memory_size_t get_extent() ;
         virtual memory_size_t get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type();
         virtual memory_size_t reverse_get_extent() ;
         virtual memory_size_t reverse_get_file_extent();
         virtual BYTE * reverse_get_data() ;
         virtual memory_offset_t get_delta_length();

      };

      class ItemPtrArray: public spa(Item)
      {
      public:
      };

      class GroupItem: public Item,public ItemPtrArray
      {
      public:


         GroupItem * m_pgroupitem;


         virtual EItemType get_type();
         virtual memory_size_t get_extent();
         virtual memory_size_t get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type();
         virtual memory_size_t reverse_get_extent() ;
         virtual memory_size_t reverse_get_file_extent();
         virtual BYTE * reverse_get_data() ;
         virtual memory_offset_t get_delta_length();

         virtual UINT read_ch(::file::edit_buffer * pfile);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new ACE_NEW

      };

      file_position_t           m_dwPosition;
      file_size_t               m_dwInternalFilePosition;
      file_size_t               m_dwFileLength;
      file_position_t           m_dwReadPosition;
      file_offset_t             m_iCurItem;


      sp(::data::tree_item)   m_ptreeitem;
      sp(::data::tree_item)   m_ptreeitemFlush;
      memory_offset_t              m_iBranch;
      ::file::buffer_sp           m_pfile;
      sp(GroupItem)          m_pgroupitem;
      bool                 m_bRootDirection;

      edit_buffer(::ace::application * papp);
      virtual ~edit_buffer();

      void SetFile(::file::buffer_sp  pfile);

      void FillFilePosition(Item * pitem);

      virtual bool IsValid() const;
      //void load_string(string & str);
      //void create(memory_offset_t iSize = -1);
      //void seek_to_begin();
      file_position_t seek(file_offset_t lOff,::file::e_seek  nFrom);
      file_position_t get_position() const;

      //virtual string GetFilePath() const;

      file_size_t get_length() const;
      //void Truncate(memory_offset_t iPosition);
      //void clear();
      virtual memory_size_t read(void *lpBuf,memory_size_t nCount);
      virtual void write(const void * lpBuf,memory_size_t nCount);
      virtual void Insert(const void * lpBuf,memory_size_t nCount);
      virtual void Delete(memory_size_t uiCount);



      void flush();
      bool SaveTo(::file::ostream & file);
      bool Save(::file::stream_buffer & file);
      bool Save_N_to_CRLF(::file::stream_buffer & file);


      void Insert(DeleteItem * pitem);
      void Insert(EditItem * pitem);
      void Insert(InsertItem * pitem);
      bool CanUndo();
      bool CanRedo();
      ::count GetRedoBranchCount();
      bool Undo();
      bool Redo();
      void MacroBegin();
      void MacroEnd();




   protected:


      void TreeInsert(Item * pitem);
      bool calc_root_direction();


   private:


      edit_buffer(const ::file::edit_buffer &):
         ::data::data(NULL),
         ::data::tree(NULL)
      {

         }

   };


} // namespace file


