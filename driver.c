#include <linux/module.h>
#include <linux/input.h>
#include <linux/usb.h>
#include <linux/kernel.h>
#include <linux/init.h>       
#include "macropad.h"

#define MACROPAD_VENDOR_ID 0x1234  // demo vendor id
#define MACROPAD_PRODUCT_ID 0x5678  //demo product id // Both needed to register device with kernel

#define MACROPAD_KEY_A 0x01 // Demo key addresses to map in kernel space
#define MACROPAD_KEY_B 0x02
#define MACROPAD_KEY_C 0x03

#define compile_SIGNAL 44  // Custom signal number
#define terminal_SIGNAL 45  // Custom signal number
#define software_SIGNAL 46  // Custom signal number


extern void callForCompileExecute(void);
extern void splitTerminal(void);
extern void openSoftware(void);


static const unsigned short macropad_idmap[] = {
    MACROPAD_VENDOR_ID, MACROPAD_PRODUCT_ID,
    0
};

MODULE_DEVICE_TABLE(usb, macropad_idmap);

static struct usb_driver macropad_driver;

static int macropad_event(struct input_dev *dev, unsigned int type,
                          unsigned int code, int value)
{
    if (type == EV_KEY && value == 1) {
        switch (code) {
        case MACROPAD_KEY_A:
             // Send signal to user space when ENTER key is pressed
            kill_pid_info(compile_SIGNAL, SIGUSR1);

            break;
        case MACROPAD_KEY_B:
            kill_pid_info(terminal_SIGNAL, SIGUSR2);
            break;
        case MACROPAD_KEY_C:
            kill_pid_info(software_SIGNAL, SIGUSR3);
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

    // Allocating input device
    input_dev = devm_input_allocate_device(&interface->dev);
    if (!input_dev)
        return -ENOMEM;

    // Setting up input device
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

    // Registering input device
    error = input_register_device(input_dev);
    if (error)
        return error;

    // Saving input device in interface
    usb_set_intfdata(interface, input_dev);

    return 0;
}

static void macropad_disconnect(struct usb_interface *interface)
{
    struct input_dev *input_dev = usb_get_intfdata(interface);

    // Deregister input device
    input_unregister_device(input_dev);
}

static struct usb_driver macropad_driver = {
    .name = "macropad",
    .probe = macropad_probe,
    .disconnect = macropad_disconnect,
    .id_table = macropad_idmap,
};

module_usb_driver(macropad_driver);