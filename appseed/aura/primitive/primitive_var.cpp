#include "framework.h"
#include <math.h>


//IMPLEMENT_AXIS_FIXED_ALLOC_STATIC(var);


var::var(const char * psz)
{
   m_etype = type_new;
   set_string(psz);
}

var::var(::element * pelement)
{
   m_etype = type_new;
   operator = (pelement);
}

var::var(string str)
{
   m_etype = type_new;
   set_string(str);
}

var::var(string * pstr)
{
   m_etype = type_new;
   operator = (pstr);
}

var::var(bool b)
{
   m_etype = type_new;
   operator = (b);
}

var::var(bool * pb)
{
   m_etype = type_new;
   operator = (pb);
}

var::var(int32_t i)
{
   m_etype = type_new;
   operator = (i);
}

var::var(uint32_t ui )
{
   m_etype = type_uint32;
   operator = (ui);
}

var::var(int64_t i)
{
   m_etype = type_new;
   operator = (i);
}

var::var(uint64_t ui )
{
   m_etype = type_uint64;
   m_ui64 = ui;
}

#ifdef APPLEOS
#ifdef OS64BIT
var::var(long l)
{
   m_etype = type_uint64;
   m_ui64 = (uint64_t) l;
}
#endif
#endif

var::var(int32_t * pi)
{
   m_etype = type_new;
   operator = (pi);
}

var::var(uint32_t * pui)
{
   m_etype = type_new;
   operator = (pui);
}

var::var(int64_t * pi)
{
   m_etype = type_new;
   operator = (pi);
}

var::var(uint64_t * pui)
{
   m_etype = type_new;
   operator = (pui);
}

var::var(float f)
{
   m_etype = type_new;
   operator = (f);
}

var::var(double d)
{
   m_etype = type_new;
   operator = (d);
}

var::var(const stringa & var)
{
   m_etype  = type_new;
   operator = (var);
}

var::var(const int_array & ia)
{
   m_etype  = type_new;
   operator = (ia);
}

var::var(const var_array & var)
{
   m_etype  = type_new;
   operator = (var);
}

var::var(const property_set & set)
{
   m_etype  = type_new;
   operator = (set);
}

var::var(const pair_set_interface & set)
{
   m_etype  = type_new;
   operator = (set);
}

var::var(const str_str_interface & set)
{
   m_etype  = type_new;
   operator = (set);
}

var::var(const class var & var)
{
   m_etype = type_new;
   operator = (var);
}

var::var(class var * pvar)
{
   m_etype = type_new;
   operator = (pvar);
}

var::var(const property & prop)
{
   m_etype = type_new;
   operator = (prop);
}

var::var(const string_composite & composite)
{
   m_etype = type_new;
   operator = (composite);
}


var::var(const id & id)
{
   m_etype = type_new;
   operator = (id);
}


var::var(const ::duration & duration)
{

   m_etype = type_duration;
   m_duration = duration;

}


var::var(::duration * pduration)
{

   m_etype = type_pduration;
   m_pduration = pduration;

}


var::~var()
{

}

strsize var::get_length() const
{

   return get_string().get_length();

}


void var::get_string(char * psz) const
{

   strcpy(psz, get_string());

}


var::e_type var::get_type() const
{

   return m_etype;

}


class var & var::operator ++(int32_t)
{

   switch(get_type())
   {
   case type_new:
   case type_null:
   case type_stra:
   case type_inta:
   case type_empty:
   case type_element:
      set_type(type_int32);
      m_i32 = 1;
      break;
   case type_bool:
      if(!m_b)
      {
         set_type(type_int32);
         m_i32 = 1;
      }
      else
      {
         set_type(type_int32);
         m_i32 = 2;
      }
      break;
   case type_string:
      set_type(type_int32);
      m_i32 = atoi(m_str) + 1;
      break;
   case type_double:
      m_d += 1.0;
      break;
   case type_int32:
      m_i32++;
      break;
   case type_uint32:
      m_ui32++;
      break;
   default:
      set_type(type_int32, false);
      m_i32 = 1;
      break;
   }
   return *this;
}



void var::set_type(e_type e_type, bool bConvert)
{
   m_sp.release();
   if(e_type == m_etype)
      return;
   if(bConvert)
   {
      switch(e_type)
      {
      case type_int32:
         m_i32       = int32();
         break;
      case type_uint32:
         m_ui32      = uint32();
         break;
      case type_double:
         m_d         = get_double();
         break;
      case type_string:
         m_str       = get_string();
         break;
      case type_id:
         m_id        = get_id();
         break;
      default:
         break;
      }
   }
   m_etype = e_type;
}

void var::unset()
{
   set_type(type_new, false);
}

bool var::ok() const
{
   return get_type() != type_parareturn || ::is_return_ok(m_parareturn);
}

bool var::failed() const
{
   return get_type() == type_parareturn && !::is_return_ok(m_parareturn);
}

void var::set_string(const string & str)
{
   if(get_type() == type_pstring)
   {
      *m_pstr = str;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = str;
   }
   else
   {
      set_type(type_string, false);
      m_str = str;
   }
}

void var::set_id(const id & id)
{
   if(get_type() == type_pid)
   {
      *m_pid = id;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = id;
   }
   else
   {
      set_type(type_id, false);
      m_id = id;
   }
}

class var & var::operator = (para_return & eret)
{
   set_type(type_parareturn, false);
   m_parareturn = eret;
   return *this;
}

class var & var::operator = (bool b)
{
   if(get_type() == type_pbool)
   {
      *m_pb = b;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = b;
   }
   else
   {
      set_type(type_bool, false);
      m_b = b;
   }
   return *this;
}

class var & var::operator = (bool * pb)
{
   set_type(type_pbool, false);
   m_pb = pb;
   return *this;
}

class var & var::operator = (int32_t i)
{
   if(get_type() == type_pint32)
   {
      *m_pi32 = i;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = i;
   }
   else
   {
      set_type(type_int32, false);
      m_i32 = i;
   }
   return *this;
}




class var & var::operator = (int32_t * pi)
{
   set_type(type_pint32, false);
   m_pi32 = pi;
   return *this;
}

class var & var::operator = (uint32_t * pui)
{
   set_type(type_puint32, false);
   m_pui32 = pui;
   return *this;
}

class var & var::operator = (int64_t * pi)
{
   set_type(type_pint64, false);
   m_pi64 = pi;
   return *this;
}

class var & var::operator = (uint64_t * pui)
{
   set_type(type_puint64, false);
   m_pui64 = pui;
   return *this;
}

class var & var::operator = (const ::datetime::time & time)
{
   set_type(type_time, false);
   m_time = time.get_time();
   return *this;
}

class var & var::operator = (const FILETIME & filetime)
{
   set_type(type_filetime, false);
   m_filetime = filetime;
   return *this;
}

class var & var::operator = (int64_t l)
{
   if(get_type() == type_pint64)
   {
      *m_pi64 = l;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = l;
   }
   else
   {
      set_type(type_int64, false);
      m_i64 = l;
   }
   return *this;
}

class var & var::operator = (uint64_t ul)
{
   if(get_type() == type_puint64)
   {
      *m_pui64 = ul;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = ul;
   }
   else
   {
      set_type(type_uint64, false);
      m_ui64 = ul;
   }
   return *this;
}


class var & var::operator = (uint32_t ui)
{
   set_type(type_uint32, false);
   m_ui32 = ui;
   return *this;
}

class var & var::operator = (float f)
{
   set_type(type_float, false);
   m_f = f;
   return *this;
}


class var & var::operator = (double d)
{
   set_type(type_double, false);
   m_d = d;
   return *this;
}


class var & var::operator = (string str)
{
   set_string(str);
   return *this;
}

class var & var::operator = (string * pstr)
{
   set_type(type_pstring, false);
   m_pstr = pstr;
   return *this;
}

