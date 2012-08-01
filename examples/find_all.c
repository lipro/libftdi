/* find_all.c

   Example for ftdi_usb_find_all()

   This program is distributed under the GPL, version 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <ftdi.h>

int main(void)
{
    int ret, i;
    struct ftdi_context ftdic;
    struct ftdi_device_list *devlist, *curdev;
    char manufacturer[128], description[128];

    if (ftdi_init(&ftdic) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }

    if ((ret = ftdi_usb_find_all(&ftdic, &devlist, 0x0403, 0x6001)) < 0)
    {
        fprintf(stderr, "ftdi_usb_find_all failed: %d (%s)\n", ret, ftdi_get_error_string(&ftdic));
        return EXIT_FAILURE;
    }

    printf("Number of FTDI devices found: %d\n", ret);

    i = 0;
    for (curdev = devlist; curdev != NULL; i++)
    {
        printf("Checking device: %d\n", i);
        if ((ret = ftdi_usb_get_strings(&ftdic, curdev->dev, manufacturer, 128, description, 128, NULL, 0)) < 0)
        {
            fprintf(stderr, "ftdi_usb_get_strings failed: %d (%s)\n", ret, ftdi_get_error_string(&ftdic));
            return EXIT_FAILURE;
        }
        printf("Manufacturer: %s, Description: %s\n\n", manufacturer, description);
        curdev = curdev->next;
    }

    ftdi_list_free(&devlist);
    ftdi_deinit(&ftdic);

    return EXIT_SUCCESS;
}
