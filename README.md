# cmpe195_laztech
**Spring 2016 / Fall 2016**

LazTech is an upgrade kit for the K40 laser cutter/engraver. Both a new hardware motherboard and software printer drivers are included in this project.
## 1 Hardware
## 2 USB Device Side Code
### 2.1 Documentation
There is a lot of good documentaiton in the first link. Some of the documents are subsets of other documents.
* [MPLAB Harmony Integrated Software Framework Documentation](http://www.microchip.com/mplab/mplab-harmony) Note: Click the documentation tab.
  * [MPLAB Harmony Help Document](http://ww1.microchip.com/downloads/en/DeviceDoc/MPLAB%20Harmony%20Help%20%28v1.07.01%29.pdf)
    * [Creating Your Own USB Device Section](http://ww1.microchip.com/downloads/en/DeviceDoc/Volume%20IV%20-%20MPLAB%20Harmony%20Framework%20Reference%20(v1.07.01).pdf#14133)
* [USB Device Class Specifications](http://www.usb.org/developers/docs/devclass_docs/)
  * [USB Device Class Definition for Printing Devices](http://www.usb.org/developers/docs/devclass_docs/usbprint11a021811.pdf)

## 3 USB Host Side Driver
### 3.1 Kernel Source
This is the kernel we will be building our module against.
* [Linux kernel stable tree](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/)
* [Linux cross reference](http://lxr.free-electrons.com/) Note: This should take you to the lastest linux-stable version but if not, check what version the master branch is at on the git repo and use that on LXR.

### 3.2 Documentation
Here is some authoritative information on kernel module and usb host development.
* [Documentation](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/Documentation)
  * [Building External Modules](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/Documentation/kbuild/modules.txt)
  * [usb](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/Documentation/usb)

### 3.3 Headers / Sources
These are some of the core includes we will need to get our module and filesystem installed.
* [Include](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include)
  * [linux/module.h](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include/linux/module.h)
  * [linux/usb.h](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include/linux/usb.h)
  * [linux/usb](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include/linux/usb)
* [drivers/usb](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb) Note: There is a lot of information in this directory. Check the README.
  * [README](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb/README)
  * [class/usblp.c](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb/class/usblp.c)

### 3.4 Example USB Drivers
These are some links to different usb drivers that can be used for reference.
* [drivers/usb](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb)
  * FTDI USB Single Port Serial Converter (This is what is on almost all of our dev boards.)
    * [serial/ftdi_sio.h](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb/serial/ftdi_sio.h)
    * [serial/ftdi_sio.c](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/drivers/usb/serial/ftdi_sio.c)

### 3.5 Debugging
* strace (user space tracing)
  * [Ubuntu manuals - strace(1)](http://manpages.ubuntu.com/manpages/wily/en/man1/strace.1.html)
* ftrace (kernel space tracing)
  * [LWN.net - Debugging the kernel using Ftrace - part 1](https://lwn.net/Articles/365835/)
  * [LWN.net - Debugging the kernel using Ftrace - part 2](https://lwn.net/Articles/366796/)
  * `echo ":mod:<your_mod_name>" > set_ftrace_filter` is really useful.
