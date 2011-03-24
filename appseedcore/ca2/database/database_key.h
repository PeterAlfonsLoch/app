#pragma once

namespace database
{

   class CLASS_DECL_ca key
   {
   public:
      key();
      key(const key & key);
      key(id idSection, id idKey, id idIndex);

      id              m_idSection;
      id              m_idKey;
      id              m_idIndex;

      key & operator = (const key & key);
   };

} // namespace database