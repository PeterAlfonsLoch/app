#pragma once

#include "radix/flags.h"

namespace check
{

   typedef flags < e_check > check;

} // namespace check


#ifdef _WIN64
template <>
inline UINT HashKey(INT_PTR key)
{
	// default identity hash - works for most primitive values
	return (DWORD)(((DWORD_PTR)key)>>32);
}
#else
template <>
inline UINT HashKey(INT_PTR key)
{
	// default identity hash - works for most primitive values
	return (DWORD)(((DWORD_PTR)key)>>16);
}
#endif

namespace user
{

   typedef ::collection::map < INT_PTR, INT_PTR, ::user::interaction_base *, ::user::interaction_base * > int_to_window_interface;
   typedef pointer_array < interaction > interaction_array;

} // namespace user

typedef comparable_array < ::command_target * > command_target_ptra;

namespace user
{

   namespace win
   {

      namespace message
      {

         class CLASS_DECL_CORE DispatchHandlerItemArray :
            public array < DispatchHandlerItemBase *, DispatchHandlerItemBase *>
         {
         public:
            bool HasSignalizable(signalizable* psignalizable);
         };

         class DispatchSignalPtrArray :
            public array < DispatchSignal * , DispatchSignal * >
         {
         };

         class DispatchSignalArray :
            public array_ptr_alloc < DispatchSignal , DispatchSignal & >
         {
         public:
            virtual ~SignalArray();
            void GetSignalsByMessage(SignalPtrArray & signalptra, UINT uiMessage, UINT uiCode, UINT uiId);
            Signal * GetSignalByMessage(UINT uiMessage, UINT uiCode, UINT uiIdStart, UINT uiIdEnd);
         };

      } // namespace message

   } // namespace win

} // namespace user


