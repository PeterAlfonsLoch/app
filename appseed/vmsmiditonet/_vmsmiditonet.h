#ifndef ___VMSMIDITONET_INCLUDE_FILE
#define ___VMSMIDITONET_INCLUDE_FILE


struct MIDITONETMESSAGE
{
   DWORD dwTimeStamp;
   UINT uiDelta;
   UINT uiMsg;
   UINT uiChannel;
   UINT uiParam1;
   UINT uiParam2;
};






#endif // ___VMSMIDITONET_INCLUDE_FILE