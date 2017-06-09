#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA dibmap_ex1 :
      virtual public map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp >
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
         ::draw2d::dib_sp & dib = map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp>::operator [](key);
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
         
         decltype(begin()) find;

         auto it = begin();

         while (it != end())
         {

            if (it->m_element2->get_ref_count() <= 1 && it->m_element2->area() > iAreaMax)
            {

               iAreaMax = it->m_element2->area();

               find = it;

            }

            it++;

         }

         if (iAreaMax > 0)
         {

            erase(find);

         }
         else
         {

            erase(begin());

         }

      }



   };


} // namespace draw2d




