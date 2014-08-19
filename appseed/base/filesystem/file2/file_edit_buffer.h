#pragma once


namespace file
{


   class CLASS_DECL_BASE edit_buffer :
      public ::file::buffer_sp ,
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

         file_position m_dwPosition;


         Item();

         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual file_position get_position(bool bForward);

         virtual BYTE * get_data() ;
         virtual EItemType get_type();
         virtual ::primitive::memory_size get_extent();
         virtual ::primitive::memory_size get_file_extent();
         virtual BYTE * reverse_get_data();
         virtual EItemType reverse_get_type();
         virtual ::primitive::memory_size reverse_get_extent() ;
         virtual ::primitive::memory_size reverse_get_file_extent() ;
         virtual ::primitive::memory_size get_extent(bool bForward);
         virtual EItemType get_type(bool bForward);
         virtual ::primitive::memory_size get_file_extent(bool bForward);
         virtual BYTE * get_data(bool bForward);
         virtual ::primitive::memory_offset get_delta_length() ;

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new BASE_NEW


      };

      class DeleteItem : public Item
      {
      public:


         primitive::memory m_memstorage;


         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual EItemType get_type();
         virtual ::primitive::memory_size get_extent() ;
         virtual ::primitive::memory_size get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type() ;
         virtual ::primitive::memory_size reverse_get_extent();
         virtual ::primitive::memory_size reverse_get_file_extent();
         virtual BYTE * reverse_get_data();

         virtual ::primitive::memory_offset get_delta_length() ;
      };

      class InsertItem : public Item
      {
      public:


         primitive::memory m_memstorage;


         virtual UINT read_ch(::file::edit_buffer * pfile);

         virtual EItemType get_type() ;
         virtual ::primitive::memory_size get_extent() ;
         virtual ::primitive::memory_size get_file_extent() ;
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type() ;
         virtual ::primitive::memory_size reverse_get_extent() ;
         virtual ::primitive::memory_size reverse_get_file_extent() ;
         virtual BYTE * reverse_get_data();
         virtual ::primitive::memory_offset get_delta_length();

      };

      class EditItem : public Item
      {
      public:


         primitive::memory m_memstorage;
         primitive::memory m_memstorageReverse;


         virtual EItemType get_type();
         virtual ::primitive::memory_size get_extent() ;
         virtual ::primitive::memory_size get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type();
         virtual ::primitive::memory_size reverse_get_extent() ;
         virtual ::primitive::memory_size reverse_get_file_extent();
         virtual BYTE * reverse_get_data() ;
         virtual ::primitive::memory_offset get_delta_length();

      };

      class ItemPtrArray : public array < sp(Item), sp(Item) >
      {
      public:
      };

      class GroupItem : public Item, public ItemPtrArray
      {
      public:


         GroupItem * m_pgroupitem;


         virtual EItemType get_type();
         virtual ::primitive::memory_size get_extent();
         virtual ::primitive::memory_size get_file_extent();
         virtual BYTE * get_data() ;
         virtual EItemType reverse_get_type();
         virtual ::primitive::memory_size reverse_get_extent() ;
         virtual ::primitive::memory_size reverse_get_file_extent();
         virtual BYTE * reverse_get_data() ;
         virtual ::primitive::memory_offset get_delta_length();

         virtual UINT read_ch(::file::edit_buffer * pfile);

#undef new
         DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new BASE_NEW

      };

      file_position           m_dwPosition;
      file_size               m_dwInternalFilePosition;
      file_size               m_dwFileLength;
      file_position           m_dwReadPosition;
      file_offset             m_iCurItem;


      sp(::data::tree_item)   m_ptreeitem;
      sp(::data::tree_item)   m_ptreeitemFlush;
      ::primitive::memory_offset              m_iBranch;
      ::file::buffer_sp           m_pfile;
      GroupItem *          m_pgroupitem;
      bool                 m_bRootDirection;

      void SetFile(::file::buffer_sp  pfile);

      void FillFilePosition(sp(Item) pitem);

      edit_buffer(sp(::axis::application) papp);
      virtual ~edit_buffer();

      virtual bool IsValid() const;
      //void load_string(string & str);
      //void create(::primitive::memory_offset iSize = -1);
      //void seek_to_begin();
      file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      file_position get_position() const;

      //virtual string GetFilePath() const;

      file_size get_length() const;
      //void Truncate(::primitive::memory_offset iPosition);
      //void clear();
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void Insert(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void Delete(::primitive::memory_size uiCount);



      void flush();
      bool SaveTo(::file::output_stream & file);
      bool Save(::file::binary_buffer & file);
      bool Save_N_to_CRLF(::file::binary_buffer & file);


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


      void TreeInsert(sp(Item) pitem);
      bool calc_root_direction();


   private:


      edit_buffer(const ::file::edit_buffer & ) :
         ::data::data(NULL),
         ::data::tree(NULL)
      {

      }

   };


} // namespace file


