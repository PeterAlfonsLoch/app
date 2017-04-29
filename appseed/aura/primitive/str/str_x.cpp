

namespace str
{


   bool x_contains(string str, string strFind)
   {

      strsize iFind = 0;

      while ((iFind = str.find_ci(strFind, iFind)) >= 0)
      {

         bool bLowerBound1 = iFind == 0;
         bool bLowerBound = bLowerBound1 || !isalpha_dup(strFind[iFind - 1]);
         strsize iUpperBound = iFind + strFind.get_length();
         bool bUpperBound1 = iUpperBound == str.get_length();
         bool bUpperBound = bUpperBound1 || !isalpha_dup(strFind[iUpperBound]);

         if (bLowerBound && bUpperBound)
         {

            return true;

         }

         iFind++;

      }

      return false;

   }

   bool x_find(stringa & stra, string str)
   {

      for (auto & strFind : stra)
      {

         if (x_contains(str, strFind))
         {

            return true;

         }

      }

      return false;

   }

   /// [Idee:ChrifRachid@liveedutv] remove http:// and https:// from resident speech

   void x_left_remove(string & str, string strFind)
   {

      strsize iFind = 0;

      while ((iFind = str.find_ci(strFind, iFind)) >= 0)
      {

         if (iFind == 0 || !isalpha_dup(str[iFind - 1]))
         {

            str = str.Left(iFind) + str.Mid(iFind + strFind.get_length());

         }
         else
         {

            iFind++;

         }

      }

   }


} // namespace str