class var & var::operator = (id * pid)
{
   set_type(type_pid, false);
   m_pid = pid;
   return *this;
}

class var & var::operator = (const char * psz)
{
   set_string(psz);
   return *this;
}

class var & var::operator = (const wchar_t * lpcsz)
{
   set_string(::str::international::unicode_to_utf8(lpcsz));
   return *this;
}

class var & var::operator = (const property & prop)
{
   operator = (((property &)prop).get_value());
   return *this;
}

class var & var::operator = (const class var & var)
{
   if(m_etype == type_pvar)
   {
      if(m_pvar == &var)
         return *this;
      m_pvar->operator = (var);
      return *this;
   }
   if(&var != this)
   {
      switch(((class var &)var).get_type())
      {
      case type_pvar:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pvar;
         return *this;
      case type_pint32:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pi32;
         return *this;
      case type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pstr;
         return *this;
         default:
            break;
      }

      set_type(((class var &)var).get_type(), false);
      switch(((class var &)var).get_type())
      {
      case type_bool:
         m_b      = var.m_b;
         break;
      case type_int32:
         m_i32      = var.m_i32;
         break;
      case type_uint32:
         m_ui32      = var.m_ui32;
         break;
      case type_int64:
         m_i64    = var.m_i64;
         break;
      case type_uint64:
         m_ui64    = var.m_ui64;
         break;
      case type_float:
         m_f      = var.m_f;
         break;
      case type_double:
         m_d      = var.m_d;
         break;
      case type_string:
         m_str    = var.m_str;
         break;
      case type_memory:
         memory()   = ((class var &)var).memory();
         break;
      case type_inta:
         inta()   = *var.m_pia;
         break;
      case type_stra:
         stra()   = *var.m_pstra;
         break;
      case type_vara:
         vara()   = *var.m_pvara;
         break;
      case type_propset:
         propset()   = *var.m_pset;
         break;
      case type_prop:
         prop()   = ((class var &)var).prop();
         break;
      case type_element:
         {
            m_sp = ((class var &)var).m_sp;
         }
         break;
      case type_id:
         m_id    = var.m_id;
         break;
      default:
         break;
      }
   }
   return *this;
}

class var & var::operator = (const int_array & ia)
{
   inta() = ia;
   return *this;
}

class var & var::operator = (const class primitive::memory & memoryParam)
{
   primitive::memory() = memoryParam;
   return *this;
}


class var & var::operator = (const stringa & straParam)
{
   stra() = straParam;
   return *this;
}

class var & var::operator = (const var_array & varaParam)
{
   vara() = varaParam;
   return *this;
}

