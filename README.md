# PamUUID

A PAM authentication module for Linux using USB Flash Drives. This module
will allow you to login to your system by insert a USB drive and with the
needing to type a password.

## Getting Started

To get a copy of this software download or clone the GitHub repository.

Download:

```
wget https://github.com/LuisRusso/PamUUID/archive/master.zip
```

Clone:

```
git clone git@github.com:LuisRusso/PamUUID.git
```

### Prerequisites

The following components are used to install and run this software.

* linux and systemd (or similar)
* gcc, GNU compiler collection
* GNU Make
* Linux-PAM (http://www.linux-pam.org/)

### Installing

First check that you have the Linux-PAM lib installed. In Debian this can
be obtained by running:

```
apt-get install libpam0g-dev
```

Once this is installed you can check if everything is ok by compiling the
project. Simply execute

```
make
```

If all went well your build system is working with Linux-PAM, gcc, make,
etc. Otherwise it the Linux-PAM lib is missing your compile will complain
about this line.

#include <security/pam_modules.h>

Next determine if your system has the appropriate linux, systemd, udev
components first list the directory /dev/disk/by-uuid/ with:

```
ls /dev/disk/by-uuid/
```

If this directory does not exist then most likely you do not have the
necessary components, but check with your distribution if it is located
elsewhere. If the directory exists then insert the pendrive you intend to
use and list the directory again. Check that a new file appears. The name
of the file corresponds to the uuid of the filesystem in the drive. It will
be unique to your system but it should have the folowing format:

* For most filesystems 32 hex digits separated as
  xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx (version 4 UUIDs), e.g.,
  7cec6c81-9eaa-44ad-8d6c-e607f3101627.

* For vfat filesystems 8 hex digits separated as xxxx-xxxx, e.g.,
  4059-33BB.

For more info check
[Wikipedia](https://en.wikipedia.org/wiki/Universally_unique_identifier).

If several files appeared or you are unsure about the correct UUID to use

```
ls -lh /dev/disks/by-uuid/
```

This lists the devices associated to the UUIDs, for all the partitions in
your system.

You can now edit the file pam_uuid.h file.

TODO ...


A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Contributing

If you found this project useful please share it, also you can create an
[issue](https://github.com/LuisRusso/PamUUID/issues) with comments and
suggestions.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions
available, see the [tags on this
repository](https://github.com/your/project/tags).

## Authors

* **Luís M. S. Russo** - *Initial work* -
    [LuisRusso](https://github.com/LuisRusso)

See also the list of
[contributors](https://github.com/your/project/contributors) who
participated in this project.

## License

This project is licensed under the BSD 2-Clause "Simplified" License - see
the [LICENSE](LICENSE) file for details

## Acknowledgments

* This project was inspired by the [pamusb](http://www.pamusb.org/) project.
* This software uses a [suckless](https://suckless.org/) approach.


then do

make
make install

Now edit the file /etc/pam.d/common-auth

Add as first command line in file

auth sufficient pam_uuid.so

Finally test some login

TODO, modify makefile so that the resulting file is not executable,
just an so

Edit the main and main.c so it is more robust.
