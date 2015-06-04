#pragma once


namespace user
{

   template < class CELL >
   class mesh_cache  :
      public mesh_cache_interface
   {
   public:

      
      bool                                  m_bCaching;
      int32_t                               m_iCacheNextIndex;
      int_map < int_map < CELL > >          m_map;


      mesh_cache();
      virtual ~mesh_cache();


      void _001Invalidate();
      
      virtual void _001CacheHint(mesh * pmesh, int_ptr iItemStart, int_ptr iItemCount);

      virtual void _001GetItemText(::user::mesh_item * pitem);


   };
   template < class CELL >
   mesh_cache<CELL>::mesh_cache()
   {
      m_bCaching = false;
      m_iCacheNextIndex = 0;
   }
   template < class CELL >
      mesh_cache<CELL>::~mesh_cache()
   {

   }
      template < class CELL >
      void mesh_cache<CELL>::_001CacheHint(::user::mesh * pmesh,index iItemStart,index iItemCount)
   {

      //draw_mesh_item item(pmesh);

      //index i = 0;

      //for(item.m_iItem = iItemStart; i < iItemCount; i++,item.m_iItem++)
      //{

      //   

      //}

   }
      template < class CELL >
   void mesh_cache<CELL>::_001GetItemText(::user::mesh_item * pitem)
   {

      if(m_bCaching)
      {

         return_(pitem->m_bOk,false);

      }

      if(pitem->m_iItem < 0)
      {

         return_(pitem->m_bOk,false);

      }

      {

         auto passoc = m_map.PLookup(pitem->m_iItem);

         if(passoc != NULL)
         {

            auto passoc2 = passoc->m_element2.PLookup(pitem->m_iColumn);

            if(passoc2 != NULL)
            {

               passoc2->m_element2.get_topic_text(pitem->m_strText);

               return_(pitem->m_bOk,true);

            }

         }

      }

      //_001CacheHint(pitem->m_plist, pitem->m_iItem, 1);

      //{

      //   auto passoc = m_map.PLookup(pitem->m_iItem);

      //   if(passoc != NULL)
      //   {

      //      auto passoc2 = passoc->m_element2.PLookup(pitem->m_iItem);

      //      if(passoc2 != NULL)
      //      {

      //         pitem->m_strText = passoc2->m_element2;

      //         return_(pitem->m_bOk,true);

      //      }

      //   }

      //}

      return_(pitem->m_bOk,false);

   }

   template < class CELL >
   void mesh_cache<CELL>::_001Invalidate()
   {
      m_map.remove_all();

   }
} // namespace user