class var & var::operator = (const property_set & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

class var & var::operator = (const pair_set_interface & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

class var & var::operator = (const str_str_interface & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

var & var::operator = (const string_composite & composite)
{

   string str;
   ::count count = composite.get_length();
   char * psz = str.GetBufferSetLength(count);
   composite.get_string(psz);
   str.ReleaseBuffer(count);
   operator = (str);

   return *this;

}

class var & var::operator = (const id & id)
{

   set_id(id);
   return *this;

}

/*var::operator id &()
{
   if(get_type() == type_pvar)
      return m_pvar->operator id &();
   else if(get_type() == type_pid)
      return *m_pid;
   else if(get_type() != type_id)
      m_id = get_id();
   set_type(type_id);
   return m_id;
}


var::operator string & ()
{
   if(get_type() == type_pvar)
      return m_pvar->operator string &();
   else if(get_type() == type_pstring)
      return *m_pstr;
   else if(get_type() != type_string)
      m_str = get_string();
   set_type(type_string);
   return m_str;
}*/


class var & var::operator = (const ::duration & duration)
{


   set_type(type_duration);

   m_duration = duration;

   return *this;

}


class var & var::operator = (::duration * pduration)
{


   set_type(type_pduration);

   m_pduration = pduration;

   return *this;

}


var::operator const char *() const
{
   return get_string();
}




bool var::is_true(bool bDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return bDefault;
   case type_empty:
      return bDefault;
   case type_string:
      return !m_str.is_empty() && !m_str.CompareNoCase("false");
   case type_int32:
      return m_i32 != 0;
   case type_uint32:
      return m_ui32 != 0;
   case type_double:
      return m_d != 0;
   case type_element:
      return m_sp.is_set();
   case type_bool:
      return m_b;
   case type_pvar:
      return m_pvar->is_true(bDefault);
   default:
      return bDefault;
   }
}

bool var::is_empty() const
{
   switch(m_etype)
   {
   case type_null:
      return true;
   case type_empty:
      return true;
   case type_new:
      return true;
   case type_string:
      return m_str.is_empty();
   case type_int32:
      return m_i32 == 0;
   case type_uint32:
      return m_ui32 == 0;
   case type_double:
      return m_d == 0.0;
   case type_element:
      return m_sp.is_set();
   case type_pvar:
      return m_pvar->is_empty();
   case type_id:
      return m_id.is_empty();
   case type_pid:
      return m_pid->is_empty();
   default:
      return false;
   }
}

bool var::has_char() const
{
   return get_string().has_char();
}

bool var::is_set() const
{
   if(get_type() != type_new)
      return true;
   else
      return false;
}


bool var::is_new() const
{
   if(m_etype == type_new)
      return true;
   else
      return false;
}


bool var::is_null() const
{
   if(m_etype == type_null)
      return true;
   else
      return false;
}


bool var::is_new_or_null() const
{
   return is_new() || is_null();
}

void var::read(::file::input_stream & is)
{
   int32_t i;
   is >> i;
   set_type(e_type(i), false);
   switch(get_type())
   {
   case type_string:
      {
         strsize size;
         is >> size;
         char * lpsz = m_str.GetBuffer(size + 2);
         is.read(lpsz, (size + 1) * sizeof(CHAR));
         m_str.ReleaseBuffer();
      }
      break;
   case type_int32:
      {
         is >> m_i32;
      }
      break;
   case type_bool:
      {
         is >> m_b;
      }
      break;
   case type_new:
   case type_null:
   case type_empty:
      break;
   case type_inta:
      {
         int32_t iCount;
         is >> iCount;
         inta().allocate(iCount);
         for(int32_t i = 0; i < m_pia->get_count(); i++)
         {
            is >> (int32_t &) m_pia->element_at(i);
         }
      }
      break;
   case type_memory:
      {
         is >> memory();
      }
      break;
   case type_stra:
      {
         is >> stra();
      }
      break;
   case type_propset:
      {
         is >> propset();
      }
      break;
   case type_id:
      {
         is >> m_id;
      }
      break;
   case type_element:
      {
         sp(type) info;
         is >> info;
         m_sp = Sys(is.m_spbuffer->get_app()).alloc(info);
         if(m_sp.is_null())
         {
            throw "object allocation is not implemented";
         }
         sp(::file::serializable) pserializable = m_sp;
         if(pserializable != NULL)
         {
            pserializable->read(is);
         }
         else
         {
            throw io_exception(is.m_spbuffer->get_app(), "object serialization is not implemented");
         }
      }
      break;
   default:
      throw "WHAT!!";
   }
}

void var::write(::file::output_stream & ostream)
{
   int32_t i = get_type();
   ostream << i;
   switch(get_type())
   {
   case type_string:
      {
         strsize len = m_str.get_length();
         ostream << len;
         ostream.write((const char *) m_str, m_str.get_length() + 1);
      }
      break;
   case type_int32:
      ostream << m_i32;
      break;
   case type_bool:
      ostream << m_b;
      break;
   case type_new:
   case type_null:
   case type_empty:
      break;
   case type_inta:
      {
         ostream << inta().get_count();
         for(int32_t i = 0; i < m_pia->get_count(); i++)
         {
            ostream << m_pia->element_at(i);
         }
      }
      break;
   case type_memory:
      ostream << memory();
      break;
   case type_stra:
      ostream << stra();
      break;
   case type_propset:
      ostream << propset();
      break;
   case type_id:
      ostream << m_id;
      break;
   case type_element:
      {
         sp(type) info(Sys(ostream.m_spbuffer->get_app()).get_type_info(typeid(*m_sp.m_p)));
         ostream << info;
         sp(::file::serializable) pserializable = m_sp;
         if(pserializable != NULL)
         {
            pserializable->write(ostream);
         }
         else
         {
            throw io_exception(ostream.m_spbuffer->get_app(), "object is not serializable");
         }
      }
      break;
   default:
      throw "WHAT!!";
   }
}

int32_t var::compare_ci(const class var & var) const
{
   if(m_etype == var::type_inta)
   {
      if(var.m_etype == var::type_inta)
      {
         //var = var1.inta() - var2.inta();
      }
      else
      {
         //var = var1;
         //var.inta().remove(var2.int32());
      }
   }
   else if(m_etype == var::type_stra)
   {
      if(var.m_etype == var::type_stra)
      {
         //var = var1.stra() - var2.stra();
      }
      else
      {
         //var = var1;
         //var.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == var::type_vara)
   {
      if(var.m_etype == var::type_vara)
      {
      //   var = var1.vara() - var2.vara();
      }
      else
      {
        // var = var1;
         //var.vara().remove(var2);
      }
   }
   else if(is_double() || var.is_double())
   {
      double d = get_double() - var.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
         return -1;
   }
   else if(is_integer() || var.is_integer())
   {
      return int32() - var.int32();
   }
   else if(is_natural() || var.is_natural())
   {
      return (int32_t) (uint32() - var.uint32());
   }
   else
   {
      return get_string().CompareNoCase(var.get_string());
   }
   return -2;
}

int32_t var::compare_ci(const char * psz) const
{
   var var(psz);
   return compare_ci(var);
}


int32_t var::compare(const class var & var) const
{
   if(m_etype == var::type_inta)
   {
      if(var.m_etype == var::type_inta)
      {
         //var = var1.inta() - var2.inta();
      }
      else
      {
         //var = var1;
         //var.inta().remove(var2.int32());
      }
   }
   else if(m_etype == var::type_stra)
   {
      if(var.m_etype == var::type_stra)
      {
         //var = var1.stra() - var2.stra();
      }
      else
      {
         //var = var1;
         //var.stra().remove(var2.get_string());
      }
   }
   else if(m_etype == var::type_vara)
   {
      if(var.m_etype == var::type_vara)
      {
      //   var = var1.vara() - var2.vara();
      }
      else
      {
        // var = var1;
         //var.vara().remove(var2);
      }
   }
   else if(is_double() || var.is_double())
   {
      double d = get_double() - var.get_double();
      if(d == 0.0)
         return 0;
      else if(d > 0.0)
         return 1;
      else if(d < 0.0)
         return -1;
   }
   else if(is_integer() || var.is_integer())
   {
      return int32() - var.int32();
   }
   else if(is_natural() || var.is_natural())
   {
      return (int32_t) (uint32() - var.uint32());
   }
   else
   {
      return get_string().Compare(var.get_string());
   }
   return -2;
}

int32_t var::compare(const char * psz) const
{
   var var(psz);
   return compare(var);
}

bool var::operator == (const class var & var) const
{
   // if variables are equal:
   // all values of both variables should be equal
   return compare(var) == 0;
}

bool var::operator > (const class var & var) const
{
   return compare(var) > 0;
}

bool var::operator < (const class var & var) const
{
   return compare(var) < 0;
}

bool var::operator >= (const class var & var) const
{
   return compare(var) >= 0;
}

bool var::operator <= (const class var & var) const
{
   return compare(var) <= 0;
}

bool var::operator != (const class var & var) const
{
   return compare(var) != 0;
}

bool var::operator == (const char * psz) const
{
   return get_string() == psz;
}

bool var::operator < (const char * psz) const
{
   return get_string() < psz;
}

bool var::operator <= (const char * psz) const
{
   return get_string() <= psz;
}

bool var::operator >= (const char * psz) const
{
   return get_string() >= psz;
}

bool var::operator > (const char * psz) const
{
   return get_string() > psz;
}

bool var::operator != (const char * psz) const
{
   return get_string() != psz;
}

bool var::operator == (const string & str) const
{
   return get_string() == str;
}

bool var::operator != (const string & str) const
{
   return get_string() != str;
}

bool var::operator < (const string & str) const
{
   return get_string() < str;
}

bool var::operator <= (const string & str) const
{
   return get_string() <= str;
}

bool var::operator >= (const string & str) const
{
   return get_string() >= str;
}

bool var::operator > (const string & str) const
{
   return get_string() > str;
}

bool var::operator == (int32_t i) const
{
   return int32() == i;
}

bool var::operator != (int32_t i) const
{
   return int32() != i;
}

bool var::operator < (int32_t i) const
{
   return int32() < i;
}

bool var::operator <= (int32_t i) const
{
   return int32() <= i;
}

bool var::operator >= (int32_t i) const
{
   return int32() >= i;
}

bool var::operator > (int32_t i) const
{
   return int32() > i;
}



bool var::operator == (bool b) const
{
   return is_equivalent(get_bool(), b);
}

bool var::operator != (bool b) const
{
   return is_different(get_bool(), b);
}

bool var::operator < (bool b) const
{
   return is_lesser(get_bool(), b);
}

bool var::operator <= (bool b) const
{
   return is_lesser_or_equal(get_bool(), b);
}

bool var::operator >= (bool b) const
{
   return is_greater_or_equal(get_bool(), b);
}

bool var::operator > (bool b) const
{
   return is_greater(get_bool(), b);
}

bool var::strict_equal(const class var & var) const
{
   return m_etype == var.m_etype && operator == (var);
}

bool var::strict_equal(const char * psz) const
{
   return m_etype == type_string && m_str == psz;
}

bool var::strict_equal(const string & str) const
{
   return m_etype == type_string && m_str == str;
}

bool var::strict_equal(double d) const
{
   return m_etype == type_double && m_d == d;
}

bool var::strict_equal(int32_t i) const
{
   return m_etype == type_int32 && m_i32 == i;
}

bool var::strict_equal(bool b) const
{
   return m_etype == type_bool && is_equivalent(m_b, b);
}

bool var::strict_different(const class var & var) const
{
   return m_etype != var.m_etype || operator != (var);
}

bool var::strict_different(const char * psz) const
{
   return m_etype != type_string || m_str != psz;
}

bool var::strict_different(const string & str) const
{
   return m_etype != type_string || m_str != str;
}

bool var::strict_different(double d) const
{
   return m_etype != type_double || m_d != d;
}

bool var::strict_different(int32_t i) const
{
   return m_etype != type_int32 || m_i32 != i;
}

bool var::strict_different(bool b) const
{
   return m_etype != type_bool || is_different(m_b, b);
}

bool strict_equal(const char * psz, const class var & var)
{
   return var.m_etype == var::type_string && psz == var.m_str;
}

bool strict_equal(const string & str, const class var & var)
{
   return var.m_etype == var::type_string && str == var.m_str;
}

bool strict_equal(double d, const class var & var)
{
   return var.m_etype == var::type_double && d == var.m_d;
}

bool strict_equal(int32_t i, const class var & var)
{
   return var.m_etype == var::type_int32 && i == var.m_i32;
}

bool strict_equal(bool b, const class var & var)
{
   return var.m_etype == var::type_bool && is_equivalent(b, var.m_b);
}

bool strict_different(const char * psz, const class var & var)
{
   return var.m_etype != var::type_string || psz != var.m_str;
}

bool strict_different(const string & str, const class var & var)
{
   return var.m_etype != var::type_string || str != var.m_str;
}

bool strict_different(double d, const class var & var)
{
   return var.m_etype != var::type_double || d != var.m_d;
}

bool strict_different(int32_t i, const class var & var)
{
   return var.m_etype != var::type_int32 || i != var.m_i32;
}

bool strict_different(bool b, const class var & var)
{
   return var.m_etype != var::type_bool || is_different(b, var.m_b);
}

string var::to_r_string() const
{
   if(is_array())
   {
      string str;
      str += "array (";
      for(int32_t i = 0; i < array_get_count(); i++)
      {
         if(i > 0)
            str += " ";
         str += key(i).get_string();
         str += " => ";
         str += at(i).to_r_string();
         str += ";";
      }
      str += ")";
      return str;
   }
   else
   {
      return get_string();
   }
}

string var::get_string(const char * pszOnNull) const
{

   if(m_etype == type_pvar)
   {
      return m_pvar->get_string(pszOnNull);
   }
   else if(m_etype == type_pstring)
   {
      return *m_pstr;
   }
   else if(m_etype != type_string)
   {
      string str;

      if(m_etype == var::type_null)
      {
         str = pszOnNull;
      }
      else if(m_etype == var::type_int32)
      {
         str = ::str::from(m_i32);
      }
      else if(m_etype == var::type_uint32)
      {
         str = ::str::from( m_ui32);
      }
      else if(m_etype == var::type_int64)
      {
         str = i64toa_dup(m_i64);
      }
      else if(m_etype == var::type_uint64)
      {
         str = ::str::from(m_ui64);
      }
      else if(m_etype == var::type_double)
      {
         str = ::str::from(m_d);
      }
      else if(m_etype == var::type_id)
      {
         str = m_id;
      }
      else if(m_etype == var::type_pid)
      {
         str = *m_pid;
      }
      else if(m_etype == var::type_stra)
      {
         str = stra().implode("");
      }

      return str;

   }
   else
   {
      return m_str;
   }

}

string & var::get_ref_string(const char * pszOnNull)
{

   if(m_etype == type_string)
   {
      return m_str;
   }
   else if(m_etype == type_pvar)
   {
      return m_pvar->get_ref_string(pszOnNull);
   }
   else if(m_etype == type_pstring)
   {
      return *m_pstr;
   }
   else
   {
      m_str = get_string(pszOnNull);
      set_type(type_string, false);
      return m_str;
   }

}


id var::get_id(const char * pszOnNull) const
{
   if(m_etype == type_pvar)
   {
      return m_pvar->get_id(pszOnNull);
   }
   else if(m_etype == type_pid)
   {
      return *m_pid;
   }
   else if(m_etype != type_id)
   {

      ::id id;

      if(m_etype == var::type_null)
      {
         id = pszOnNull;
      }
      else if(m_etype == var::type_int32)
      {
         id = m_i32;
      }
      else if(m_etype == var::type_int64)
      {
         id = (int_ptr) m_i64;
      }
      else if(m_etype == var::type_uint32)
      {
         id = (int_ptr) m_ui32;
      }
      else if(m_etype == var::type_double)
      {
         string str;
         str.Format("%f", m_d);
         id = str;
      }
      else if(m_etype == var::type_string)
      {
         id = m_str;
      }
      else if(m_etype == var::type_pstring)
      {
         id = *m_pstr;
      }

      return id;

   }
   else
   {
      return m_id;
   }
}



id & var::get_ref_id(const char * pszOnNull)
{
   if(m_etype == type_pvar)
   {
      return m_pvar->get_ref_id(pszOnNull);
   }
   else if(m_etype == type_pid)
   {
      return *m_pid;
   }
   else
   {

      m_id = get_id();
      set_type(type_id, false);
      return m_id;

   }

}



int32_t var::int32(int32_t iDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return iDefault;
   case type_empty:
      return iDefault;
   case type_string:
      return atoi(m_str);
   case type_int32:
      return m_i32;
   case type_uint32:
      return (int32_t)m_ui32;
   case type_int64:
      return (int32_t) m_i64;
   case type_uint64:
      return (int32_t) m_ui64;
   case type_element:
      return iDefault;
   case type_pvar:
      return m_pvar->int32(iDefault);
   case type_pstring:
      return atoi(*m_pstr);
   case type_id:
   {
      if(!is32integer((int64_t) m_id))
         throw overflow_error(get_thread_app(), "var contains id that does not fit 32 bit integer");
      return (int32_t) (int64_t) m_id;
   }
   case type_pid:
   {
      if(!is32integer((int64_t) *m_pid))
         throw overflow_error(get_thread_app(), "var contains id that does not fit 32 bit integer");
      return (int32_t) (int64_t) *m_pid;
   }
   default:
      return iDefault;
   }
}

uint32_t var::uint32(uint32_t uiDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return uiDefault;
   case type_empty:
      return uiDefault;
   case type_string:
      return atoi(m_str);
   case type_int32:
      return m_i32;
   case type_uint32:
      return (uint32_t) m_ui32;
   case type_element:
      return uiDefault;
   case type_uint64:
      return (uint32_t) m_ui64;
   case type_pvar:
      return m_pvar->uint32(uiDefault);
   default:
      return uiDefault;
   }
}

int64_t var::int64(int64_t iDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return iDefault;
   case type_empty:
      return iDefault;
   case type_string:
      return atol(m_str);
   case type_int32:
      return m_i32;
   case type_uint32:
      return m_ui32;
   case type_int64:
      return m_i64;
   case type_uint64:
      return m_ui64;
   case type_element:
      return iDefault;
   case type_pvar:
      return m_pvar->int64(iDefault);
   default:
      return iDefault;
   }
}


uint64_t var::uint64(uint64_t uiDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return uiDefault;
   case type_empty:
      return uiDefault;
   case type_string:
      return atol(m_str);
   case type_int32:
      return m_i32;
   case type_uint32:
      return m_ui32;
   case type_element:
      return uiDefault;
   case type_pvar:
      return m_pvar->uint64(uiDefault);
   default:
      return uiDefault;
   }

}


