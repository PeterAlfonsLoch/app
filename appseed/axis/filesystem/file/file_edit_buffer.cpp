#include "framework.h"


namespace file
{


   edit_buffer::Item::Item()
   {

   }


   UINT edit_buffer::Item::read_ch(::file::edit_buffer * pfile)
   {

      UNREFERENCED_PARAMETER(pfile);

      throw not_implemented(pfile->get_app());

      return 0;

   }


   file_position edit_buffer::Item::get_position(bool bForward) {UNREFERENCED_PARAMETER(bForward); return m_dwPosition;};

   BYTE * edit_buffer::Item::get_data() { return NULL; }
   edit_buffer::EItemType edit_buffer::Item::get_type() { return ItemTypeUndefined; }
   ::primitive::memory_size edit_buffer::Item::get_extent() { return 0; }
   ::primitive::memory_size edit_buffer::Item::get_file_extent() { return 0; }
   BYTE * edit_buffer::Item::reverse_get_data() { return NULL; }
   edit_buffer::EItemType edit_buffer::Item::reverse_get_type() { return ItemTypeUndefined; }
   ::primitive::memory_size edit_buffer::Item::reverse_get_extent() { return 0; }
   ::primitive::memory_size edit_buffer::Item::reverse_get_file_extent() { return 0; }
   ::primitive::memory_size edit_buffer::Item::get_extent(bool bForward) { return bForward ? get_extent() : reverse_get_extent(); }
   edit_buffer::EItemType edit_buffer::Item::get_type(bool bForward) { return bForward ? get_type() : reverse_get_type(); }
   ::primitive::memory_size edit_buffer::Item::get_file_extent(bool bForward) { return bForward ? get_file_extent() : reverse_get_file_extent(); }
   BYTE * edit_buffer::Item::get_data(bool bForward) { return bForward ? get_data() : reverse_get_data(); }
   ::primitive::memory_offset edit_buffer::Item::get_delta_length()  { return 0; }



   edit_buffer::EItemType edit_buffer::DeleteItem::get_type()
   {
      return ItemTypeDelete;
   }

   ::primitive::memory_size edit_buffer::DeleteItem::get_extent()
   {
      return 0;
   }

   ::primitive::memory_size edit_buffer::DeleteItem::get_file_extent()
   {
      return m_memstorage.get_size();
   }

   BYTE * edit_buffer::DeleteItem::get_data()
   {
      return NULL;
   }

   edit_buffer::EItemType edit_buffer::DeleteItem::reverse_get_type()
   {
      return ItemTypeInsert;
   }

   ::primitive::memory_size edit_buffer::DeleteItem::reverse_get_extent()
   {
      return m_memstorage.get_size();
   }

   ::primitive::memory_size edit_buffer::DeleteItem::reverse_get_file_extent()
   {
      return 0;
   }

   BYTE * edit_buffer::DeleteItem::reverse_get_data()
   {
      return m_memstorage.get_data();
   }

   ::primitive::memory_offset edit_buffer::DeleteItem::get_delta_length()
   {
      return - (::primitive::memory_offset) m_memstorage.get_size();
   }

