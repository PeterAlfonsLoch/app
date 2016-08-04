#include "framework.h"

#define MAX_STOP (::numeric_info < file_position_t >::get_maximum_value())

namespace file
{


   edit_buffer::Item::Item()
   {

   }


   bool edit_buffer::Item::read_byte(byte * pbyte, ::file::edit_buffer * pfile)
   {

      UNREFERENCED_PARAMETER(pfile);
      UNREFERENCED_PARAMETER(pbyte);

      throw not_implemented(pfile->get_app());

      return false;

   }

   file_position_t edit_buffer::Item::get_position(bool bForward) { UNREFERENCED_PARAMETER(bForward); return m_dwPosition; };

   BYTE * edit_buffer::Item::get_data() { return NULL; }
   edit_buffer::EItemType edit_buffer::Item::get_type() { return ItemTypeUndefined; }
   memory_size_t edit_buffer::Item::get_extent() { return 0; }
   memory_size_t edit_buffer::Item::get_file_extent() { return 0; }
   BYTE * edit_buffer::Item::reverse_get_data() { return NULL; }
   edit_buffer::EItemType edit_buffer::Item::reverse_get_type() { return ItemTypeUndefined; }
   memory_size_t edit_buffer::Item::reverse_get_extent() { return 0; }
   memory_size_t edit_buffer::Item::reverse_get_file_extent() { return 0; }
   memory_size_t edit_buffer::Item::get_extent(bool bForward) { return bForward ? get_extent() : reverse_get_extent(); }
   edit_buffer::EItemType edit_buffer::Item::get_type(bool bForward) { return bForward ? get_type() : reverse_get_type(); }
   memory_size_t edit_buffer::Item::get_file_extent(bool bForward) { return bForward ? get_file_extent() : reverse_get_file_extent(); }
   BYTE * edit_buffer::Item::get_data(bool bForward) { return bForward ? get_data() : reverse_get_data(); }
   memory_offset_t edit_buffer::Item::get_delta_length()  { return 0; }



   edit_buffer::EItemType edit_buffer::DeleteItem::get_type()
   {
      return ItemTypeDelete;
   }

   memory_size_t edit_buffer::DeleteItem::get_extent()
   {
      return 0;
   }

   memory_size_t edit_buffer::DeleteItem::get_file_extent()
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

   memory_size_t edit_buffer::DeleteItem::reverse_get_extent()
   {

      return m_memstorage.get_size();

   }


   memory_size_t edit_buffer::DeleteItem::reverse_get_file_extent()
   {

      return 0;

   }


   BYTE * edit_buffer::DeleteItem::reverse_get_data()
   {

      return m_memstorage.get_data();

   }


   memory_offset_t edit_buffer::DeleteItem::get_delta_length()
   {

      return - (memory_offset_t) m_memstorage.get_size();

   }


   bool edit_buffer::DeleteItem::read_byte(byte * pbyte, ::file::edit_buffer * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(pfile->m_dwIterationPosition >= m_dwPosition)
         {

            pfile->m_dwIterationPosition += m_memstorage.get_size();

            if (pfile->m_dwStopPosition != MAX_STOP && m_dwPosition < pfile->m_dwStopPosition)
            {

               pfile->m_dwStopPosition += m_memstorage.get_size();

            }

         }
         else if (pfile->m_dwStopPosition > m_dwPosition)
         {

            pfile->m_dwStopPosition = m_dwPosition;

         }

      }
      else
      {
         if(pfile->m_dwPosition + pfile->m_iOffset >= m_dwPosition)
         {

            if(pfile->m_dwPosition + pfile->m_iOffset < (m_dwPosition + m_memstorage.get_size()))
            {

               if (pbyte != NULL)
               {

                  *pbyte = m_memstorage.get_data()[pfile->m_dwPosition - m_dwPosition];

               }

               return true;

            }
            else
            {

               pfile->m_dwPosition -= m_memstorage.get_size();

            }

         }

      }