float var::get_float(float fDefault) const
{
   switch(m_etype)
   {
   case type_null:
      return fDefault;
   case type_empty:
      return fDefault;
   case type_int32:
      return (float) m_i32;
   case type_uint32:
      return (float) m_ui32;
   case type_int64:
      return (float) m_i64;
   case type_uint64:
      return (float) m_ui64;
   case type_float:
      return m_f;
   case type_double:
      return (float) m_d;
   case type_string:
      return (float) atof(m_str);
   case type_pvar:
      return m_pvar->get_float(fDefault);
   default:
      return fDefault;
   }

}


double var::get_double(double dDefault) const
{
   double d;
   if(m_etype == type_null)
   {
      return dDefault;
   }
   else if(m_etype == type_empty)
   {
      return dDefault;
   }
   else if(m_etype == var::type_int32)
   {
      d = (double) m_i32;
   }
   else if(m_etype == var::type_uint32)
   {
      d = (double) m_ui32;
   }
   else if(m_etype == var::type_int64)
   {
      d = (double) m_i64;
   }
   else if(m_etype == var::type_uint64)
   {
      d = (double) m_ui64;
   }
   else if(m_etype == var::type_float)
   {
      d = (double) m_f;
   }
   else if(m_etype == var::type_double)
   {
      d = m_d;
   }
   else if(m_etype == var::type_string)
   {
      d = atof(m_str);
   }
   else if(m_etype == var::type_pvar)
   {
      d = m_pvar->get_double(dDefault);
   }
   else
   {
      return dDefault;
   }
   return d;
}


