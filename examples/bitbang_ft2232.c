/* bitbang_ft2232.c

   Output some flickering in bitbang mode to the FT2232

   Thanks to max@koeln.ccc.de for fixing and extending
   the example for the second channel.

   This program is distributed under the GPL, version 2
*/

#include <stdio.h>
#include <unistd.h>
#ifdef __WIN32__
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#endif
#include <ftdi.h>

int main(int argc, char **argv)
{
    struct ftdi_context ftdic, ftdic2;
    char buf[1];
    int f,i;

    // Init 1. channel
    if (ftdi_init(&ftdic) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }

    ftdi_set_interface(&ftdic, INTERFACE_A);
    f = ftdi_usb_open(&ftdic, 0x0403, 0x6001);
    if (f < 0 && f != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(&ftdic));
        exit(-1);
    }
    printf("ftdi open succeeded(channel 1): %d\n",f);

    printf("enabling bitbang mode(channel 1)\n");
    ftdi_set_bitmode(&ftdic, 0xFF, BITMODE_BITBANG);

    // Init 2. channel
    if (ftdi_init(&ftdic2) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }
    ftdi_set_interface(&ftdic2, INTERFACE_B);
    f = ftdi_usb_open(&ftdic2, 0x0403, 0x6001);
    if (f < 0 && f != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(&ftdic2));
        exit(-1);
    }
    printf("ftdi open succeeded(channel 2): %d\n",f);

    printf("enabling bitbang mode (channel 2)\n");
    ftdi_set_bitmode(&ftdic2, 0xFF, BITMODE_BITBANG);

    // Write data
    printf("startloop\n");
    for (i = 0; i < 23; i++)
    {
        buf[0] =  0x1;
        printf("porta: %02i: 0x%02x \n",i,buf[0]);
        f = ftdi_write_data(&ftdic, buf, 1);
        if (f < 0)
            fprintf(stderr,"write failed on channel 1 for 0x%x, error %d (%s)\n", buf[0], f, ftdi_get_error_string(&ftdic));
        sleep(1);

        buf[0] =  0x2;
        printf("porta: %02i: 0x%02x \n",i,buf[0]);
        f = ftdi_write_data(&ftdic, buf, 1);
        if (f < 0)
            fprintf(stderr,"write failed on channel 1 for 0x%x, error %d (%s)\n", buf[0], f, ftdi_get_error_string(&ftdic));
        sleep(1);

        buf[0] =  0x1;
        printf("portb: %02i: 0x%02x \n",i,buf[0]);
        f = ftdi_write_data(&ftdic2, buf, 1);
        if (f < 0)
            fprintf(stderr,"write failed on channel 2 for 0x%x, error %d (%s)\n", buf[0], f, ftdi_get_error_string(&ftdic2));
        sleep(1);

        buf[0] =  0x2;
        printf("portb: %02i: 0x%02x \n",i,buf[0]);
        f = ftdi_write_data(&ftdic2, buf, 1);
        if (f < 0)
            fprintf(stderr,"write failed on channel 2 for 0x%x, error %d (%s)\n", buf[0], f, ftdi_get_error_string(&ftdic2));
        sleep(1);
    }
    printf("\n");

    printf("disabling bitbang mode(channel 1)\n");
    ftdi_disable_bitbang(&ftdic);
    ftdi_usb_close(&ftdic);
    ftdi_deinit(&ftdic);

    printf("disabling bitbang mode(channel 2)\n");
    ftdi_disable_bitbang(&ftdic2);
    ftdi_usb_close(&ftdic2);
    ftdi_deinit(&ftdic2);
}