      return false;

   }




   edit_buffer::EItemType edit_buffer::InsertItem::get_type()
   {
      return ItemTypeInsert;
   }

   memory_size_t edit_buffer::InsertItem::get_extent()
   {
      return m_memstorage.get_size();
   }

   memory_size_t edit_buffer::InsertItem::get_file_extent()
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

   memory_size_t edit_buffer::InsertItem::reverse_get_extent()
   {
      return 0;
   }

   memory_size_t edit_buffer::InsertItem::reverse_get_file_extent()
   {
      return m_memstorage.get_size();
   }

   BYTE * edit_buffer::InsertItem::reverse_get_data()
   {
      return NULL;
   }

   memory_offset_t edit_buffer::InsertItem::get_delta_length()
   {
      return (memory_offset_t) m_memstorage.get_size();
   }



   bool edit_buffer::InsertItem::read_byte(byte * pbyte, ::file::edit_buffer * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(m_dwPosition <= pfile->m_dwIterationPosition)
         {

            if(pfile->m_dwIterationPosition < (m_dwPosition + m_memstorage.get_size()))
            {

               if (pbyte != NULL)
               {

                  *pbyte = m_memstorage.get_data()[pfile->m_dwIterationPosition - m_dwPosition];

               }

               pfile->m_dwPosition++;

               return true;

            }
            else
            {

                pfile->m_dwIterationPosition -= m_memstorage.get_size();

                if (pfile->m_dwStopPosition != MAX_STOP && m_dwPosition  < pfile->m_dwStopPosition)
                {

                   if (m_dwPosition + m_memstorage.get_size() < pfile->m_dwStopPosition)
                   {

                      pfile->m_dwStopPosition -= m_memstorage.get_size();

                   }

                }

            }

         }
         else
         {
          
            if (pfile->m_dwStopPosition > m_dwPosition)
            {

               pfile->m_dwStopPosition = m_dwPosition;

            }

         }

      }
      else
      {

         if(pfile->m_dwPosition + pfile->m_iOffset >= m_dwPosition)
         {

            pfile->m_iOffset -= m_memstorage.get_size();

            pfile->m_dwLength -= m_memstorage.get_size();

         }

      }

      return false;

   }






   edit_buffer::EItemType edit_buffer::EditItem::get_type()
   {
      return ItemTypeEdit;
   }

   memory_size_t edit_buffer::EditItem::get_extent()
   {
      return m_memstorage.get_size();
   }

   memory_size_t edit_buffer::EditItem::get_file_extent()
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

   memory_size_t edit_buffer::EditItem::reverse_get_extent()
   {
      return m_memstorageReverse.get_size();
   }

   memory_size_t edit_buffer::EditItem::reverse_get_file_extent()
   {
      return get_extent();
   }

   BYTE * edit_buffer::EditItem::reverse_get_data()
   {
      return m_memstorageReverse.get_data();
   }

   memory_offset_t edit_buffer::EditItem::get_delta_length()
   {
      return 0;
   }












   edit_buffer::EItemType edit_buffer::GroupItem::get_type()
   {
      return ItemTypeGroup;
   }

   memory_size_t edit_buffer::GroupItem::get_extent()
   {
      return 0;
   }

   memory_size_t edit_buffer::GroupItem::get_file_extent()
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

   memory_size_t edit_buffer::GroupItem::reverse_get_extent()
   {
      return 0;
   }

   memory_size_t edit_buffer::GroupItem::reverse_get_file_extent()
   {
      return 0;
   }

   BYTE * edit_buffer::GroupItem::reverse_get_data()
   {
      return 0;
   }

   memory_offset_t edit_buffer::GroupItem::get_delta_length()
   {
      memory_offset_t iLen = 0;
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         iLen += this->element_at(i)->get_delta_length();
      }
      return iLen;
   }


   bool edit_buffer::GroupItem::read_byte(byte * pbyte, ::file::edit_buffer * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         for(index i = get_upper_bound(); i >= 0; i--)
         {
            
            if (this->element_at(i)->read_byte(pbyte, pfile))
            {

               return true;

            }
               
         }

      }
      else
      {
         for(index i = 0; i < this->get_count(); i++)
         {

            if (this->element_at(i)->read_byte(pbyte, pfile))
            {

               return true;

            }

         }

      }

      return false;

   }


   edit_buffer::edit_buffer(::aura::application * papp):
      object(papp),
      ::data::data(papp),
      ::file::buffer_sp(papp),
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

      if(pfile.cast < ::file::memory_buffer >() == NULL || pfile.cast < ::file::buffered_buffer >() == NULL)
      {

         pfile = canew(::file::buffered_buffer(get_app(),pfile));

      }

      if(pfile == NULL)
         throw invalid_argument_exception(get_app());

      m_pfile = pfile;

      m_dwFileLength = pfile->get_length();

      m_pfile->seek(0,::file::seek_begin);

      m_dwPosition = 0;

   }


   memory_size_t edit_buffer::read(void *lpBuf,memory_size_t nCount)
   {
      
      byte * buf = (byte *)lpBuf;

      memory_size_t uiRead = 0;

      memory_size_t uiReadCount = 0;

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

      uint64_t uiStopSize;

      m_iOffset = 0;

      m_ptreeitemBeg = m_ptreeitemFlush->get_next();

      byte b;


      m_dwLength = m_dwFileLength;

      file_position_t dwStartPosition;

      do
      {

      l1:

         //ptreeitem = m_ptreeitemBeg;

         m_dwStopPosition = MAX_STOP;

         //m_itemptraStop.remove_all();

         // m_iOffset is the position offset valid only for the following while loop

         m_iStartOffset = m_iOffset;

         ptreeitem = m_ptreeitem;

         m_dwIterationPosition = m_dwPosition;

         while (nCount > 0 && ptreeitem != NULL && ptreeitem != m_ptreeitemFlush && m_dwPosition < m_dwLength)
         {

            sp(Item) pitem = (sp(Item))ptreeitem->m_pitem;

            //if (!m_itemptraHit.contains(pitem))
            {



               if (pitem->read_byte(&b, this))
               {

                  buf[uiRead] = b;

                  nCount--;

                  uiRead++;

                  //m_dwPosition++;

                  goto l1;

               }

            }


            if (nCount <= 0)
               break;

            ptreeitem = m_bRootDirection ? ptreeitem->get_previous() : ptreeitem->get_next();

            //ptreeitem = ptreeitem->get_next();

            //if (ptreeitem == m_ptreeitemEnd)
            //{

            //   break;

            //}

         }

         uiReadCount = 0;

         uiStopSize = m_pfile->get_length();

         if (m_dwStopPosition < uiStopSize && m_dwIterationPosition <= m_dwStopPosition)
         {

            uiStopSize = m_dwStopPosition;

         }

         while(nCount > 0 && m_dwIterationPosition < uiStopSize  && m_dwPosition < m_dwLength)
         {

            m_pfile->seek((file_offset_t)m_dwIterationPosition,::file::seek_begin);

            uiReadCount = m_pfile->read(&buf[uiRead],(memory_size_t) MAX(0, MIN(uiStopSize - m_dwIterationPosition, nCount)));

            if(uiReadCount <= 0)
               break;

            nCount -= uiReadCount;

            uiRead += uiReadCount;

            m_dwPosition += uiReadCount;

            m_dwIterationPosition += uiReadCount;

         }

      } while(nCount > 0 && m_dwPosition < m_dwLength);

      return uiRead;

   }


   void edit_buffer::TreeInsert(Item * pitem)
   {
      if(m_pgroupitem != NULL
         && m_pgroupitem != pitem)
      {
         m_pgroupitem->add(pitem);
         return;
      }
      sp(::data::tree_item) pitemNew;
      if(m_ptreeitem != NULL && m_ptreeitem->next() != NULL)
      {
         pitemNew = insert_item(pitem,::data::RelativeFirstChild,m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }
      else
      {
         pitemNew = insert_item(pitem,::data::RelativeLastSibling,m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_ptreeitem = pitemNew;
         }
      }

   }

   void edit_buffer::write(const void * lpBuf,memory_size_t nCount)
   {
      EditItem * pedit;
      pedit = canew(EditItem);
      pedit->m_dwPosition = m_dwPosition;
      pedit->m_memstorage.allocate(nCount);
      memcpy(pedit->m_memstorage.get_data(),lpBuf,nCount);
      TreeInsert(pedit);
      m_dwPosition += nCount;
   }

   void edit_buffer::Insert(const void * lpBuf,memory_size_t nCount)
   {
      InsertItem * pinsert;
      pinsert = canew(InsertItem);
      pinsert->m_dwPosition = m_dwPosition;
      pinsert->m_memstorage.allocate(nCount);
      memcpy(pinsert->m_memstorage.get_data(),lpBuf,nCount);
      TreeInsert(pinsert);
      m_dwFileLength += nCount;
   }

   void edit_buffer::Delete(memory_size_t uiCount)
   {

      DeleteItem * pdelete;

      uiCount = MIN(uiCount,(memory_size_t) (get_length() - m_dwPosition));
      if(uiCount == 0)
         return;

      pdelete = canew(DeleteItem);
      pdelete->m_dwPosition = m_dwPosition;
      pdelete->m_memstorage.allocate(uiCount);
      seek((file_offset_t)m_dwPosition,::file::seek_begin);
      read(pdelete->m_memstorage.get_data(),uiCount);
      TreeInsert(pdelete);
      m_dwFileLength -= uiCount;

   }


   file_position_t edit_buffer::get_position() const
   {
      return m_dwPosition;
   }

   bool edit_buffer::IsValid() const
   {
      return true;
   }

   file_position_t edit_buffer::seek(file_offset_t lOff,::file::e_seek nFrom)
   {
      ASSERT(IsValid());
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      file_position_t dwNew = (uint32_t)-1;

      switch(nFrom)
      {
      case ::file::seek_begin:
         dwNew = (file_position_t)lOff;
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
         return (file_position_t)-1;
      }

      m_dwPosition = 0;

      memory_size_t uiRead = 0;

      memory_size_t uiReadCount = 0;

      if (m_dwPosition >= m_dwFileLength)
      {

         return uiRead;

      }

      //      uint32_t dwPosition = m_dwPosition;
      //      uint32_t dwFilePosition = m_dwPosition;
      //      uint32_t dwMaxCount = m_dwFileLength;
      //      uint32_t dwUpperLimit = m_dwFileLength;
      //      int32_t iOffset =0;

//      sp(::data::tree_item) ptreeitem;
//
//      //      GroupItem * pitemgroup = NULL;
//
//      int_array ia;
//
//      m_bRootDirection = calc_root_direction();
//
//      UINT uiReadItem = 0xffffffff;
//
//      uint64_t uiStopSize;
//
//      m_iStartOffset = 0;
//
//      m_iOffset = 0;
//
//      DWORD dwNewParam = dwNew;
//
//      m_itemptraHit.remove_all();
//
//      do
//      {
//
//      l1:
//
//         ptreeitem = m_ptreeitem;
//
//         m_dwLength = dwNew;
//
////         m_itemptraStop.remove_all();
//
//         m_dwStopPosition = ::numeric_info < file_position_t > ::get_maximum_value();
//
//         // m_iOffset is the position offset valid only for the following while loop
//
//         // m_iOffset = m_iStartOffset;
//
//         while (dwNew > 0 && ptreeitem != NULL && ptreeitem != m_ptreeitemFlush && m_dwPosition < m_dwLength)
//         {
//
//            sp(Item) pitem = (sp(Item))ptreeitem->m_pitem;
//
////            if (!m_itemptraHit.contains(pitem))
//            {
//
//               if (pitem->read_byte(NULL, this))
//               {
//
//                  m_itemptraHit.add(pitem);
//
//                  dwNew--;
//
//                  uiRead++;
//
//                  m_dwPosition++;
//
//                  goto l1;
//
//               }
//
//            }
//
//            if (dwNew <= 0)
//               break;
//
//            ptreeitem = m_bRootDirection ? ptreeitem->get_previous() : ptreeitem->get_next();
//
//         }
//
//         uiReadCount = 0;
//
//         uiStopSize = m_pfile->get_length();
//
//         if (m_dwStopPosition < uiStopSize && m_dwPosition <= m_dwStopPosition)
//         {
//
//            uiStopSize = m_dwStopPosition;
//
//         }
//
//         while (dwNew > 0 && m_dwPosition < uiStopSize)
//         {
//
//            m_pfile->seek((file_offset_t)m_dwPosition, ::file::seek_begin);
//
//            uiReadCount = MIN(uiStopSize - m_dwPosition, dwNew);
//
//            if (uiReadCount <= 0)
//               break;
//
//            dwNew -= uiReadCount;
//
//            uiRead += uiReadCount;
//
//            m_dwPosition += uiReadCount;
//
//         }
//
//      } while (dwNew > 0 && m_dwPosition < m_dwLength && uiReadCount > 0);

      m_dwPosition = dwNew;

      return dwNew;

   }


   file_size_t edit_buffer::get_length() const
   {
      return m_dwFileLength;
   }

   void edit_buffer::flush()
   {
      string strTimeFile;

      strTimeFile = Application.file().time_square();

      ::file::buffer_sp spfile = Application.file().get_file(strTimeFile,::file::type_binary | ::file::mode_read_write | ::file::mode_create | ::file::defer_create_directory);

      if(spfile.is_null())
      {
         throw ::file::exception(get_app(),::file::exception::none,-1,strTimeFile);
         return;
      }

      Save(*spfile);

      char buf[4096];
      memory_size_t uiRead;
      m_pfile->set_length(0);
      spfile->seek(0,::file::seek_begin);
      while((uiRead = spfile->read(buf,sizeof(buf))) > 0)
      {
         m_pfile->write(buf,uiRead);
      }
      m_pfile->flush();
      m_dwFileLength = m_pfile->get_length();
      m_ptreeitemFlush = m_ptreeitem;
   }

   bool edit_buffer::SaveTo(::file::ostream & ostream)
   {
      char buf[4096];
      memory_size_t uiRead;
      seek(0,::file::seek_begin);
      while((uiRead = read(buf,sizeof(buf))) > 0)
      {
         ostream.write(buf,uiRead);
      }
      ostream.flush();
      //file.close();
      return true;
   }

   bool edit_buffer::Save(::file::stream_buffer & file)
   {
      char buf[4096];
      memory_size_t uiRead;
      file.set_length(0);
      seek(0,::file::seek_begin);
      while((uiRead = read(buf,sizeof(buf))) > 0)
      {
         file.write(buf,uiRead);
      }
      file.flush();
      //file.close();
      return true;
   }

   bool edit_buffer::Save_N_to_CRLF(::file::stream_buffer & file)
   {
      char buf[4096];
      string str;
      memory_size_t uiRead;
      file.set_length(0);
      seek(0,::file::seek_begin);
      while((uiRead = read(buf,sizeof(buf))) > 0)
      {
         buf[uiRead] = '\0';
         str = buf;
         str.replace("\n","\r\n");
         file.write(str,str.get_length());
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
         || m_ptreeitem->get_next(false,false) != NULL;
   }

   ::count edit_buffer::GetRedoBranchCount()
   {
      if(m_ptreeitem == NULL)
         return 1;
      else
         return   m_ptreeitem->get_expandable_children_count()
         + (m_ptreeitem->get_next(false,false) != NULL ? 1 : 0)
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
      m_dwFileLength += ((sp(Item)) ptreeitem->m_pitem)->get_delta_length();
      m_ptreeitem = ptreeitem;
      return true;
   }

   void edit_buffer::MacroBegin()
   {
      GroupItem * pgroupitem = canew(GroupItem);
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



