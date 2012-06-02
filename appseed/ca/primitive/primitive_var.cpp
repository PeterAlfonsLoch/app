#include "framework.h"


var::var(const char * psz)
{
   m_etype = type_new;
   m_pca2 = NULL;
   set_string(psz);
}

var::var(::ca::ca * pca2)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pca2);
}

var::var(string str)
{
   m_etype = type_new;
   m_pca2 = NULL;
   set_string(str);
}

var::var(string * pstr)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pstr);
}

var::var(bool b)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (b);
}

var::var(bool * pb)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pb);
}

var::var(int i)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (i);
}

var::var(int64_t i)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (i);
}

var::var(unsigned int ui )
{
   m_etype = type_uint;
   m_pca2 = NULL;
   operator = (ui);
}

var::var(int * pi)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pi);
}

var::var(int64_t * pi)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pi);
}

var::var(double d)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (d);
}

#ifdef WINDOWS

var::var(unsigned long ul)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (ul);
}

#endif

var::var(const stringa & var)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (var);
}

var::var(const int_array & ia)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (ia);
}

var::var(const var_array & var)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (var);
}

var::var(const gen::property_set & set)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (set);
}

var::var(const gen::pair_set_interface & set)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (set);
}

var::var(const gen::str_str_interface & set)
{
   m_etype  = type_new;
   m_pca2   = NULL;
   operator = (set);
}

var::var(const class var & var)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (var);
}

var::var(class var * pvar)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (pvar);
}

var::var(const gen::property & prop)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (prop);
}

var::var(const string_composite & composite)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (composite);
}

var::var(const id & id)
{
   m_etype = type_new;
   m_pca2 = NULL;
   operator = (id);
}

var::~var()
{
   if(m_pca2 != NULL)
   {
      try
      {
         gen::release(m_pca2);
      }
      catch(...)
      {
      }
   }
}

strsize var::get_length() const
{
   return get_string().get_length();
}

void var::get_string(char * psz) const
{
   gen::str::copy(psz, get_string());
}

var::e_type var::get_type() const
{
   return m_etype;
}

class var & var::operator ++(int)
{
   switch(get_type())
   {
   case type_new:
   case type_null:
   case type_stra:
   case type_inta:
   case type_empty:
   case type_ca2:
      set_type(type_integer);
      m_i = 1;
      break;
   case type_bool:
      if(!m_b)
      {
         set_type(type_integer);
         m_i = 1;
      }
      else
      {
         set_type(type_integer);
         m_i = 2;
      }
      break;
   case type_string:
      set_type(type_integer);
      m_i = atoi(m_str) + 1;
      break;
   case type_double:
      m_d += 1.0;
      break;
   case type_integer:
      m_i++;
      break;
   case type_ulong:
      m_ul++;
      break;
   default:
      set_type(type_integer, false);
      m_i = 1;
      break;
   }
   return *this;
}



