#include "StdAfx.h"

namespace database
{

   key::key()
   {
   }

   key::key(const key & key)
   {
      operator = (key);
   }

   key::key(::database::id idSection, ::database::id idKey, ::database::id idIndex)
   {
      m_idSection    = idSection;
      m_idKey        = idKey;
      m_idIndex      = idIndex;
   }



   key & key::operator = (const key & key)
   {
      if(&key != this)
      {
         m_idSection    = key.m_idSection;
         m_idKey        = key.m_idKey;
         m_idIndex      = key.m_idIndex;
      }
      return *this;
   }

} // namespace database
