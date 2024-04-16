#include <linux/module.h>
#include <linux/input.h>
#include <linux/usb.h>
#include <linux/kernel.h>

#define MACROPAD_VENDOR_ID 0x1234  /* Replace with your vendor ID */
#define MACROPAD_PRODUCT_ID 0x5678 /* Replace with your product ID */

#define MACROPAD_KEY_A 0x01
#define MACROPAD_KEY_B 0x02
#define MACROPAD_KEY_C 0x03

static const unsigned short macropad_idmap[] = {
    MACROPAD_VENDOR_ID, MACROPAD_PRODUCT_ID,
    0 /* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, macropad_idmap);

static struct usb_driver macropad_driver;

static int macropad_event(struct input_dev *dev, unsigned int type,
                          unsigned int code, int value)
{
    if (type == EV_KEY && value == 1) {
        switch (code) {
        case MACROPAD_KEY_A:
            compileExecute();
            break;
        case MACROPAD_KEY_B:
            langSwitch();
            break;
        case MACROPAD_KEY_C:
            openApp();
            break;
        default:
            break;
        }
    }

    return 0;
}

static int macropad_probe(struct usb_interface *interface,
                          const struct usb_device_id *id)
{
    struct usb_device *udev = interface_to_usbdev(interface);
    struct input_dev *input_dev;
    int error;

    /* Allocate input device */
    input_dev = devm_input_allocate_device(&interface->dev);
    if (!input_dev)
        return -ENOMEM;

    /* Set up input device */
    input_dev->name = "Macropad";
    input_dev->phys = "/macropad/input0";
    input_dev->id.bustype = BUS_USB;
    input_dev->id.vendor = MACROPAD_VENDOR_ID;
    input_dev->id.product = MACROPAD_PRODUCT_ID;
    input_dev->id.version = 0x0001;

    input_set_capability(input_dev, EV_KEY, MACROPAD_KEY_A);
    input_set_capability(input_dev, EV_KEY, MACROPAD_KEY_B);
    input_set_capability(input_dev, EV_KEY, MACROPAD_KEY_C);

    input_dev->event = macropad_event;

    /* Register input device */
    error = input_register_device(input_dev);
    if (error)
        return error;

    /* Save input device in interface */
    usb_set_intfdata(interface, input_dev);

    return 0;
}

static void macropad_disconnect(struct usb_interface *interface)
{
    struct input_dev *input_dev = usb_get_intfdata(interface);

    /* Deregister input device */
    input_unregister_device(input_dev);
}

static struct usb_driver macropad_driver = {
    .name = "macropad",
    .probe = macropad_probe,
    .disconnect = macropad_disconnect,
    .id_table = macropad_idmap,
};

module_usb_driver(macropad_driver);