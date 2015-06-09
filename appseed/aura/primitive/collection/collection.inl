#pragma once
















#ifdef WINDOWS
namespace gen
{
   namespace win
   {
      template < class TYPE, class ARG_TYPE >
      bool CreateSafeArray(array < TYPE, ARG_TYPE > & ar, VARIANT * pvar, VARTYPE vt)
      {
          pvar->vt = VT_ARRAY | vt;
          SAFEARRAYBOUND rgsabound[1];
          rgsabound[0].lLbound = 0;
          rgsabound[0].cElements = get_size();
          pvar->parray = SafeArrayCreate(vt, 1, rgsabound);
          if(pvar->parray == NULL)
              return false;
          for(int32_t i = 0; i < get_size(); i++)
          {
              SafeArrayPutElement(pvar->parray, (long *) &i, &ar.element_at(i));
          }
      }

      template < class TYPE, class ARG_TYPE >
      bool CopySafeArray(array < TYPE, ARG_TYPE > & ar, VARIANT * var)
      {
      //    AFX_MANAGE_STATE(AfxGetStaticModuleState())
          ASSERT(pvar->vt == (VT_ARRAY | VT_I4));
          ar.remove_all();
          UINT uiDim;

          if(1 != (uiDim = SafeArrayGetDim(pvar->parray)))
          {
              ASSERT(FALSE);
              return false;
          }

          HRESULT hr;
          long lLBound;
          long lUBound;

          if(FAILED(hr = SafeArrayGetLBound(pvar->parray, uiDim, &lLBound)))
          {
              return false;
          }

          if(FAILED(hr = SafeArrayGetUBound(pvar->parray, uiDim, &lUBound)))
          {
              return false;
          }

          DWORD dw;
          for(int32_t i = lLBound; i <= lUBound; i++)
          {
              SafeArrayGetElement(pvar->parray, (long *) &i, &dw);
              ar.add(dw);
          }
          return true;

      }
   }
}
#endif












template < typename Type, typename RawType >
void string_array < Type, RawType >::add(const var & var)
{
   if(var.is_empty())
   {
   }
   else if(var.get_type() == var::type_stra)
   {
      ::lemon::array::add(*this, var.stra());
   }
   else if(var.cast < string_array < Type, RawType > >() != NULL)
   {
      ::lemon::array::add(*this, *var.cast < string_array < Type,RawType > >());
   }
   else if(var.get_type() == var::type_vara)
   {
      for(int32_t i = 0; i < var.vara().get_count(); i++)
      {
         ::lemon::array::add(*this,var.vara()[i].get_string());
      }
   }
   else if(var.get_type() == var::type_inta)
   {
      for(int32_t i = 0; i < var.inta().get_count(); i++)
      {
         ::lemon::array::add(*this,::str::from(var.inta()[i]));
      }
   }
   else if(var.get_type() == var::type_propset)
   {
      for(auto property : var.propset())
      {
         ::lemon::array::add(*this, property.get_value().get_string());
      }
   }
   else
   {
      ::lemon::array::add(*this, var.get_string());
   }
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::add(const property & prop)
{
   add(prop.get_value());
}


template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::operator = (var varSrc)
{
   this->remove_all();
   if(varSrc.get_type() == var::type_stra)
   {
      varSrc.get_array(*this);
   }
   else
   {
      if(varSrc.get_count() == 1)
      {
         add((Type)varSrc.get_string());
      }
      else if(varSrc.get_count() > 1)
      {
         varSrc.get_array(*this);
      }
   }
   return *this;
}




