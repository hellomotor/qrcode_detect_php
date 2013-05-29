%module qrcode_detect
%include "phppointers.i"
%{
    extern const char *single_decode_file(const char *fileName, int pure_barcode, int *REF);

    extern const char *single_decode_memory(const char *ptr, int size, int imageType, int pure_barcode, int *REF);
%}

extern const char *single_decode_file(const char *fileName, int pure_barcode, int *REF);

extern const char *single_decode_memory(const char *ptr, int size, int imageType, int pure_barcode, int *REF);
