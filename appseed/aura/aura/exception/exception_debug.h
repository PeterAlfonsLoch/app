#pragma once


CLASS_DECL_AURA int __node_is_debugger_attached();

CLASS_DECL_AURA bool is_debugger_attached();


CLASS_DECL_AURA bool EnforceFilter( bool bEnforce );

   // WriteMemory function 
   // 
   // This function writes the specified sequence of bytes from 
   // the source primitive::memory into the target primitive::memory. In addition, the function 
   // modifies virtual primitive::memory protection attributes of the target primitive::memory page 
   // to make sure that it is writeable.
   // 
CLASS_DECL_AURA bool WriteMemory( BYTE* pTarget, const BYTE* pSource, uint32_t size );


