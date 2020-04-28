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
be unique to your system and it should have the folowing format:

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

You can now edit the file pam_uuid.h file. Locate this line.

{"John", "/dev/disk/by-uuid/", "7cec6c81-9eaa-44ad-8d6c-e607f3101627", plain},

If your username is John then congratulations you only need to change the
UUID, the third entry in the list. Otherwise update the username also ;-)

For now the only authentication method is plain, so leave it.

We are now ready to compile the module, run

```
make
```

After it compiles successfully. You now need to install it as root:

```
sudo make install
```

This copies the module to the /lib/security directory. You can list the
directory to make sure it is Ok. If the directory does not exist check with
your distribution and copy to the appropriate location.

The final step is authorizing the module edit the /etc/pam.d/common-auth
file. Add the following line before any other authorization:

```
auth sufficient pam_uuid.so
```

In this case the module become sufficient for authentication. You may use
more elaborated configurations, for example in a two-factor authentication
process, check this
[Guide](http://www.linux-pam.org/Linux-PAM-html/Linux-PAM_SAG.html).

## Post Install

If you want to remove this module just execute as root

```
make deinstall
```

This deletes the module from the /lib/security directory. In case this
application did not met your expectations or you need some specific feature
consider creating an issue about it.

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
