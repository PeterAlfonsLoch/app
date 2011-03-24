#pragma once

#define CA2_PALACE_SAFE_ZONE_BORDER_SIZE 32

struct CLASS_DECL_ca plex     // warning var length structure
{
   plex*          pNext;
   __int64        size;
   // BYTE data[maxNum*elementSize];

   void * data() { return ((byte*)(this+1)) + CA2_PALACE_SAFE_ZONE_BORDER_SIZE; }

   static plex* PASCAL create(plex*& head, UINT_PTR nMax, UINT_PTR cbElement);
         // like 'calloc' but no zero fill
         // may throw primitive::memory exceptions

   void FreeDataChain();       // free this one and links
};

