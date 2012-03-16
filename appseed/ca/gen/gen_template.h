#pragma once

#include "_pointer.h"
#include "_raw_pointer.h"
#include "_full_pointer.h"
#include "_base_enum.h"
#include "collection/_array_ptr_alloc.h"

class CLASS_DECL_ca string2a :
   public array_ptr_alloc < stringa, stringa & >
{
public:
};

namespace gen
{

   class signal;
   class signal::signal_delegate;
   class handler_item_base;


   class CLASS_DECL_ca signalid_array : public base_array < signalid *, signalid * >
   {
   public:
      virtual ~signalid_array();
      signalid * get(signalid * pid);
   };

   class CLASS_DECL_ca dispatch_handler_item_array :
      public base_array < dispatch_handler_item_base *, dispatch_handler_item_base *>
   {
   public:
      bool HasSignalizable(gen::signalizable * psignalizable);
   };

   class CLASS_DECL_ca dispatch_signal_ptr_array :
      public base_array < signal * , signal * >
   {
   public:
      bool emit(signal_object * pobj);
   };


   class CLASS_DECL_ca signal_array :
      public array_ptr_alloc < signal * , signal * >
   {
   public:
      void GetSignalsById(dispatch_signal_ptr_array & signalptra, signalid * pid);
      signal * GetSignalById(signalid * pid);
   };

   class CLASS_DECL_ca var_property_array :
      public ex1::serializable_array < array_ptr_alloc < property, property & > >
   {
   public:
   };

} // namespace gen


class CLASS_DECL_ca dword_2darray :
   public array_ptr_alloc < dword_array, dword_array & >
{
public:
};

class CLASS_DECL_ca index_2darray :
   public array_ptr_alloc < index_array, index_array & >
{
public:
};
