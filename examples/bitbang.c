/* This program is distributed under the GPL, version 2 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __WIN32__
#define sleep(x) Sleep(x)
#endif
#include <ftdi.h>

int main(int argc, char **argv)
{
    struct ftdi_context ftdic;
    int f,i;
    char buf[1];

    if (ftdi_init(&ftdic) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }

    f = ftdi_usb_open(&ftdic, 0x0403, 0x6001);

    if (f < 0 && f != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(&ftdic));
        exit(-1);
    }

    printf("ftdi open succeeded: %d\n",f);

    printf("enabling bitbang mode\n");
    ftdi_set_bitmode(&ftdic, 0xFF, BITMODE_BITBANG);

    sleep(3);

    buf[0] = 0x0;
    printf("turning everything on\n");
    f = ftdi_write_data(&ftdic, buf, 1);
    if (f < 0)
    {
        fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(&ftdic));
    }

    sleep(3);

    buf[0] = 0xFF;
    printf("turning everything off\n");
    f = ftdi_write_data(&ftdic, buf, 1);
    if (f < 0)
    {
        fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(&ftdic));
    }

    sleep(3);

    for (i = 0; i < 32; i++)
    {
        buf[0] =  0 | (0xFF ^ 1 << (i % 8));
        if ( i > 0 && (i % 8) == 0)
        {
            printf("\n");
        }
        printf("%02hhx ",buf[0]);
        fflush(stdout);
        f = ftdi_write_data(&ftdic, buf, 1);
        if (f < 0)
        {
            fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(&ftdic));
        }
        sleep(1);
    }

    printf("\n");

    printf("disabling bitbang mode\n");
    ftdi_disable_bitbang(&ftdic);

    ftdi_usb_close(&ftdic);
    ftdi_deinit(&ftdic);
}
