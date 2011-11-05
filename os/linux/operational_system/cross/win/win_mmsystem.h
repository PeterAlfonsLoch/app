#pragma once


typedef DWORD           FOURCC;         /* a four character code */


namespace mus
{


   class midi_stream;
   class midi_out;


} // namespace mus


typedef mus::midi_stream *       HMIDISTRM;
typedef mus::midi_out *          HMIDIOUT;