void var::set_type(e_type e_type, bool bConvert)
{
   if(m_pca2 != NULL)
   {
      gen::release(m_pca2);
      m_pca2 = NULL;
   }
   if(e_type == m_etype)
      return;
   if(bConvert)
   {
      switch(e_type)
      {
      case type_integer:
         m_i      = get_integer();
         break;
      case type_ulong:
         m_ul     = get_ulong();
         break;
      case type_double:
         m_d      = get_double();
         break;
      case type_string:
         m_str    = get_string();
         break;
      case type_id:
         m_id     = get_id();
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
   return get_type() != type_parareturn || ::gen::ok(m_parareturn);
}

bool var::failed() const
{
   return get_type() == type_parareturn && !::gen::ok(m_parareturn);
}

void var::set_string(const char * psz)
{
   if(get_type() == type_pstring)
   {
      *m_pstr = psz;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = psz;
   }
   else
   {
      set_type(type_string, false);
      m_str = psz;
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

class var & var::operator = (gen::para_return & eret)
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

class var & var::operator = (int i)
{
   if(get_type() == type_pinteger)
   {
      *m_pi = i;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = i;
   }
   else
   {
      set_type(type_integer, false);
      m_i = i;
   }
   return *this;
}



#ifdef LINUX

class var & var::operator = (long int i)
{
   if(get_type() == type_pint64)
   {
      *m_pi64 = i;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = i;
   }
   else
   {
      set_type(type_int64, false);
      m_i64 = i;
   }
   return *this;
}

#endif

class var & var::operator = (int * pi)
{
   set_type(type_pinteger, false);
   m_pi = pi;
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
   set_type(type_pint64, false);
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

class var & var::operator = (long l)
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

class var & var::operator = (unsigned long ul)
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

class var & var::operator = (long long ll)
{
   if(get_type() == type_pint64)
   {
      *m_pi64 = ll;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = ll;
   }
   else
   {
      set_type(type_int64, false);
      m_i64 = ll;
   }
   return *this;
}

class var & var::operator = (unsigned long long ull)
{
   if(get_type() == type_puint64)
   {
      *m_pui64 = ull;
   }
   else if(get_type() == type_pvar)
   {
      *m_pvar = ull;
   }
   else
   {
      set_type(type_uint64, false);
      m_ui64 = ull;
   }
   return *this;
}

class var & var::operator = (unsigned int ui)
{
   set_type(type_uint, false);
   m_ui = ui;
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
   set_string(gen::international::unicode_to_utf8(lpcsz));
   return *this;
}

class var & var::operator = (const gen::property & prop)
{
   operator = (((gen::property &)prop).get_value());
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
      case type_pinteger:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pi;
         return *this;
      case type_pstring:
         // should dereference (this operator here means a content copy)
         *this  = *((class var &)var).m_pstr;
         return *this;
      }

      set_type(((class var &)var).get_type(), false);
      switch(((class var &)var).get_type())
      {
      case type_bool:
         m_b      = var.m_b;
         break;
      case type_integer:
         m_i      = var.m_i;
         break;
      case type_int64:
         m_i64    = var.m_i64;
         break;
      case type_ulong:
         m_ul     = var.m_ul;
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
      case type_ca2:
         {
            m_pca2 = ((class var &)var).m_pca2;
            gen::add_ref(m_pca2);
         }
         break;
      case type_id:
         m_id    = var.m_id;
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

class var & var::operator = (const gen::property_set & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

class var & var::operator = (const gen::pair_set_interface & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

class var & var::operator = (const gen::str_str_interface & propsetParam)
{
   propset() = propsetParam;
   return *this;
}

var & var::operator = (const string_composite & composite)
{

   string str;
   count count = composite.get_length();
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


var::operator const char *() const
{
   return get_string();
}


// returns 0 for unknown conversions
var::operator unsigned int()
{
   switch(m_etype)
   {
   case type_null:
      return 0;
   case type_empty:
      return 0;
   case type_string:
      return atoi(m_str);
   case type_integer:
      return m_i;
   case type_ulong:
      return m_ul;
   case type_ca2:
      return 0;
   case type_pvar:
      return m_pvar->operator unsigned int();
   default:
      return 0;
   }
}

// returns 0 for unknown conversions
var::operator long()
{
   switch(m_etype)
   {
   case type_null:
      return 0;
   case type_empty:
      return 0;
   case type_string:
      return atol(m_str);
   case type_integer:
      return m_i;
   case type_ulong:
      return m_ul;
   case type_ca2:
      return 0;
   case type_pvar:
      return m_pvar->operator long();
   default:
      return 0;
   }
}

// returns 0 for unknown conversions
var::operator int()
{
   switch(m_etype)
   {
   case type_null:
      return 0;
   case type_empty:
      return 0;
   case type_string:
      return atoi(m_str);
   case type_integer:
      return m_i;
   case type_int64:
      return (int) m_i64;
   case type_ulong:
      return m_ul;
   case type_ca2:
      return 0;
   case type_pvar:
      return m_pvar->operator int();
   case type_pstring:
      return atoi(*m_pstr);
   case type_id:
      return m_id;
   case type_pid:
      return *m_pid;
   default:
      return 0;
   }
}

// returns 0 for unknown conversions
var::operator int64_t()
{
   switch(m_etype)
   {
   case type_null:
      return 0;
   case type_empty:
      return 0;
   case type_string:
      return atoi(m_str);
   case type_integer:
      return m_i;
   case type_int64:
      return m_i64;
   case type_ulong:
      return m_ul;
   case type_ca2:
      return 0;
   case type_pvar:
      return m_pvar->operator int();
   default:
      return 0;
   }
}

bool var::is_true() const
{
   switch(m_etype)
   {
   case type_null:
      return false;
   case type_empty:
      return false;
   case type_string:
      return !m_str.is_empty() && !m_str.CompareNoCase("false");
   case type_integer:
      return m_i != 0;
   case type_ulong:
      return m_ul != 0;
   case type_double:
      return m_d != 0;
   case type_ca2:
      return m_pca2 != NULL;
   case type_bool:
      return m_b;
   case type_pvar:
      return m_pvar->is_true();
   default:
      return false;
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
   case type_integer:
      return m_i == 0;
   case type_ulong:
      return m_ul == 0;
   case type_double:
      return m_d == 0.0;
   case type_ca2:
      return m_pca2 != NULL;
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

void var::read(ex1::byte_input_stream & is)
{
   int i;
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
   case type_integer:
      {
         is >> m_i;
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
         int iCount;
         is >> iCount;
         inta().set_size(iCount);
         for(int i = 0; i < m_pia->get_count(); i++)
         {
            is >> (int &) m_pia->element_at(i);
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
   case type_ca2:
      {
         ::ca::type_info info;
         is >> info;
         m_pca2 = Sys(is.get_app()).alloc(info);
         if(m_pca2 == NULL)
         {
            throw "object allocation is not implemented";
         }
         ::ex1::byte_serializable * pserializable = dynamic_cast < ::ex1::byte_serializable * > (m_pca2);
         if(pserializable != NULL)
         {
            pserializable->read(is);
         }
         else
         {
            ::ex1::plain_text_serializable * pserializable = dynamic_cast < ::ex1::plain_text_serializable * > (m_pca2);
            if(pserializable != NULL)
            {
               pserializable->read(is.m_spreader);
            }
            else
            {
               throw "object serialization is not implemented";
            }
         }
      }
      break;
   default:
      throw "WHAT!!";
   }
}

void var::write(ex1::byte_output_stream & ostream)
{
   int i = get_type();
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
   case type_integer:
      ostream << m_i;
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
         for(int i = 0; i < m_pia->get_count(); i++)
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
   case type_ca2:
      {
         ::ca::type_info info(typeid(*m_pca2));
         ostream << info;
         ::ex1::byte_serializable * pserializable = dynamic_cast < ::ex1::byte_serializable * >(m_pca2);
         if(pserializable != NULL)
         {
            pserializable->write(ostream);
         }
         else
         {
            ::ex1::plain_text_serializable * pserializable = dynamic_cast < ::ex1::plain_text_serializable * >(m_pca2);
            if(pserializable != NULL)
            {
               pserializable->write(ostream.m_spwriter);
            }
            else
            {
               throw "object is not serializable";
            }
         }
      }
      break;
   default:
      throw "WHAT!!";
   }
}

int var::compare_ci(const class var & var) const
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
         //var.inta().remove(var2.get_integer());
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
      return get_integer() - var.get_integer();
   }
   else if(is_ulong() || var.is_ulong())
   {
      return get_ulong() - var.get_ulong();
   }
   else
   {
      return get_string().CompareNoCase(var.get_string());
   }
   return -2;
}

int var::compare_ci(const char * psz) const
{
   var var(psz);
   return compare_ci(var);
}


int var::compare(const class var & var) const
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
         //var.inta().remove(var2.get_integer());
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
      return get_integer() - var.get_integer();
   }
   else if(is_ulong() || var.is_ulong())
   {
      return get_ulong() - var.get_ulong();
   }
   else
   {
      return get_string().Compare(var.get_string());
   }
   return -2;
}

int var::compare(const char * psz) const
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

bool var::operator == (int i) const
{
   return get_integer() == i;
}

bool var::operator != (int i) const
{
   return get_integer() != i;
}

bool var::operator < (int i) const
{
   return get_integer() < i;
}

bool var::operator <= (int i) const
{
   return get_integer() <= i;
}

bool var::operator >= (int i) const
{
   return get_integer() >= i;
}

bool var::operator > (int i) const
{
   return get_integer() > i;
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

bool var::strict_equal(int i) const
{
   return m_etype == type_integer && m_i == i;
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

bool var::strict_different(int i) const
{
   return m_etype != type_integer || m_i != i;
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

bool strict_equal(int i, const class var & var)
{
   return var.m_etype == var::type_integer && i == var.m_i;
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

bool strict_different(int i, const class var & var)
{
   return var.m_etype != var::type_integer || i != var.m_i;
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
      for(int i = 0; i < array_get_count(); i++)
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
      else if(m_etype == var::type_integer)
      {
         str.Format("%I32d", m_i);
      }
      else if(m_etype == var::type_int64)
      {
         str.Format("%I64d", m_i64);
      }
      else if(m_etype == var::type_ulong)
      {
         str.Format("%d", m_ul);
      }
      else if(m_etype == var::type_double)
      {
         str.Format("%f", m_d);
      }
      else if(m_etype == var::type_id)
      {
         str = m_id;
      }
      else if(m_etype == var::type_pid)
      {
         str = *m_pid;
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


inline id var::get_id(const char * pszOnNull) const
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
      else if(m_etype == var::type_integer)
      {
         id = m_i;
      }
      else if(m_etype == var::type_int64)
      {
         id = m_i64;
      }
      else if(m_etype == var::type_ulong)
      {
         id = (int64_t) m_ul;
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

int var::get_integer(int iDefault) const
{
   switch(m_etype)
   {
   case var::type_pvar:
      return m_pvar->get_integer(iDefault);
   case var::type_integer:
      return m_i;
   case var::type_int64:
      return m_i64;
   case var::type_ulong:
      return (int) m_ul;
   case var::type_double:
      return (int) m_d;
   case var::type_string:
      {
         gen::str::atoi(m_str, iDefault);
         return iDefault;
      }
   default:
      return iDefault;
   }
}

unsigned long var::get_ulong() const
{
   unsigned long ul;
   if(m_etype == var::type_integer)
   {
      ul = (unsigned long) m_i;
   }
   else if(m_etype == var::type_ulong)
   {
      ul = m_ul;
   }
   else if(m_etype == var::type_double)
   {
      ul = (unsigned long) m_d;
   }
   else
   {
      ul = atoi(m_str);
   }
   return ul;
}

double var::get_double() const
{
   double d;
   if(m_etype == var::type_integer)
   {
      d = (double) m_i;
   }
   else if(m_etype == var::type_ulong)
   {
      d = (double) m_ul;
   }
   else if(m_etype == var::type_double)
   {
      d = m_d;
   }
   else
   {
      d = atof(m_str);
   }
   return d;
}

bool var::get_bool() const
{
   bool b;
   if(m_etype == var::type_integer)
   {
      b = m_i != 0;
   }
   else if(m_etype == var::type_ulong)
   {
      b = m_ul != 0;
   }
   else if(m_etype == var::type_double)
   {
      b = m_d != 0.0;
   }
   else if(m_etype == var::type_bool)
   {
      b = m_b;
   }
   else
   {
      b = m_str.get_length() > 0 &&
          m_str.CompareNoCase("false") != 0;
   }
   return b;
}

class primitive::memory & var::memory()
{
   if(get_type() != type_memory)
   {
      set_type(type_memory);
   }
   if(m_pca2 == NULL)
   {
      m_pca2 = new class primitive::memory();
   }
   return *dynamic_cast < class primitive::memory * > (m_pca2);
}



stringa & var::stra()
{
   if(m_etype != type_stra)
   {
      stringa * pstra = new stringa();
      pstra->add(*this);
      set_type(type_stra, false);
      ASSERT(m_pca2 == NULL);
      m_pca2 = pstra;
      m_pstra = pstra;
   }
   else if(m_pca2 == NULL)
   {
      m_pstra = new stringa();
      m_pca2 = m_pstra;
   }
   return *m_pstra;
}

int_array & var::inta()
{
   if(m_etype != type_inta)
   {
      int_array * pia =  new int_array();
      for(int i = 0; i < array_get_count(); i++)
      {
         pia->add((int) at(i));
      }
      set_type(type_inta, false);
      ASSERT(m_pca2 == NULL);
      m_pca2 = pia;
      m_pia = pia;
   }
   else if(m_pca2 == NULL)
   {
      m_pia = new int_array();
      m_pca2 = m_pia;
   }
   return *m_pia;
}

int64_array & var::int64a()
{
   if(m_etype != type_int64a)
   {
      int64_array * pia =  new int64_array();
      for(int i = 0; i < array_get_count(); i++)
      {
         pia->add((int64_t) at(i));
      }
      set_type(type_int64a, false);
      ASSERT(m_pca2 == NULL);
      m_pca2 = pia;
      m_pia64 = pia;
   }
   else if(m_pca2 == NULL)
   {
      m_pia64 = new int64_array();
      m_pca2 = m_pia64;
   }
   return *dynamic_cast < int64_array * > (m_pca2);
}

const class primitive::memory & var::memory() const
{
   if(get_type() != type_memory)
   {
      throw 0;
   }
   return *dynamic_cast < const class primitive::memory * > (m_pca2);
}


stringa var::stra() const
{
   var varTime = *this;
   return varTime.stra();
}

int_array var::inta() const
{
   var varTime = *this;
   return varTime.inta();
}

int64_array var::int64a() const
{
   var varTime = *this;
   return varTime.int64a();
}

class var & var::operator = (::ca::ca * pca2)
{
   if(m_pca2 == pca2)
      return *this;
   set_type(type_ca2, false);
   m_pca2 = pca2;
   gen::add_ref(m_pca2);
   return *this;
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
      var_array * pvara =  new var_array();
      for(int i = 0; i < array_get_count(); i++)
      {
         pvara->add(at(i));
      }
      set_type(type_vara, false);
      ASSERT(m_pca2 == NULL);
      m_pca2 = pvara;
      m_pvara = pvara;
   }
   else if(m_pca2 == NULL)
   {
      m_pvara = new var_array();
      m_pca2 = m_pvara;
   }
   return *m_pvara;
}

var_array var::vara() const
{
   if(get_type() == type_pvar)
   {
      return m_pvar->vara();
   }
   else if(get_type() != type_vara)
   {
      var varTime = *this;
      return varTime.vara();
   }
   return *m_pvara;
}

gen::property_set & var::propset(::ca::application * papp)
{
   gen::property_set * pset;
   if(m_etype == type_pvar)
   {
      pset = &m_pvar->propset();
   }
   else if(m_etype != type_propset)
   {
      gen::property_set * ppropset = new gen::property_set();
      for(int i = 0; i < array_get_count(); i++)
      {
         ppropset->add(NULL, at(i));
      }
      set_type(type_propset, false);
      //ASSERT(m_pca2 == NULL);
      m_pca2 = ppropset;
      pset = ppropset;
      m_pset = pset;
   }
   else if(m_pca2 == NULL)
   {
      pset = new gen::property_set();
      m_pca2 = pset;
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

gen::property_set var::propset() const
{
   var varTime = *this;
   return varTime.propset();
}

gen::property & var::prop()
{
   if(m_etype != type_prop)
   {
      set_type(type_prop);
   }
   if(m_pca2 == NULL)
   {
      m_pprop = new gen::property();
      m_pca2 = m_pprop;
   }
   return *dynamic_cast < gen::property * > (m_pca2);
}

gen::property var::prop() const
{
   if(get_type() != type_prop)
   {
      var varTime = *this;
      return varTime.prop();
   }
   return *dynamic_cast < const gen::property * > (m_pca2);
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




void var::on_delete(::ca::ca * pca)
{
   if(m_pca2 == pca)
   {
      m_pca2 = NULL;
      unset();
   }
}

variable_strict_compare var::strict_compare() const
{
   return *this;
}

var var::dereference()
{
   if(get_type() == type_pvar)
      return m_pvar->dereference();
   else if(get_type() == type_pstring)
      return *m_pstr;
   else if(get_type() == type_pinteger)
      return *m_pi;
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



bool var::array_contains(const char * psz, index find, count count) const
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
         index upperbound = min(array_get_upper_bound(), find + count - 1);
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
         index upperbound = min(array_get_upper_bound(), last);
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


var var::operator - (int i) const
{
   return get_integer() - i;
}

var var::operator - (unsigned int user) const
{
   return get_ulong() - user;
}

var var::operator - (long l) const
{
   return get_integer() - l;
}

var var::operator - (unsigned long ul) const
{
   return get_ulong() - ul;
}

var var::operator - (double d) const
{
   return get_double() - d;
}

var CLASS_DECL_ca operator - (int i, const class var & var)
{
   return i - var.get_integer();
}

var CLASS_DECL_ca operator - (unsigned int user, const class var & var)
{
   return user - var.get_ulong();
}

var CLASS_DECL_ca operator - (long l, const class var & var)
{
   return l - var.get_integer();
}

var CLASS_DECL_ca operator - (unsigned long ul, const class var & var)
{
   return ul - var.get_ulong();
}

var CLASS_DECL_ca operator - (double d, const class var & var)
{
   return d - var.get_double();
}

var CLASS_DECL_ca operator - (const class var & var1, const class var & var2)
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
         var.inta().remove(var2.get_integer());
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
      var = var1.get_integer() - var2.get_integer();
   }
   else if(var1.is_ulong() || var2.is_ulong())
   {
      var = var1.get_ulong() - var2.get_ulong();
   }
   else
   {
      var = atoi(var1.get_string()) - atoi(var2.get_string());
   }
   return var;
}


var var::operator + (int i) const
{
   return get_integer() + i;
}

var var::operator + (unsigned int user) const
{
   return get_ulong() + user;
}

var var::operator + (long l) const
{
   return get_integer() + l;
}

var var::operator + (unsigned long ul) const
{
   return get_ulong() + ul;
}

var var::operator + (double d) const
{
   return get_double() + d;
}

var CLASS_DECL_ca operator + (int i, const class var & var)
{
   return i + var.get_integer();
}

var CLASS_DECL_ca operator + (unsigned int user, const class var & var)
{
   return user + var.get_ulong();
}

var CLASS_DECL_ca operator + (long l, const class var & var)
{
   return l + var.get_integer();
}

var CLASS_DECL_ca operator + (unsigned long ul, const class var & var)
{
   return ul + var.get_ulong();
}

var CLASS_DECL_ca operator + (double d, const class var & var)
{
   return d + var.get_double();
}

var CLASS_DECL_ca operator + (const class var & var1, const class var & var2)
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
            var.inta().add(var2.get_integer());
         }
      }
      else
      {
         var = var2;
         var.inta().add(var1.get_integer());
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
      var = var1.get_integer() + var2.get_integer();
   }
   else if(var1.is_ulong() && var2.is_ulong())
   {
      var = var1.get_ulong() + var2.get_ulong();
   }
   else
   {
      var = var1.get_string() + var2.get_string();
   }
   return var;
}






















var var::operator / (int i) const
{
   return get_integer() / i;
}

var var::operator / (unsigned int user) const
{
   return get_ulong() / user;
}

var var::operator / (long l) const
{
   return get_integer() / l;
}

var var::operator / (unsigned long ul) const
{
   return get_ulong() / ul;
}

var var::operator / (double d) const
{
   return get_double() / d;
}

var CLASS_DECL_ca operator / (int i, const class var & var)
{
   return i / var.get_integer();
}

var CLASS_DECL_ca operator / (unsigned int user, const class var & var)
{
   return user / var.get_ulong();
}

var CLASS_DECL_ca operator / (long l, const class var & var)
{
   return l / var.get_integer();
}

var CLASS_DECL_ca operator / (unsigned long ul, const class var & var)
{
   return ul / var.get_ulong();
}

var CLASS_DECL_ca operator / (double d, const class var & var)
{
   return d / var.get_double();
}

var CLASS_DECL_ca operator / (const class var & var1, const class var & var2)
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
         var.inta().divide(var2.get_integer());
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
      var = var1.get_integer() / var2.get_integer();
   }
   else if(var1.is_ulong() || var2.is_ulong())
   {
      var = var1.get_ulong() / var2.get_ulong();
   }
   else
   {
      var = atoi(var1.get_string()) / atoi(var2.get_string());
   }
   return var;
}


var var::operator * (int i) const
{
   return get_integer() * i;
}

var var::operator * (unsigned int user) const
{
   return get_ulong() * user;
}

var var::operator * (long l) const
{
   return get_integer() * l;
}

var var::operator * (unsigned long ul) const
{
   return get_ulong() * ul;
}

var var::operator * (double d) const
{
   return get_double() * d;
}

var CLASS_DECL_ca operator * (int i, const class var & var)
{
   return i * var.get_integer();
}

var CLASS_DECL_ca operator * (unsigned int user, const class var & var)
{
   return user * var.get_ulong();
}

var CLASS_DECL_ca operator * (long l, const class var & var)
{
   return l * var.get_integer();
}

var CLASS_DECL_ca operator * (unsigned long ul, const class var & var)
{
   return ul * var.get_ulong();
}

var CLASS_DECL_ca operator * (double d, const class var & var)
{
   return d * var.get_double();
}

var CLASS_DECL_ca operator * (const class var & var1, const class var & var2)
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
            var.inta().add(var2.get_integer());
         }
      }
      else
      {
         var = var2;
         var.inta().add(var1.get_integer());
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
      var = var1.get_integer() * var2.get_integer();
   }
   else if(var1.is_ulong() || var2.is_ulong())
   {
      var = var1.get_ulong() * var2.get_ulong();
   }
   else
   {
      var = var1.get_string() * var2.get_string();
   }
   return var;
}

























class var & var::operator -= (int i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (unsigned int user)
{
   operator =(*this - user);
   return *this;
}

class var & var::operator -= (long i)
{
   operator =(*this - i);
   return *this;
}

class var & var::operator -= (unsigned long user)
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
























class var & var::operator += (int i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (unsigned int user)
{
   operator =(*this + user);
   return *this;
}

class var & var::operator += (long i)
{
   operator =(*this + i);
   return *this;
}

class var & var::operator += (unsigned long user)
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
























class var & var::operator /= (int i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (unsigned int user)
{
   operator =(*this / user);
   return *this;
}

class var & var::operator /= (long i)
{
   operator =(*this / i);
   return *this;
}

class var & var::operator /= (unsigned long user)
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
























class var & var::operator *= (int i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (unsigned int user)
{
   operator =(*this * user);
   return *this;
}

class var & var::operator *= (long i)
{
   operator =(*this * i);
   return *this;
}

class var & var::operator *= (unsigned long user)
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
   || m_etype == type_integer
   || m_etype == type_pinteger
   || m_etype == type_ulong
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
   else if(m_etype == type_ca2)
   {
      return false;
   }
   else
   {
      return false;
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
            int i;
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
   if(m_etype == type_integer)
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
            for(int i = 1; i < str.get_length(); i++)
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

bool var::is_ulong() const
{
   if(m_etype == type_ulong)
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
            for(int i = 1; i < str.get_length(); i++)
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
      return dynamic_cast < const gen::property_set * > (m_pca2)->has_property(pszName);
   }
   else if(get_type() == type_pvar)
   {
      return m_pvar->has_property(pszName);
   }
   else if(get_type() == type_ca2)
   {
      if(ca2 < var >() != NULL)
      {
         return ca2 < var >()->has_property(pszName);
      }
      else if(ca2 < gen::property_set >() != NULL)
      {
         return ca2 < gen::property_set >()->has_property(pszName);
      }
      else if(ca2 < gen::property >() != NULL)
      {
         return ca2 < gen::property >()->name().CompareNoCase(pszName) == 0;
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












void var::consume_number(const char * & psz)
{
   consume_number(psz, psz + strlen(psz) - 1);
}

void var::consume_number(const char * & psz, const char * pszEnd)
{
   const char * pszParse = psz;
   bool bSigned = false;
   bool bFloat = false;
   gen::str::consume_spaces(pszParse, 0, pszEnd);
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
   gen::str::consume_spaces(pszJson, 0, pszEnd);
   if(*pszJson == '{')
   {
      propset().parse_json(pszJson, pszEnd);
   }
   else if(*pszJson == '\"')
   {
      operator = (gen::str::consume_quoted_value(pszJson, pszEnd));
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
      string str = "not expected character : ";
      str += pszJson;
      throw str;
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

      case type_integer:
      case type_pinteger:
      case type_ulong:
         return true;

      case type_pvar:
         return m_pvar->is_numeric();

      case type_ca2:
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

      case type_uint:
         return true;

      case type_id:
         return m_id.is_number();

      case type_pid:
         return m_pid->is_number();

      case type_int64a:
         return false;

      default:
         throw not_implemented_exception();

   };

}
