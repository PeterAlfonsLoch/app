#pragma once


class CLASS_DECL_ACE request_signal :
   public signal_details
{
public:


   var         m_varFile;
   var         m_varQuery;


   request_signal(::ace::application * papp, class ::signal * psignal = NULL);


};