   UINT edit_buffer::DeleteItem::read_ch(::file::edit_buffer * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            pfile->m_dwReadPosition += m_memstorage.get_size();
         }
      }
      else
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorage.get_size()))
            {
               return ((byte *)m_memstorage.get_data())[pfile->m_dwReadPosition - m_dwPosition];
            }
            else
            {
               pfile->m_dwReadPosition -= m_memstorage.get_size();
            }
         }
      }
      return 0xffffffff;
   }









   edit_buffer::EItemType edit_buffer::InsertItem::get_type()
   {
      return ItemTypeInsert;
   }

   ::primitive::memory_size edit_buffer::InsertItem::get_extent()
   {
      return m_memstorage.get_size();
   }

   ::primitive::memory_size edit_buffer::InsertItem::get_file_extent()
   {
      return 0;
   }

   BYTE * edit_buffer::InsertItem::get_data()
   {
      return m_memstorage.get_data();
   }

   edit_buffer::EItemType edit_buffer::InsertItem::reverse_get_type()
   {
      return ItemTypeDelete;
   }

   ::primitive::memory_size edit_buffer::InsertItem::reverse_get_extent()
   {
      return 0;
   }

   ::primitive::memory_size edit_buffer::InsertItem::reverse_get_file_extent()
   {
      return m_memstorage.get_size();
   }

   BYTE * edit_buffer::InsertItem::reverse_get_data()
   {
      return NULL;
   }

   ::primitive::memory_offset edit_buffer::InsertItem::get_delta_length()
   {
      return (::primitive::memory_offset) m_memstorage.get_size();
   }



   UINT edit_buffer::InsertItem::read_ch(::file::edit_buffer * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            if(pfile->m_dwReadPosition < (m_dwPosition + m_memstorage.get_size()))
            {
               return ((byte *)m_memstorage.get_data())[pfile->m_dwReadPosition - m_dwPosition];
            }
            else
            {
               pfile->m_dwReadPosition -= m_memstorage.get_size();
            }
         }
      }
      else
      {
         if(pfile->m_dwReadPosition >= m_dwPosition)
         {
            pfile->m_dwReadPosition += m_memstorage.get_size();
         }
      }
      return 0xffffffff;
   }










   edit_buffer::EItemType edit_buffer::EditItem::get_type()
   {
      return ItemTypeEdit;
   }

   ::primitive::memory_size edit_buffer::EditItem::get_extent()
   {
      return m_memstorage.get_size();
   }

   ::primitive::memory_size edit_buffer::EditItem::get_file_extent()
   {
      return get_extent();
   }

   BYTE * edit_buffer::EditItem::get_data()
   {
      return m_memstorage.get_data();
   }

   edit_buffer::EItemType edit_buffer::EditItem::reverse_get_type()
   {
      return ItemTypeEdit;
   }

   ::primitive::memory_size edit_buffer::EditItem::reverse_get_extent()
   {
      return m_memstorageReverse.get_size();
   }

   ::primitive::memory_size edit_buffer::EditItem::reverse_get_file_extent()
   {
      return get_extent();
   }

   BYTE * edit_buffer::EditItem::reverse_get_data()
   {
      return m_memstorageReverse.get_data();
   }

   ::primitive::memory_offset edit_buffer::EditItem::get_delta_length()
   {
      return 0;
   }












   edit_buffer::EItemType edit_buffer::GroupItem::get_type()
   {
      return ItemTypeGroup;
   }

   ::primitive::memory_size edit_buffer::GroupItem::get_extent()
   {
      return 0;
   }

   ::primitive::memory_size edit_buffer::GroupItem::get_file_extent()
   {
      return 0;
   }

   BYTE * edit_buffer::GroupItem::get_data()
   {
      return 0;
   }

   edit_buffer::EItemType edit_buffer::GroupItem::reverse_get_type()
   {
      return ItemTypeGroup;
   }

   ::primitive::memory_size edit_buffer::GroupItem::reverse_get_extent()
   {
      return 0;
   }

   ::primitive::memory_size edit_buffer::GroupItem::reverse_get_file_extent()
   {
      return 0;
   }

   BYTE * edit_buffer::GroupItem::reverse_get_data()
   {
      return 0;
   }

   ::primitive::memory_offset edit_buffer::GroupItem::get_delta_length()
   {
      ::primitive::memory_offset iLen = 0;
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         iLen += this->element_at(i)->get_delta_length();
      }
      return iLen;
   }

   UINT edit_buffer::GroupItem::read_ch(::file::edit_buffer * pfile)
   {
      if(pfile->m_bRootDirection)
      {
         for(index i = get_upper_bound(); i >= 0; i--)
         {
            UINT uiReadItem = this->element_at(i)->read_ch(pfile);
            if(uiReadItem <= 255)
               return uiReadItem;
         }
      }
      else
      {
         for(index i = 0; i < this->get_count(); i++)
         {
            UINT uiReadItem = this->element_at(i)->read_ch(pfile);
            if(uiReadItem <= 255)
               return uiReadItem;
         }
      }
      return 0xffffffff;
   }


   edit_buffer::edit_buffer(sp(::axis::application) papp) :
      element(papp),
      ::file::buffer_sp(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {

      m_iBranch = 0;
      m_pgroupitem = NULL;

      m_ptreeitem = get_base_item();
      m_ptreeitemFlush = get_base_item();

   }

   edit_buffer::~edit_buffer()
   {

   }


   void edit_buffer::SetFile(::file::buffer_sp  pfile)
   {

      if(pfile == NULL)
         throw invalid_argument_exception(get_app());

      m_pfile = pfile;

      m_dwFileLength = pfile->get_length();

      m_pfile->seek(0, ::file::seek_begin);

      m_dwPosition = 0;

   }


   ::primitive::memory_size edit_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      byte * buf = (byte *) lpBuf;
      UINT uiRead = 0;
      if(m_dwPosition >= m_dwFileLength)
      {
         return uiRead;
      }
//      uint32_t dwPosition = m_dwPosition;
//      uint32_t dwFilePosition = m_dwPosition;
//      uint32_t dwMaxCount = m_dwFileLength;
//      uint32_t dwUpperLimit = m_dwFileLength;
//      int32_t iOffset =0;
      sp(::data::tree_item) ptreeitem;
//      GroupItem * pitemgroup = NULL;
      int_array ia;

      m_bRootDirection = calc_root_direction();

      UINT uiReadItem = 0xffffffff;
      do
      {
l1:
         ptreeitem = m_ptreeitem;
         m_dwReadPosition = m_dwPosition;
         while(nCount > 0 && ptreeitem != NULL && ptreeitem != m_ptreeitemFlush && m_dwPosition < m_dwFileLength)
         {
            sp(Item) pitem = (sp(Item) )ptreeitem->m_pitem;
            uiReadItem = pitem->read_ch(this);
            if(uiReadItem <= 255)
            {
               buf[uiRead] = (byte) uiReadItem;
               nCount--;
               uiRead++;
               m_dwPosition++;
               goto l1;
            }
            if(nCount <= 0)
               break;
            ptreeitem = m_bRootDirection ? ptreeitem->get_previous() : ptreeitem->get_next();
         }
         if(nCount > 0 && m_dwPosition < m_dwFileLength)
         {
            m_pfile->seek((file_offset) m_dwPosition, ::file::seek_begin);
            if(!m_pfile->read(&uiReadItem, 1))
               break;
            buf[uiRead] = (byte) uiReadItem;
            nCount--;
            uiRead++;
            m_dwPosition++;
         }
         else
         {
            break;
         }
      } while(nCount > 0 && m_dwPosition < m_dwFileLength);
      return uiRead;
   }


   void edit_buffer::TreeInsert(sp(Item) pitem)
   {
      if(m_pgroupitem != NULL
        && m_pgroupitem != pitem)
      {
         m_pgroupitem->add(pitem);
         return;
      }
      sp(::data::tree_item) pitemNew = NULL;
      if(m_ptreeitem != NULL && m_ptreeitem->next().is_set())
      {
         pitemNew = insert_item(pitem, ::data::RelativeFirstChild, m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }
      else
      {
         pitemNew = insert_item(pitem, ::data::RelativeLastSibling, m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }

   }

   void edit_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      EditItem * pedit;
      pedit = new EditItem;
      pedit->m_dwPosition = m_dwPosition;
      pedit->m_memstorage.allocate(nCount);
      memcpy(pedit->m_memstorage.get_data(), lpBuf, nCount);
      TreeInsert(pedit);
      m_dwPosition += nCount;
   }

   void edit_buffer::Insert(const void * lpBuf, ::primitive::memory_size nCount)
   {
      InsertItem * pinsert;
      pinsert = new InsertItem;
      pinsert->m_dwPosition = m_dwPosition;
      pinsert->m_memstorage.allocate(nCount);
      memcpy(pinsert->m_memstorage.get_data(), lpBuf, nCount);
      TreeInsert(pinsert);
      m_dwFileLength += nCount;
   }

   void edit_buffer::Delete(::primitive::memory_size uiCount)
   {

      DeleteItem * pdelete;

      uiCount = MIN(uiCount, (::primitive::memory_size) (get_length() - m_dwPosition));
      if(uiCount == 0)
         return;

      pdelete = new DeleteItem;
      pdelete->m_dwPosition = m_dwPosition;
      pdelete->m_memstorage.allocate(uiCount);
      seek((file_offset) m_dwPosition, ::file::seek_begin);
      read(pdelete->m_memstorage.get_data(), uiCount);
      TreeInsert(pdelete);
      m_dwFileLength -= uiCount;

   }


   file_position edit_buffer::get_position() const
   {
      return m_dwPosition;
   }

   bool edit_buffer::IsValid() const
   {
      return true;
   }

   file_position edit_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      ASSERT(IsValid());
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      file_position dwNew = (uint32_t) -1;

      switch(nFrom)
      {
      case ::file::seek_begin:
         dwNew = (file_position) lOff;
         break;
      case ::file::seek_end:
         dwNew = get_length() - lOff;
         break;
      case ::file::seek_current:
         if(lOff < 0)
         {
            dwNew = m_dwPosition + lOff;
            if(dwNew > m_dwPosition)
               dwNew = 0;
         }
         else
         {
            dwNew = m_dwPosition + lOff;
         }

         break;
      default:
         return (file_position) -1;
      }

      m_dwPosition = dwNew;

      return dwNew;
   }


   file_size edit_buffer::get_length() const
   {
      return m_dwFileLength;
   }

   void edit_buffer::flush()
   {
      string strTimeFile;

      strTimeFile = Application.file_time_square();

      ::file::binary_buffer_sp spfile = Application.file_get_file(strTimeFile, ::file::type_binary | ::file::mode_read_write | ::file::mode_create | ::file::defer_create_directory);

      if(spfile.is_null())
      {
         throw ::file::exception(get_app(), ::file::exception::none, -1, strTimeFile);
         return;
      }

      Save(*spfile);

      char buf[4096];
      primitive::memory_size uiRead;
      m_pfile->set_length(0);
      spfile->seek(0, ::file::seek_begin);
      while((uiRead = spfile->read(buf, sizeof(buf))) > 0)
      {
         m_pfile->write(buf, uiRead);
      }
      m_pfile->flush();
      m_dwFileLength = m_pfile->get_length();
      m_ptreeitemFlush = m_ptreeitem;
   }

   bool edit_buffer::SaveTo(::file::output_stream & ostream)
   {
      char buf[4096];
      primitive::memory_size uiRead;
      seek(0, ::file::seek_begin);
      while((uiRead = read(buf, sizeof(buf))) > 0)
      {
         ostream.write(buf, uiRead);
      }
      ostream.flush();
      //file.close();
      return true;
   }

   bool edit_buffer::Save(::file::binary_buffer & file)
   {
      char buf[4096];
      primitive::memory_size uiRead;
      file.set_length(0);
      seek(0, ::file::seek_begin);
      while((uiRead = read(buf, sizeof(buf))) > 0)
      {
         file.write(buf, uiRead);
      }
      file.flush();
      //file.close();
      return true;
   }

   bool edit_buffer::Save_N_to_CRLF(::file::binary_buffer & file)
   {
      char buf[4096];
      string str;
      primitive::memory_size uiRead;
      file.set_length(0);
      seek(0, ::file::seek_begin);
      while((uiRead = read(buf, sizeof(buf))) > 0)
      {
         buf[uiRead] = '\0';
         str = buf;
         str.replace("\n", "\r\n");
         file.write(str, str.get_length());
      }
      //file.flush();
      file.close();
      return true;
   }


   bool edit_buffer::CanUndo()
   {
      return m_ptreeitem != get_base_item();
   }

   bool edit_buffer::CanRedo()
   {
      return m_iBranch < m_ptreeitem->get_expandable_children_count()
         || m_ptreeitem->get_next(false, false) != NULL;
   }

   ::count edit_buffer::GetRedoBranchCount()
   {
      if(m_ptreeitem == NULL)
         return 1;
      else
         return   m_ptreeitem->get_expandable_children_count()
           + (m_ptreeitem->get_next(false, false) != NULL ? 1 : 0)
           + (m_ptreeitem->m_children.has_elements() ? 1 : 0);
   }

   bool edit_buffer::Undo()
   {
      if(!CanUndo())
         return false;

      m_dwFileLength -= ((sp(Item))m_ptreeitem->m_pitem)->get_delta_length();
      m_ptreeitem = m_ptreeitem->get_previous();

      return true;
   }

   bool edit_buffer::Redo()
   {
      if(m_iBranch < 0 || m_iBranch >= GetRedoBranchCount())
      {
         return false;
      }
//      sp(Item) pitem = NULL;
      sp(::data::tree_item) ptreeitem;
      if(m_iBranch < m_ptreeitem->get_expandable_children_count())
      {
         ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);
      }
      else
         ptreeitem = m_ptreeitem->get_next();
      if(ptreeitem == NULL)
         return false;
      m_dwFileLength += (( sp(Item) ) ptreeitem->m_pitem)->get_delta_length();
      m_ptreeitem = ptreeitem;
      return true;
   }

   void edit_buffer::MacroBegin()
   {
      GroupItem * pgroupitem = new GroupItem;
      pgroupitem->m_pgroupitem = m_pgroupitem;
      m_pgroupitem = pgroupitem;
   }

   void edit_buffer::MacroEnd()
   {
      if(m_pgroupitem == NULL)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_pgroupitem->m_pgroupitem == NULL)
      {
         TreeInsert(m_pgroupitem);
      }
      m_pgroupitem = m_pgroupitem->m_pgroupitem;
   }



   bool edit_buffer::calc_root_direction()
   {
      sp(::data::tree_item) ptreeitem;
      if(m_ptreeitem == m_ptreeitemFlush)
         return false;
      for(ptreeitem  = m_ptreeitem;
          ptreeitem != m_ptreeitemFlush && ptreeitem != get_base_item() && ptreeitem != NULL;
          ptreeitem  = ptreeitem->get_previous())
      {
      }
      return ptreeitem == m_ptreeitemFlush;
   }




} // namespace core



