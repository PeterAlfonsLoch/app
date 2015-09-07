#include "aura/aura/aura.h"


struct CLASS_DECL_AXIS_RDPCLIENT rdp_event_item
{

   rdpInput * input;
   BOOL bKey;
   BOOL down;
   UINT scancode;
   UINT uiMessage;
   POINT pt;
   void send();
};

typedef array < rdp_event_item > rdp_event_itema;

mutex g_mutexRdpEvent;
map < rdpInput *,rdpInput *,rdp_event_itema> g_eventmap;


CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_queue_event(rdpInput* input,BOOL bKey,BOOL down,UINT scancode,UINT uiMessage,POINT pt)
{

   synch_lock sl(&g_mutexRdpEvent);

   rdp_event_item item;
   item.input = input;
   item.bKey = bKey;
   item.down = down;
   item.scancode = scancode;
   item.uiMessage = uiMessage;
   item.pt = pt;

   g_eventmap[input].add(item);
}

CLASS_DECL_AXIS_RDPCLIENT bool  ca2rdp_get_event(rdp_event_item & item,rdpInput* input)
{

   synch_lock sl(&g_mutexRdpEvent);

   if(g_eventmap[input].has_elements())
   {
      item = g_eventmap[input][0];
      g_eventmap[input].remove_at(0);
      return true;
   }
   return false;
}



void rdp_event_item::send()
{
   ca2rdp_send_event(input,bKey,down,scancode,uiMessage,pt);
}