class primitive::memory & var::memory()
{
   if(get_type() != type_memory)
   {
      set_type(type_memory);
   }
   if(m_sp.is_null())
   {
      m_sp = canew(class primitive::memory());
   }
   return *dynamic_cast < class primitive::memory * > (m_sp.m_p);
}



stringa & var::stra()
{
   if(m_etype != type_stra)
   {
      sp(stringa) pstra = canew(stringa());
      pstra->add(*this);
      set_type(type_stra, false);
      ASSERT(m_sp.is_null());
      m_sp = pstra;
      m_pstra = pstra;
   }
   else if(m_sp.is_null())
   {
      m_pstra = canew(stringa());
      m_sp = m_pstra;
   }
   return *m_pstra;
}

int_array & var::inta()
{
   if(m_etype != type_inta)
   {
      int_array * pia =  canew(int_array());
      for(int32_t i = 0; i < array_get_count(); i++)
      {
         pia->add((int32_t) at(i));
      }
      set_type(type_inta, false);
      ASSERT(m_sp.is_null());
      m_sp = pia;
      m_pia = pia;
   }
   else if(m_sp.is_null())
   {
      m_pia = canew(int_array());
      m_sp = m_pia;
   }
   return *m_pia;
}

int64_array & var::int64a()
{
   if(m_etype != type_int64a)
   {
      int64_array * pia =  canew(int64_array());
      for(index i = 0; i < array_get_count(); i++)
      {
         pia->add(at(i).operator int64_t());
      }
      set_type(type_int64a, false);
      ASSERT(m_sp.is_null());
      m_sp = pia;
      m_pia64 = pia;
   }
   else if(m_sp.is_null())
   {
      m_pia64 = canew(int64_array());
      m_sp = m_pia64;
   }
   return *dynamic_cast < int64_array * > (m_sp.m_p);
}

duration & var::duration()
{

   if (m_etype == type_duration)
   {

      return m_duration;

   }
   else if (m_etype == type_pduration)
   {

      return *m_pduration;

   }
   else
   {

      set_type(type_duration);

      m_duration.set_null();

      return m_duration;

   }

}


const class primitive::memory & var::memory() const
{
   if(get_type() != type_memory)
   {
      throw 0;
   }
   return *dynamic_cast < const class primitive::memory * > (m_sp.m_p);
}


const stringa & var::stra() const
{

   return ((var *)this)->stra();

}


const int_array & var::inta() const
{

   return ((var *)this)->inta();

}

const int64_array & var::int64a() const
{

   return ((var *)this)->int64a();

}


class var & var::operator = (var * pvar)
{
   if(m_pvar == pvar)
      return *this;
   set_type(type_pvar, false);
   m_pvar = pvar;
   return *this;
}


var_array & var::vara()
{
   if(m_etype == type_pvar)
   {
      return m_pvar->vara();
   }
   else if(m_etype != type_vara)
   {
      var_array * pvara =  canew(var_array());
      for(int32_t i = 0; i < array_get_count(); i++)
      {
         pvara->add(at(i));
      }
      set_type(type_vara, false);
      ASSERT(m_sp.is_null());
      m_sp = pvara;
      m_pvara = pvara;
   }
   else if(m_sp.is_null())
   {
      m_pvara = canew(var_array());
      m_sp = m_pvara;
   }
   return *m_pvara;
}


const var_array & var::vara() const
{

   return ((var *)this)->vara();

}


const ::duration & var::duration() const
{

   return ((var *)this)->duration();

}


property_set & var::propset(sp(::aura::application) papp)
{
   sp(property_set) pset;
   if(m_etype == type_pvar)
   {
      pset = &m_pvar->propset();
   }
   else if(m_etype != type_propset)
   {
      pset = canew(property_set());
      for(int32_t i = 0; i < array_get_count(); i++)
      {
         pset->add(id(), at(i));
      }
      set_type(type_propset, false);
      //ASSERT(m_sp.is_null());
      m_sp = pset;
      m_pset = pset;
   }
   else if(m_sp.is_null())
   {
      pset = canew(property_set());
      m_sp = pset;
      m_pset = pset;
   }
   else
   {
      pset = m_pset;
   }
   if(pset != NULL && papp != NULL)
   {
      pset->set_app(papp);
   }
   return *pset;
}


const property_set & var::propset() const
{

   return ((var *)this)->propset();

}


property & var::prop()
{
   if(m_etype != type_prop)
   {
      set_type(type_prop);
   }
   if(m_sp.is_null())
   {
      m_pprop = canew(property());
      m_sp = m_pprop;
   }
   return *dynamic_cast < property * > (m_sp.m_p);
}


const property & var::prop() const
{

   return ((var *)this)->prop();

}


string var::implode(const char * pszGlue) const
{
   if(get_type() == type_propset)
   {
      return propset().implode(pszGlue);
   }
   else if(get_type() == type_vara)
   {
      return vara().implode(pszGlue);
   }
   else if(get_type() == type_stra)
   {
      return stra().implode(pszGlue);
   }
   return "";
}


var var::explode(const char * pszGlue, bool bAddEmpty) const
{

   class var var;

   var.stra().add_tokens(get_string(), pszGlue, bAddEmpty);

   return var;

}

var var::key(index i) const
{
   switch(m_etype)
   {
   case type_inta:
      return i;
   case type_stra:
      return i;
   case type_vara:
      return i;
   case type_propset:
      return m_pset->m_propertya[i].name();
   default:
      throw "not supported";
   }
}




::comparison::var_strict var::strict_compare() const
{
   return *this;
}

var var::dereference()
{
   if(get_type() == type_pvar)
      return m_pvar->dereference();
   else if(get_type() == type_pstring)
      return *m_pstr;
   else if(get_type() == type_pint32)
      return *m_pi32;
   else if(get_type() == type_pbool)
      return *m_pb;
   else
      return *this;
}

var var::at(index i) const
{
   switch(m_etype)
   {
   case type_inta:
      return m_pia->element_at(i);
   case type_stra:
      return m_pstra->element_at(i);
   case type_vara:
      return m_pvara->element_at(i);
   case type_propset:
      return m_pset->m_propertya[i];
   case type_pvar:
      return m_pvar->at(i);
   default:
      if(i == 0)
      {
         return *this;
      }
      else
      {
         throw "index out of bounds";
      }
   }
}

var var::at(index i)
{
   switch(m_etype)
   {
   case type_inta:
      return &m_pia->element_at(i);
   case type_stra:
      return &m_pstra->element_at(i);
   case type_vara:
      return &m_pvara->element_at(i);
   case type_propset:
      return &m_pset->m_propertya[i].get_value();
   case type_pvar:
      return m_pvar->at(i);
   default:
      if(i == 0)
      {
         return this;
      }
      else
      {
         throw "index out of bounds";
      }
   }
}



bool var::array_contains(const char * psz, index find, ::count count) const
{
   switch(m_etype)
   {
   case type_inta:
      return inta().contains(atoi(psz), find, count);
   case type_stra:
      return stra().contains(psz, find, count);
   case type_vara:
      return vara().contains(psz, find, count);
   case type_propset:
      return propset().contains_value(psz, find, count);
   default:
      {
         index upperbound = MIN(array_get_upper_bound(), find + count - 1);
         for(index i = find; i <= upperbound; i++)
         {
            if(at(i) == psz)
            {
               return true;
            }
         }
      }
   }
   return false;
}

bool var::array_contains_ci(const char * psz, index find, index last) const
{
   switch(m_etype)
   {
   case type_bool:
      return false;
   case type_inta:
      return inta().contains(atoi(psz), find, last);
   case type_stra:
      return stra().contains_ci(psz, find, last);
   case type_vara:
      return vara().contains_ci(psz, find, last);
   case type_propset:
      return propset().contains_value_ci(psz, find, last);
   default:
      {
         index upperbound = MIN(array_get_upper_bound(), last);
         for(index i = find; i <= upperbound; i++)
         {
            if(at(i).get_string().CompareNoCase(psz) == 0)
            {
               return true;
            }
         }
      }
   }
   return false;
}


