%module qrcode_detect
%include "phppointers.i"
%{
    extern const char *single_detect_file(const char *fileName, int *REF);

    extern const char *single_detect_memory(const char *ptr, int size, int imageType, int *REF);
%}

extern const char *single_detect_file(const char *fileName, int *REF);

extern const char *single_detect_memory(const char *ptr, int size, int imageType, int *REF);
