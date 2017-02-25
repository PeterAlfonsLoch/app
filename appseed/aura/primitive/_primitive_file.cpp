#include "framework.h"


#include "aura/filestream.h"


#include "aura/primitive/collection_file.h"

#include "aura/primitive/collection/collection_stringl.h"


#include "primitive.h"





CLASS_DECL_AURA::file::ostream & operator << (::file::ostream & ostream, const property & prop)
{

   ostream << prop.m_element1;

   ostream << prop.m_element2;

   return ostream;

}


CLASS_DECL_AURA::file::istream & operator >> (::file::istream & istream, property & prop)
{

   istream >> prop.m_element1;

   istream >> prop.m_element2;

   return istream;

}


CLASS_DECL_AURA::file::ostream & operator << (::file::ostream & ostream, const var & var)
{
   int32_t i = var.get_type();
   ostream << i;
   switch (var.get_type())
   {
   case var::type_string:
   {
      strsize len = var.m_str.get_length();
      ostream << len;
      ostream.write((const char *)var.m_str, var.m_str.get_length() + 1);
   }
   break;
   case var::type_pstring:
   {
      strsize len = var.m_pstr->get_length();
      ostream << len;
      ostream.write((const char *)*var.m_pstr, var.m_pstr->get_length() + 1);
   }
   break;
   case var::type_int32:
      ostream << var.m_i32;
      break;
   case var::type_int64:
      ostream << var.m_i64;
      break;
   case var::type_uint64:
      ostream << var.m_ui64;
      break;
   case var::type_double:
      ostream << var.m_d;
      break;
   case var::type_bool:
      ostream << var.m_b;
      break;
   case var::type_new:
   case var::type_null:
   case var::type_empty:
      break;
   case var::type_inta:
   {
      ostream << var.inta().get_count();
      for (int32_t i = 0; i < var.m_pia->get_count(); i++)
      {
         ostream << var.m_pia->element_at(i);
      }
   }
   break;
   case var::type_memory:
      ostream << var.memory();
      break;
   case var::type_stra:
      ostream << var.stra();
      break;
   case var::type_propset:
      ostream << var.propset();
      break;
   case var::type_id:
      ostream << var.m_id;
      break;
   case var::type_element:
   {
      sp(type) info(Sys(ostream.file()->get_app()).get_type_info(typeid(*var.m_sp.m_p)));
      ostream << info;

      ::file::serializable * pserializable = var.m_sp.cast < ::file::serializable >();

      if (pserializable != NULL)
      {
         pserializable->write(ostream);
      }
      else
      {
         throw io_exception(ostream.file()->get_app(), "object is not serializable");
      }
   }
   break;
   default:
      throw simple_exception(::get_thread_app(), "var::write var type not recognized");
   }

   return ostream;

}


CLASS_DECL_AURA::file::istream & operator >> (::file::istream & is, var & var)
{

   int32_t i;
   is >> i;
   var.set_type(var::e_type(i), false);
   switch (var.get_type())
   {
   case var::type_pstring:
      var.set_type(var::type_string, false);
   case var::type_string:
   {
      strsize size;
      is >> size;
      char * lpsz = var.m_str.GetBuffer(size + 2);
      is.read(lpsz, (size + 1) * sizeof(CHAR));
      var.m_str.ReleaseBuffer();
   }
   break;
   case var::type_int32:
   {
      is >> var.m_i32;
   }
   break;
   case var::type_int64:
   {
      is >> var.m_i64;
   }
   break;
   case var::type_bool:
   {
      is >> var.m_b;
   }
   break;
   case var::type_double:
   {
      is >> var.m_d;
   }
   break;
   case var::type_new:
   case var::type_null:
   case var::type_empty:
      break;
   case var::type_inta:
   {
      int32_t iCount;
      is >> iCount;
      var.inta().allocate(iCount);
      for (int32_t i = 0; i < var.m_pia->get_count(); i++)
      {
         is >> (int32_t &)var.m_pia->element_at(i);
      }
   }
   break;
   case var::type_memory:
   {
      is >> var.memory();
   }
   break;
   case var::type_stra:
   {
      is >> var.stra();
   }
   break;
   case var::type_propset:
   {
      is >> var.propset();
   }
   break;
   case var::type_id:
   {
      is >> var.m_id;
   }
   break;
   case var::type_element:
   {
      sp(type) info;
      is >> info;
      var.m_sp = Sys(is.file()->get_app()).alloc(info);
      if (var.m_sp.is_null())
      {
         throw "object allocation is not implemented";
      }
      ::file::serializable * pserializable = var.m_sp.cast < ::file::serializable >();
      if (pserializable != NULL)
      {
         pserializable->read(is);
      }
      else
      {
         throw io_exception(is.file()->get_app(), "object serialization is not implemented");
      }
   }
   break;
   default:
      is.setstate(::file::failbit); // stream corrupt
      break;
   }

   return is;

}




CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & ostream, const stringl & strl)
{
   ostream << strl.get_count();
   POSITION pos = strl.get_head_position();
   for (int32_t i = 0; i < strl.get_count(); i++)
   {
      ostream << strl.get_next(pos);
   }
   return ostream;
}


CLASS_DECL_AURA ::file::istream & operator >> (::file::istream & istream, stringl & strl)
{
   int32_t iSize;
   istream >> iSize;
   string str;
   for (int32_t i = 0; i < iSize; i++)
   {
      istream >> str;
      strl.add_tail(str);
   }
   return istream;
}








CLASS_DECL_AURA::file::ostream & operator << (::file::ostream & ostream, const string & str)
{

   ostream.write(str);

   return ostream;

}

CLASS_DECL_AURA::file::istream & operator >> (::file::istream & istream, string & str)
{


   istream.read(str);

   return istream;


}