var var::equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const
{
   if(compare_ci(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return varOnDifferent;
   }
}

var var::equals_ci_get(const char * pszCompare, var varOnEqual) const
{
   if(compare_ci(pszCompare) == 0)
   {
      return varOnEqual;
   }
   else
   {
      return var();
   }
}


var var::operator - (int32_t i) const
{
   return int32() - i;
}

var var::operator - (uint32_t user) const
{
   return uint32() - user;
}

var var::operator - (int64_t l) const
{
   return int64() - l;
}

var var::operator - (uint64_t ul) const
{
   return (int64_t) (uint64() - ul);
}

var var::operator - (double d) const
{
   return get_double() - d;
}

var operator - (int32_t i, const class var & var)
{
   return i - var.int32();
}

var operator - (uint32_t user, const class var & var)
{
   return user - var.uint32();
}

var operator - (int64_t l, const class var & var)
{
   return l - var.int64();
}

var operator - (uint64_t ul, const class var & var)
{
   return (int64_t) (ul - var.uint64());
}

var operator - (double d, const class var & var)
{
   return d - var.get_double();
}

var operator - (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == var::type_inta)
   {
      if(var2.m_etype == var::type_inta)
      {
         var = var1.inta() - var2.inta();
      }
      else
      {
         var = var1;
         var.inta().remove(var2.int32());
      }
   }
   else if(var1.m_etype == var::type_stra)
   {
      if(var2.m_etype == var::type_stra)
      {
         var = var1.stra() - var2.stra();
      }
      else if(var2.is_array())
      {
         var = var1.stra() - const_cast < class var & > (var2).stra();
      }
      else
      {
         var = var1;
         var.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == var::type_vara)
   {
      if(var2.m_etype == var::type_vara)
      {
         var = var1.vara() - var2.vara();
      }
      else
      {
         var = var1;
         var.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      var = var1.get_double() - var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      var = var1.int32() - var2.int32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      var = var1.uint32() - var2.uint32();
   }
   else
   {
      var = atoi(var1.get_string()) - atoi(var2.get_string());
   }
   return var;
}


var var::operator + (int32_t i) const
{
   return int32() + i;
}

var var::operator + (uint32_t user) const
{
   return uint32() + user;
}

var var::operator + (int64_t l) const
{
   return int64() + l;
}

var var::operator + (uint64_t ul) const
{
   return (uint32_t) (uint64() + ul);
}

var var::operator + (double d) const
{
   return get_double() + d;
}

var operator + (int32_t i, const class var & var)
{
   return i + var.int32();
}

var operator + (uint32_t user, const class var & var)
{
   return user + var.uint32();
}

var operator + (int64_t l, const class var & var)
{
   return l + var.int64();
}

var operator + (uint64_t ul, const class var & var)
{
   return (uint32_t) (ul + var.uint64());
}

var operator + (double d, const class var & var)
{
   return d + var.get_double();
}

var operator + (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == var::type_inta
   || var1.m_etype == var::type_inta)
   {
      if(var1.m_etype == var::type_inta)
      {
         if(var2.m_etype == var::type_inta)
         {
            var = var1.inta() + var2.inta();
         }
         else
         {
            var = var1;
            var.inta().add(var2.int32());
         }
      }
      else
      {
         var = var2;
         var.inta().add(var1.int32());
      }
   }
   else if(var1.m_etype == var::type_stra
   || var2.m_etype == var::type_stra)
   {
      if(var1.m_etype == var::type_stra)
      {
         if(var2.m_etype == var::type_stra)
         {
            var = var1.stra() + var2.stra();
         }
         else
         {
            var = var1;
            var.stra().add(var2.get_string());
         }
      }
      else
      {
         var = var2;
         var.stra().add(var1.get_string());
      }
   }
   else if(var1.m_etype == var::type_vara
   || var2.m_etype == var::type_vara)
   {
      if(var2.m_etype == var::type_vara)
      {
         if(var2.m_etype == var::type_vara)
         {
            var = var1.vara() + var2.vara();
         }
         else
         {
            var = var1;
            var.vara().add(var2);
         }
      }
      else
      {
         var = var2;
         var.vara().add(var1);
      }
   }
   else if(var1.is_double() && var2.is_double())
   {
      var = var1.get_double() + var2.get_double();
   }
   else if(var1.is_integer() && var2.is_integer())
   {
      var = var1.int32() + var2.int32();
   }
   else if(var1.is_natural() && var2.is_natural())
   {
      var = var1.uint32() + var2.uint32();
   }
   else
   {
      var = var1.get_string() + var2.get_string();
   }
   return var;
}






















var var::operator / (int32_t i) const
{
   return int32() / i;
}

var var::operator / (uint32_t user) const
{
   return uint32() / user;
}

var var::operator / (int64_t l) const
{
   return int64() / l;
}

var var::operator / (uint64_t ul) const
{

   switch(m_etype)
   {
   case ::var::type_null:
      return var(type_null);
   case ::var::type_empty:
      return 0.0 / ul; // throws division by zero exception if ul is zero
   case ::var::type_int32:
      return m_i32 / (int_ptr) ul;
   case ::var::type_uint32:
      return m_ui32 / (uint_ptr) ul;
   case ::var::type_int64:
      return m_i64 / (int64_t) ul;
   case ::var::type_uint64:
      return m_ui64 / (uint64_t) ul;
   case ::var::type_float:
      return m_f / (float) ul;
   case ::var::type_double:
      return m_d / (double) ul;
   case ::var::type_string:
      return atof(m_str) / (double) ul;
   case ::var::type_pvar:
      return m_pvar->operator / (ul);
   default:
      return 0.0 / ul; // throws division by zero exception if ul is zero
   }

}

var var::operator / (double d) const
{
   return get_double() / d;
}

var operator / (int32_t i, const class var & var)
{
   return i / var.int32();
}

var operator / (uint32_t user, const class var & var)
{
   return user / var.uint32();
}

var operator / (int64_t l, const class var & var)
{
   return l / var.int64();
}

var operator / (uint64_t ul, const class var & var)
{
   switch(var.m_etype)
   {
   case ::var::type_null:
      throw simple_exception(get_thread_app(), "division by zero");
   case ::var::type_empty:
      throw simple_exception(get_thread_app(), "division by zero");
   case ::var::type_int32:
      return (int_ptr) ul / var.m_i32;
   case ::var::type_uint32:
      return (uint_ptr) ul / var.m_ui32;
   case ::var::type_int64:
      return (int64_t) ul / var.m_i64;
   case ::var::type_uint64:
      return (uint64_t) ul / var.m_ui64;
   case ::var::type_float:
      return (float) ul / var.m_f;
   case ::var::type_double:
      return (double) ul / var.m_d;
   case ::var::type_string:
      return (double) ul / atof(var.m_str);
   case ::var::type_pvar:
      return operator / (ul, *var.m_pvar);
   default:
      throw simple_exception(get_thread_app(), "division by zero");
   }

}


var operator / (double d, const class var & var)
{
   return d / var.get_double();
}

var operator / (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == var::type_inta)
   {
      if(var2.m_etype == var::type_inta)
      {
         var = var1;
         var.inta().intersect(var2.inta());
      }
      else
      {
         var = var1;
         var.inta().divide(var2.int32());
      }
   }
   else if(var1.m_etype == var::type_stra)
   {
      if(var2.m_etype == var::type_stra)
      {
         //var = var1.stra().intersect(var2.stra());
      }
      else
      {
         var = var1;
         var.stra().remove(var2.get_string());
      }
   }
   else if(var1.m_etype == var::type_vara)
   {
      if(var2.m_etype == var::type_vara)
      {
         //var = var1.vara() / var2.vara();
      }
      else
      {
         var = var1;
         var.vara().remove(var2);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      var = var1.get_double() / var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      var = var1.int32() / var2.int32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      var = var1.uint32() / var2.uint32();
   }
   else
   {
      var = atoi(var1.get_string()) / atoi(var2.get_string());
   }
   return var;
}


var var::operator * (int32_t i) const
{
   return int32() * i;
}

var var::operator * (uint32_t user) const
{
   return uint32() * user;
}

var var::operator * (int64_t l) const
{
   return int64() * l;
}

var var::operator * (uint64_t ul) const
{
   switch(m_etype)
   {
   case ::var::type_null:
      return var(type_null);
   case ::var::type_empty:
      return 0.0;
   case ::var::type_int32:
      return m_i32 * (int_ptr) ul;
   case ::var::type_uint32:
      return m_ui32 * (uint_ptr) ul;
   case ::var::type_int64:
      return m_i64 * (int64_t) ul;
   case ::var::type_uint64:
      return m_ui64 * (uint64_t) ul;
   case ::var::type_float:
      return m_f * (float) ul;
   case ::var::type_double:
      return m_d * (double) ul;
   case ::var::type_string:
      return atof(m_str) * (double) ul;
   case ::var::type_pvar:
      return m_pvar->operator * (ul);
   default:
      return 0.0;
   }

}

var var::operator * (double d) const
{
   return get_double() * d;
}

var operator * (int32_t i, const class var & var)
{
   return i * var.int32();
}

var operator * (uint32_t user, const class var & var)
{
   return user * var.uint32();
}

var operator * (int64_t l, const class var & var)
{
   return l * var.int64();
}

var operator * (uint64_t ul, const class var & var)
{

   switch(var.m_etype)
   {
   case ::var::type_null:
      return ::var(::var::type_null);
   case ::var::type_empty:
      return 0;
   case ::var::type_int32:
      return (int_ptr) ul * var.m_i32;
   case ::var::type_uint32:
      return (uint_ptr) ul * var.m_ui32;
   case ::var::type_int64:
      return (int64_t) ul * var.m_i64;
   case ::var::type_uint64:
      return (uint64_t) ul * var.m_ui64;
   case ::var::type_float:
      return (float) ul * var.m_f;
   case ::var::type_double:
      return (double) ul * var.m_d;
   case ::var::type_string:
      return (double) ul * atof(var.m_str);
   case ::var::type_pvar:
      return operator * (ul, *var.m_pvar);
   default:
      return 0;
   }

}


var operator * (double d, const class var & var)
{
   return d * var.get_double();
}

var operator * (const class var & var1, const class var & var2)
{
   var var;
   if(var1.m_etype == var::type_inta
   || var1.m_etype == var::type_inta)
   {
      if(var1.m_etype == var::type_inta)
      {
         if(var2.m_etype == var::type_inta)
         {
           // var = var1.inta().merge(var2.inta());
         }
         else
         {
            var = var1;
            var.inta().add(var2.int32());
         }
      }
      else
      {
         var = var2;
         var.inta().add(var1.int32());
      }
   }
   else if(var1.m_etype == var::type_stra
   || var2.m_etype == var::type_stra)
   {
      if(var1.m_etype == var::type_stra)
      {
         if(var2.m_etype == var::type_stra)
         {
//            var = var1.stra() * var2.stra();
         }
         else
         {
            var = var1;
            var.stra().add(var2.get_string());
         }
      }
      else
      {
         var = var2;
         var.stra().add(var1.get_string());
      }
   }
   else if(var1.m_etype == var::type_vara
   || var2.m_etype == var::type_vara)
   {
      if(var2.m_etype == var::type_vara)
      {
         if(var2.m_etype == var::type_vara)
         {
            //var = var1.vara().merge(var2.vara());
         }
         else
         {
            var = var1;
            var.vara().add(var2);
         }
      }
      else
      {
         var = var2;
         var.vara().add(var1);
      }
   }
   else if(var1.is_double() || var2.is_double())
   {
      var = var1.get_double() * var2.get_double();
   }
   else if(var1.is_integer() || var2.is_integer())
   {
      var = var1.int32() * var2.int32();
   }
   else if(var1.is_natural() || var2.is_natural())
   {
      var = var1.uint32() * var2.uint32();
   }
   else
   {
      var = var1.get_string() * var2.get_string();
   }
   return var;
}

























class var & var::operator -= (int32_t i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (uint32_t user)
{
   operator =(*this - user);
   return *this;
}

class var & var::operator -= (int64_t i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (uint64_t user)
{
   operator =(*this - user);
   return *this;
}

class var & var::operator -= (double d)
{
   operator =(*this - d);
   return *this;
}

class var & var::operator -= (const class var & var)
{
   operator =(*this - var);
   return *this;
}
























class var & var::operator += (int32_t i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (uint32_t user)
{
   operator =(*this + user);
   return *this;
}

class var & var::operator += (int64_t i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (uint64_t user)
{
   operator =(*this + user);
   return *this;
}

class var & var::operator += (double d)
{
   operator =(*this + d);
   return *this;
}

class var & var::operator += (const class var & var)
{
   operator =(*this + var);
   return *this;
}
























class var & var::operator /= (int32_t i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (uint32_t user)
{
   operator =(*this / user);
   return *this;
}

class var & var::operator /= (int64_t i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (uint64_t user)
{
   operator =(*this / user);
   return *this;
}

class var & var::operator /= (double d)
{
   operator =(*this / d);
   return *this;
}

class var & var::operator /= (const class var & var)
{
   operator =(*this / var);
   return *this;
}
























class var & var::operator *= (int32_t i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (uint32_t user)
{
   operator =(*this * user);
   return *this;
}

class var & var::operator *= (int64_t i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (uint64_t user)
{
   operator =(*this * user);
   return *this;
}

class var & var::operator *= (double d)
{
   operator =(*this * d);
   return *this;
}

class var & var::operator *= (const class var & var)
{
   operator =(*this * var);
   return *this;
}


























bool var::is_scalar() const
{
   if(m_etype == type_new
   || m_etype == type_null
   || m_etype == type_empty)
   {
      return false;
   }
   else if(m_etype == type_string
   || m_etype == type_int32
   || m_etype == type_pint32
   || m_etype == type_uint32
   || m_etype == type_bool
   || m_etype == type_double)
   {
      return true;
   }
   else if(m_etype == type_stra
      || m_etype == type_inta
      || m_etype == type_vara
      || m_etype == type_propset)
   {
      return false;
   }
   else if(m_etype == type_prop)
   {
      return prop().get_value().is_scalar();
   }
   else if(m_etype == type_element)
   {
      return false;
   }
   else
   {
      return false;
   }
}

bool var::is_real() const
{
   if(m_etype == type_double || m_etype == type_float)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
      if(is_scalar()
      && (fmod(atof(str), 1.0) == 0.0
      && abs(atof(str)) <= pow(2.0, 31.0)))
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
            || str[0] == '-'
            || isdigit(str[0]))
         {
            int32_t i;
            for(i = 1; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(isspace(str[i]))
               {
                  i++;
                  goto sp1;
               }
               if(str[i] == 'e' || str[i] == 'E')
               {
                  i++;
                  goto e;
               }
               return false;
            }
dot1:
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(isdigit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }

}


bool var::is_double() const
{
   if(m_etype == type_double)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
      if(is_scalar()
      && (fmod(atof(str), 1.0) == 0.0
      && abs(atof(str)) <= pow(2.0, 31.0)))
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
            || str[0] == '-'
            || isdigit(str[0]))
         {
            int32_t i;
            for(i = 1; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot1;
               }
               if(isspace(str[i]))
               {
                  i++;
                  goto sp1;
               }
               if(str[i] == 'e' || str[i] == 'E')
               {
                  i++;
                  goto e;
               }
               return false;
            }
dot1:
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
sp1:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == 'e' || str[i] == 'E')
                  goto e;
               return false;
            }
e:
//sp2:
            for(; i < str.get_length(); i++)
            {
               if(isspace(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               if(isdigit(str[i]))
               {
                  i++;
                  break;
               }
               return false;
            }
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               if(str[i] == '.')
               {
                  i++;
                  goto dot2;
               }
               return false;
            }
dot2:
            for(; i < str.get_length(); i++)
            {
               if(isdigit(str[i]))
                  continue;
               return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }

}

bool var::is_integer() const
{
   if(m_etype == type_int32 || m_etype == type_int64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
      if(is_scalar()
      && (fmod(atof(str), 1.0) == 0.0
      && abs(atof(str)) <= pow(2.0, 31.0)))
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
            || str[0] == '-'
            || isdigit(str[0]))
         {
            for(index i = 1; i < str.get_length(); i++)
            {
               if(!isdigit(str[i]))
                  return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }
}

bool var::is_natural() const
{
   if(m_etype == type_uint32 || m_etype == type_uint64)
   {
      return true;
   }
   // simple, lazy, slow, and a bit incorrect
   // incorrect because atof and atoi returns partials results even if it
   // encounters non-numerical symbols
   else
   {
      string str = get_string();
      if(is_scalar()
      && (fmod(atof(str), 1.0) == 0.0
      && abs(atof(str)) <= pow(2.0, 31.0)))
      {
         str.trim();
         if(str.get_length() == 0)
            return false;
         else if(str[0] == '+'
            || isdigit(str[0]))
         {
            for(index i = 1; i < str.get_length(); i++)
            {
               if(!isdigit(str[i]))
                  return false;
            }
            return true;
         }
         else
            return false;
      }
      else
      {
         return false;
      }
   }
}

bool var::has_property(const char * pszName) const
{
   if(get_type() == type_propset)
   {
      return dynamic_cast < const property_set * > (m_sp.m_p)->has_property(pszName);
   }
   else if(get_type() == type_pvar)
   {
      return m_pvar->has_property(pszName);
   }
   else if(get_type() == type_element)
   {
      if(cast < property_set >() != NULL)
      {
         return cast < property_set >()->has_property(pszName);
      }
      else if(cast < property >() != NULL)
      {
         return cast < property >()->name().CompareNoCase(pszName) == 0;
      }
      else
      {
         return false;
      }
   }
   else
   {
      return false;
   }
}









void var::consume_identifier(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void var::consume_identifier(const char * & psz, const char * pszEnd)
{
   const char * pszParse = psz;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const char * pszStart = pszParse;
   while (isalpha_dup(*pszParse) && pszParse <= pszEnd)
      pszParse++;
   string str(pszStart, pszParse - pszStart);
   if (str.CompareNoCase("false") == 0)
   {
      operator = (false);
   }
   else if (str.CompareNoCase("true") == 0)
   {
      operator = (true);
   }
   else if (str.CompareNoCase("NULL") == 0)
   {
      set_type(var::type_null);
   }
   else
   {
      throw "not expected identifier";
   }
   psz = pszParse;
}



void var::consume_number(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void var::consume_number(const char * & psz, const char * pszEnd)
{
   const char * pszParse = psz;
   bool bSigned = false;
   bool bFloat = false;
   ::str::consume_spaces(pszParse, 0, pszEnd);
   const char * pszStart = pszParse;
   if(*pszParse == '-')
   {
      bSigned = true;
      pszParse++;
   }
   if(*pszParse == '.')
   {
      bFloat = true;
      pszParse++;
   }
   while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if(*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      bFloat = true;
      if(*pszParse == '-')
      {
         bSigned = true;
         pszParse++;
      }
      if(*pszParse == '.')
      {
         bFloat = true;
         pszParse++;
      }
      while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }
   if(*pszParse == '.')
   {
      bFloat = true;
      pszParse++;
   }
   while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
   {
      pszParse++;
   }
   if(*pszParse == 'e' || *pszParse == 'E')
   {
      pszParse++;
      bFloat = true;
      if(*pszParse == '-')
      {
         bSigned = true;
         pszParse++;
      }
      if(*pszParse == '.')
      {
         bFloat = true;
         pszParse++;
      }
      while(*pszParse != '\0' && *pszParse >= '0' && *pszParse <= '9')
      {
         pszParse++;
      }
      goto end;
   }
end:
   if(pszParse == pszStart)
   {
      throw "empty string : not a number";
   }
   if(bFloat)
   {
      operator = (atof(string(pszStart, pszParse - pszStart)));
   }
   else
   {
      operator = (atoi(string(pszStart, pszParse - pszStart)));
   }
   psz = pszParse;
}

void var::parse_json(const char * & pszJson)
{
   parse_json(pszJson, pszJson + strlen(pszJson) - 1);
}

void var::parse_json(const char * & pszJson, const char * pszEnd)
{
   ::str::consume_spaces(pszJson, 0, pszEnd);
   if(*pszJson == '{')
   {
      propset().parse_json(pszJson, pszEnd);
   }
   else if(*pszJson == '\"')
   {
      operator = (::str::consume_quoted_value(pszJson, pszEnd));
   }
   else if(isdigit(*pszJson) || *pszJson == '-'  || *pszJson == '.')
   {
      consume_number(pszJson, pszEnd);
   }
   else if(*pszJson == '[')
   {
      vara().parse_json(pszJson, pszEnd);
   }
   else
   {
      consume_identifier(pszJson, pszEnd);
   }
}



bool var::is_numeric() const
{

   switch(get_type())
   {
      case type_parareturn:
      case type_new:
      case type_null:
      case type_empty:
      case type_empty_argument:
         return false;

      case type_string: // may be improved MBI
         return false;

      case type_pstring: // may be improved MBI
         return false;

      case type_int32:
      case type_pint32:
      case type_uint32:
         return true;

      case type_pvar:
         return m_pvar->is_numeric();

      case type_element:
         return false;

      case type_bool:
      case type_pbool:
         return false;

      case type_double:
         return true;

      case type_stra:
      case type_inta:
      case type_vara:
      case type_propset:
      case type_prop:
      case type_memory:
         return false;

      case type_int64:
      case type_pint64:
      case type_uint64:
      case type_puint64:
         return true;

      case type_time:
      case type_filetime:
         return false;

      case type_id:
         return false; // m_id.is_number(); // may be improved MBI

      case type_pid:
         return false; // m_pid->is_number(); // may be improved MBI

      case type_int64a:
         return false;

      default:
         throw not_implemented(get_thread_app());

   };

}



bool is_return_ok(para_return eret)
{
   return ((int32_t)eret) >= 0;
}


var str_ends_get(const char * lpcsz, const char * lpcszSuffix)
{

   string str(lpcsz);

   string strSuffix(lpcszSuffix);

   strsize iLen = strSuffix.get_length();

   if(str.Right(iLen) == lpcszSuffix)
   {

      return str.Left(str.get_length() - iLen);

   }

   return false;

}








string var::get_json()
{

   if (get_type() == var::type_propset)
   {

      return propset().get_json();

   }
   else if (get_type() == var::type_stra)
   {

      return stra().get_json();

   }
   else if (get_type() == var::type_inta)
   {

      return inta().get_json();

   }
   else if (get_type() == var::type_int64a)
   {

      return int64a().get_json();

   }
   else if (get_type() == var::type_vara)
   {

      return vara().get_json();

   }
   else if (is_numeric())
   {

      return get_string();

   }
   else
   {

      return "\"" + get_string() + "\"";

   }

}



void var::null()
{

    set_type(var::type_null);

}
