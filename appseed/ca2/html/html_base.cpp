#include "framework.h"

namespace html
{

   base::base(class tag * ptagParent)
   {
      m_ptagParent = ptagParent;
   }
      
   base::~base()
   {
   }

   class tag * base::parent()
   {
      return m_ptagParent;
   }

   class tag * base::tag()
   {
      ASSERT(get_type() == type_tag);
      return dynamic_cast < class tag * > (this);
   }

   class value * base::value()
   {
      ASSERT(get_type() == type_value);
      return dynamic_cast < class value * > (this);
   }



} // namespace html
