#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA dibmap_ex1 :
      virtual public map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp, ::draw2d::dib_sp >
   {
   public:


      int32_t m_iLimitCount;


      dibmap_ex1(::aura::application * papp, int32_t iLimitCount = 500) :
         object(papp)
      {

         m_iLimitCount = iLimitCount;

      }


      inline ::draw2d::dib_sp & operator[](class ::draw2d::dib::descriptor key)
      {
         while (get_count() > m_iLimitCount)
         {
            remove_bigger();
         }
         ::draw2d::dib_sp & dib = map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp, ::draw2d::dib_sp >::operator [](key);
         if (dib.is_null())
         {
            dib.alloc(allocer());
            dib->create(key.m_size);
         }
         return dib;
      }



      void remove_bigger()
      {

         ::draw2d::dib::descriptor keyFind;
         int64_t iAreaMax = 0;
         assoc * passoc = PGetFirstAssoc();
         while (passoc != NULL)
         {
            if (passoc->m_element2->get_ref_count() <= 1 && passoc->m_element2->area() > iAreaMax)
            {
               iAreaMax = passoc->m_element2->area();
               keyFind = passoc->m_element1;
            }
            passoc = passoc->m_pnext;
         }

         if (iAreaMax > 0)
         {
            remove_key(keyFind);
         }
         else
         {
            remove_key(PGetFirstAssoc()->m_element1);
         }
      }



   };


} // namespace draw2d




