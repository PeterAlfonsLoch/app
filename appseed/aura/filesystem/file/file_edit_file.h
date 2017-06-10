#pragma once


namespace file
{


   class CLASS_DECL_AURA edit_file:
      public ::file::file_sp,
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

      class Item :
         public ::data::item
      {
      public:


         file_position_t   m_dwPosition;

         Item();

         virtual bool read_byte(byte  * pbyte, ::file::edit_file * pfile);

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

//#undef new
//         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
//#define new AURA_NEW


      };

      class DeleteItem :
         public Item
      {
      public:


         memory m_memstorage;


         virtual bool read_byte(byte * pbyte, ::file::edit_file * pfile) override;

         virtual EItemType get_type() override;
         virtual memory_size_t get_extent() override ;
         virtual memory_size_t get_file_extent() override ;
         virtual BYTE * get_data()  override;
         virtual EItemType reverse_get_type()  override;
         virtual memory_size_t reverse_get_extent() override;
         virtual memory_size_t reverse_get_file_extent() override;
         virtual BYTE * reverse_get_data() override;

         virtual memory_offset_t get_delta_length()  override;
      };

      class InsertItem :
         public Item
      {
      public:


         memory m_memstorage;


         virtual bool read_byte(byte * pbyte, ::file::edit_file * pfile) override;

         virtual EItemType get_type()  override;
         virtual memory_size_t get_extent()  override;
         virtual memory_size_t get_file_extent() override ;
         virtual BYTE * get_data()  override;
         virtual EItemType reverse_get_type()  override;
         virtual memory_size_t reverse_get_extent() override ;
         virtual memory_size_t reverse_get_file_extent() override ;
         virtual BYTE * reverse_get_data() override;
         virtual memory_offset_t get_delta_length() override;

      };

      class EditItem :
         public Item
      {
      public:


         memory m_memstorage;
         memory m_memstorageReverse;


         virtual EItemType get_type() override;
         virtual memory_size_t get_extent() override ;
         virtual memory_size_t get_file_extent() override;
         virtual BYTE * get_data()  override;
         virtual EItemType reverse_get_type() override;
         virtual memory_size_t reverse_get_extent() override ;
         virtual memory_size_t reverse_get_file_extent() override;
         virtual BYTE * reverse_get_data()  override;
         virtual memory_offset_t get_delta_length() override;

      };

      class ItemPtrArray :
         public spa(Item)
      {
      public:
      };

      class GroupItem :
         public Item,
         public ItemPtrArray
      {
      public:


         GroupItem * m_pgroupitem;


         virtual EItemType get_type() override;
         virtual memory_size_t get_extent() override;
         virtual memory_size_t get_file_extent() override;
         virtual BYTE * get_data() override ;
         virtual EItemType reverse_get_type() override;
         virtual memory_size_t reverse_get_extent() override ;
         virtual memory_size_t reverse_get_file_extent() override;
         virtual BYTE * reverse_get_data()  override;
         virtual memory_offset_t get_delta_length() override;

         virtual bool read_byte(byte * pbyte, ::file::edit_file * pfile) override;

//#undef new
//         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
//#define new AURA_NEW

      };

      file_position_t                     m_dwPosition;
      file_position_t                     m_dwLength;
      file_position_t                     m_dwIterationPosition;
      file_size_t                         m_dwInternalFilePosition;
      file_size_t                         m_dwFileLength;
      //file_position_t                     m_dwStopPosition;
      file_offset_t                       m_iCurItem;
      file_offset_t                       m_iOffset;
      file_offset_t                       m_iStartOffset;

      ::comparable_array < Item * >       m_itemptraHit;
      ::comparable_array < Item * >       m_itemptraRead;


      sp(::data::tree_item)               m_ptreeitem;
      sp(::data::tree_item)               m_ptreeitemFlush;
      sp(::data::tree_item)               m_ptreeitemBeg;
      sp(::data::tree_item)               m_ptreeitemEnd;
      memory_offset_t                     m_iBranch;
      ::file::file_sp                   m_pfile;
      sp(GroupItem)                       m_pgroupitem;
      bool                                m_bRootDirection;

      edit_file(::aura::application * papp);
      virtual ~edit_file();

      void SetFile(::file::file_sp  pfile);

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
      virtual InsertItem * Insert(const void * lpBuf,memory_size_t nCount);
      virtual DeleteItem * Delete(memory_size_t uiCount);



      void flush();
      bool SaveTo(::file::ostream & file);
      bool Save(::file::file & file);
      bool Save_N_to_CRLF(::file::file & file);


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


      edit_file(const ::file::edit_file &):
         ::data::data(NULL),
         ::data::tree(NULL)
      {

         }

   };


} // namespace file


