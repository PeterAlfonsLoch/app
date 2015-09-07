#include "aura/aura/aura.h"
#include "axis/rdpclient/client/common/rdpclient.h"

struct CLASS_DECL_AXIS_RDPCLIENT rdp_event_item
{

   void * input;
   int bKey;
   int down;
   UINT scancode;
   UINT uiMessage;
   POINT pt;
   void send();
};


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

>>>>>>> .r16293
typedef array < rdp_event_item > rdp_event_itema;

mutex g_mutexRdpEvent;
map < void *,void *,rdp_event_itema> g_eventmap;

CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_send_event(void * input,int bKey,int down,UINT scancode,UINT uiMessage,POINT pt);

CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_queue_event(void * input,int bKey,int down,UINT scancode,UINT uiMessage,POINT pt)
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

CLASS_DECL_AXIS_RDPCLIENT int  ca2rdp_get_event(rdp_event_item & item,void* input)
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
