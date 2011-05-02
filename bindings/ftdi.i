/* File: example.i */
%module ftdi
%include "typemaps.i"
%include "cpointer.i"
%pointer_functions(unsigned int, uintp);
%pointer_functions(unsigned char *, ucharp);
%pointer_functions(char *, charp);

%typemap(in) unsigned char* = char*;
%ignore ftdi_write_data_async;
%ignore ftdi_async_complete;

%include ftdi.h
%{
#include <ftdi.h>
%}

extern "C" {

%apply char *OUTPUT { unsigned char *buf };
    int ftdi_read_data(struct ftdi_context *ftdi, unsigned char *buf, int size);
%clear unsigned char *buf;

%apply int *OUTPUT { unsigned int *chunksize };
    int ftdi_read_data_get_chunksize(struct ftdi_context *ftdi, unsigned int *chunksize);
    int ftdi_write_data_get_chunksize(struct ftdi_context *ftdi, unsigned int *chunksize);
%clear unsigned int *chunksize;

    //int ftdi_write_data_async(struct ftdi_context *ftdi, unsigned char *buf, int size);
    //void ftdi_async_complete(struct ftdi_context *ftdi, int wait_for_more);
%apply char *OUTPUT { unsigned char *pins };
    int ftdi_read_pins(struct ftdi_context *ftdi, unsigned char *pins);
%clear unsigned char *pins;

%apply char *OUTPUT { unsigned char *latency };
    int ftdi_get_latency_timer(struct ftdi_context *ftdi, unsigned char *latency);
%clear unsigned char *latency;

%apply char *OUTPUT { unsigned short *status };
    int ftdi_poll_modem_status(struct ftdi_context *ftdi, unsigned short *status);
%clear unsigned short *status;

%apply char *OUTPUT { unsigned char *output };
    int  ftdi_eeprom_build(struct ftdi_eeprom *eeprom, unsigned char *output);
%clear unsigned char *output;

%apply char *OUTPUT { unsigned char *eeprom };
    int ftdi_read_eeprom(struct ftdi_context *ftdi, unsigned char *eeprom);
    int ftdi_write_eeprom(struct ftdi_context *ftdi, unsigned char *eeprom);
%clear unsigned char *eeprom;

%apply int *OUTPUT { unsigned int *chipid };
    int ftdi_read_chipid(struct ftdi_context *ftdi, unsigned int *chipid);
%clear unsigned int *chipid;

}
