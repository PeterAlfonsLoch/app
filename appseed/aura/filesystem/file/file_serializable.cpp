//#include "framework.h"


namespace file
{

      
   //serializable::serializable()
   //{

   //}

   void serializable::write(ostream & ostream)
   {

      ((const serializable *) this)->write(ostream);

   }

   void serializable::write(ostream & ostream) const
   {
      
      ((serializable *) this)->write(ostream);

   }

   void serializable::read(istream & istream)
   {

   }

} // namespace file


















