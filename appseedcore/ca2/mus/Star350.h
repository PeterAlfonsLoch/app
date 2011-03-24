#pragma once

typedef struct tag_star350filehdr
{
    BYTE    x1[12];
    WORD    wDivision;
    WORD    wTracks;
    WORD    wMelodyTrack;
    WORD    wLyricTrack;
}   STAR350FILEHDR, *LPSTAR350FILEHDR;

typedef struct tag_star350chunkhdr
{
    DWORD   dwLength;
}   STAR350CHUNKHDR,
    *LPSTAR350CHUNKHDR;


