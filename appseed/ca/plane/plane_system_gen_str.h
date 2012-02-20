#pragma once


namespace gen
{


   namespace str
   {


      inline CLASS_DECL_ca string         itoa(const id & id)
      {

         if(!id.is_number())
            throw simple_exception("invalid_conversion");

         return i64toa(id.m_i);

      }


   } // namespace str


} // namespace gen