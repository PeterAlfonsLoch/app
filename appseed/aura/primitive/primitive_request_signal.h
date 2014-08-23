#pragma once


class CLASS_DECL_AURA request_signal :
   public signal_details
{
public:


   var         m_varFile;
   var         m_varQuery;


   request_signal(sp(::aura::application) papp, class ::signal * psignal = NULL);


};






