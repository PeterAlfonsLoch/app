#pragma once


class CLASS_DECL_AXIS request_signal :
   public signal_details
{
public:


   var         m_varFile;
   var         m_varQuery;


   request_signal(sp(::base::application) papp, class ::signal * psignal = NULL);


};






