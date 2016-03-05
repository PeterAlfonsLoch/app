#pragma once

extern "C"
{

void basecore_init();
void basecore_term();
void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, struct i_close_quit * pi);
void basecore_app_indicator_term(void * pind);

} // extern "C"


struct i_close_quit
{
public:

   virtual void __close() = 0;
   virtual void __quit() = 0;
   virtual bool __close_is_closed() = 0;

};

