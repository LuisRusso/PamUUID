# PamUUID 0.2.0-alpha.1

A PAM authentication module for Linux using USB Flash Drives. This module
will allow you to login to your system by inserting a USB drive, without
the need to type a password.

## Table of contents

- [Getting Started]
   - [Prerequisites]
   - [Installing]
       - [Linux Install]
       - [FreeBSD Install]
- [FAQ]
- [Contributing]
- [Versioning]
- [Authors]
- [License]
- [Acknowledgments]


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

This package was tested with [Debian] and [FreeBSD], it will most likely
work with other Linux distributions and UNIX variants. Some version of the
following components must exist in the system.

For Linux:

* [udev] (or similar, e.g., [eudev])
* C compiler, [gcc] or [clang]
* [GNU Make]
* [Linux-PAM]

For FreeBSD:

* [devd]
* C compiler, [gcc] or [clang]
* [Make]
* [PAM library]

### Installing

#### Linux Install

First check that you have the PAM library is installed. In [Debian] this can
be obtained by running:

```
apt-get install libpam0g-dev
```

Once this is installed you can check if everything is ok by compiling the
project. Simply execute

```
make
```

If all went well your build system is working. Otherwise if the PAM
lib is missing your compile will complain about this line.

`#include <security/pam_modules.h>`

Next determine if your system has the appropriate udev
components. List the directory `/dev/disk/by-uuid/` with:

```
ls /dev/disk/by-uuid/
```

This directory should exist. Otherwise you, most likely, do not have the
necessary components. Check with your distribution if it is located
elsewhere.

Now insert the pendrive you intend to use and list the directory
again. Check that a new file appears.

The name of the file corresponds to the uuid of the filesystem in the
drive. It will be unique to your system and it should have the folowing
format:

* For most filesystems 32 hex digits separated as
  xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx (version 4 UUIDs), e.g.,
  `7cec6c81-9eaa-44ad-8d6c-e607f3101627`.

* For vfat filesystems 8 hex digits separated as xxxx-xxxx, e.g.,
  `4059-33BB`.

For more info check [Wikipedia].

If several files appeared or you are unsure about the correct UUID to use
you can run the following command:

```
ls -lh /dev/disk/by-uuid/
```

This lists the devices associated to the UUIDs, for all the partitions in
your system.

You can now edit the file `pam_uuid.h` file. This file was created by the
initial make.

```
editor pam_uuid.h
```

Locate the following line:

`   {"John", "/dev/disk/by-uuid/", "7cec6c81-9eaa-44ad-8d6c-e607f3101627", plain},`

If your username is John then congratulations you only need to change the
UUID, the third entry in the list. Otherwise update the username also ;-)

You can also add more of these lines, for other users, or other pens.

For now the only authentication method is plain, so leave it.

Next compile the module. Run

```
make
```

After it compiles successfully you need to install it as root:

```
sudo make install
```

This copies the module to the `/lib/security` directory. You can list the
directory to make sure it is Ok. If the directory does not exist check with
your distribution and copy to the appropriate location.

The final step is authorizing the module. Edit the
`/etc/pam.d/common-auth` file as root.

```
sudo editor /etc/pam.d/common-auth
```

Add the following line before any other authorization:

```
auth sufficient pam_uuid.so
```

In this case the module becomes sufficient for authentication. You may use
more elaborated configurations, for example a two-factor authentication
process.

#### FreeBSD Install

First check that you have the PAM library is installed. Make sure you
installed the system with the dev option. You can check if everything is ok
by compiling the project. Simply execute

```
make
```

If all went well your build system is working. Otherwise if the PAM
lib is missing your compile will complain about this line.

`#include <security/pam_modules.h>`

Next determine if your system has the appropriate devd
components. List the directory `/dev/diskid/` with:

```
ls /dev/diskid/
```

In FreeBSD this directory might not exist and everything is Ok. The
directory will show up when you insert the pendrive.

Now insert the pendrive you intend to use and list the directory
again. Check that a new file appears.

In FreeBSD the file should look something like
`DISK-7CEC6C819EAA44AD8D6CE607` and is associated to the device not the
partition. In fact there should also be partition files that end in `s1`,
`s2`, etc.

You can now edit the file `pam_uuid.h` file. This file was created by the
initial make.

```
editor pam_uuid.h
```

Comment out the line:

`   {"John", "/dev/disk/by-uuid/", "7cec6c81-9eaa-44ad-8d6c-e607f3101627", plain},`

and uncomment the line

`   /* {"John", "/dev/diskid/", "DISK-7CEC6C819EAA44AD8D6CE607", plain}, */`

If your username is John then congratulations you only need to change the
diskid file, the third entry in the list. Otherwise update the username
also ;-)

You can also add more of these lines, for other users, or other pens.

For now the only authentication method is plain, so leave it.

Next compile the module. Run

```
make
```

After it compiles successfully you need to install it as root:

```
sudo make install
```

This copies the module to the `/usr/lib` directory. You can list the
directory to make sure it is Ok.

The final step is authorizing the module. Edit the file
`/etc/pam.d/login` as root.

```
sudo editor /etc/pam.d/login
```

Add the following line before any other authorization:

```
auth sufficient pam_uuid.so
```

In this case the module becomes sufficient for authentication. You may use
more elaborated configurations, for example a two-factor authentication
process.

## FAQ

> If I install this module can I still login with a password?

Yes. You just won't have to.

> This module is not what I wanted. How do I remove it?

If you want to remove it you need to call the makefile again as
root. Execute

```
sudo make deinstall
```

This deletes the module from the install directory. In case the module did
not met your expectations or you need some specific feature consider
creating an [issue] about it or emailing me [lmsrusso@gmail.com].

> This module is pretty cool. How can I help?

Share it with your friends. Consider creating an issue with suggestions or
just send a "thank you" email to [lmsrusso@gmail.com].

> Do I have to use an UUID ?

No. All that the module does is to check if the file exists in your
filesystem. Therefore you can use any file, whatsoever. That being said, it
is probably a bad idea to use a file that resides permanently in the
filesystem. However you may want to use the labels of the filesystems. In
linux these reside in `/dev/disk/by-label`. In this case you may need to
use [e2label] for ext filesystems or [fatlabel] for fat filesystems. In
FreeBSD you might want to look into [glabel].

If you have a spare pen you may want to use it as a backup authentication
pen. Just in case you lose your primary pen. In this case just use the same
label in both pens.

> How safe is PamUUID?

Depends on your usage. The module does not grant access to `ssh` logins.

If you have a pen that is registered in your `pam_uuid.h` it is
best not to insert it in any other computer, as the UUID and labels are
clearly accessible.

It is safer if you are using two factor authentication. In which case make
sure to have a backup authentication pen.

> This works for login but not for my screen saver?

Make sure to use a locker or screen saver that uses PAM, for example [sxlock].

## Contributing

If you found this project useful please share it, also you can create an
[issue] with comments and suggestions.

## Versioning

We use [SemVer] for versioning. For the versions available, see the [tags]
on this repository.

## Authors

* **Luís M. S. Russo** - *Initial work* - [LuisRusso]

See also the list of [contributors] who participated in this project.

## License

This project is licensed under the BSD 2-Clause "Simplified" License - see
the [LICENSE file] for details

## Acknowledgments

* This project was inspired by the [pamusb] project.
* This software uses a [suckless] approach.
* Thanks to [PurpleBooth] for the [README-Template].
* The [grip] tool by [Joe Esposito] was very handy for producing this file.


[Getting Started]: #getting-started
[Prerequisites]: #prerequisites
[Installing]: #installing
[Linux Install]: #linux-install
[FreeBSD Install]: #freebsd-install
[FAQ]: #faq
[Contributing]: #contributing
[Versioning]: #versioning
[Authors]: #authors
[License]: #license
[Acknowledgments]: #acknowledgments

[Debian]: https://www.debian.org/
[FreeBSD]: https://www.freebsd.org/
[udev]: https://en.wikipedia.org/wiki/Udev
[eudev]: https://wiki.gentoo.org/wiki/Eudev
[gcc]: https://gcc.gnu.org/
[clang]: https://clang.llvm.org/
[GNU Make]: https://www.gnu.org/software/make/
[Linux-PAM]: http://www.linux-pam.org/
[devd]: https://www.freebsd.org/cgi/man.cgi?query=devd&sektion=8&apropos=0&manpath=FreeBSD+12.1-RELEASE+and+Ports
[Make]: https://www.freebsd.org/doc/en/books/developers-handbook/tools-make.html
[PAM library]: https://www.freebsd.org/doc/en/articles/pam/article.html
[Wikipedia]: https://en.wikipedia.org/wiki/Universally_unique_identifier
[issue]: ../../issues
[lmsrusso@gmail.com]: mailto:lmsrusso@gmail.com
[e2label]: http://e2fsprogs.sourceforge.net
[fatlabel]: https://github.com/dosfstools/dosfstools
[glabel]: https://www.freebsd.org/cgi/man.cgi?query=glabel&sektion=8&manpath=freebsd-release-ports
[sxlock]: https://github.com/lahwaacz/sxlock
[SemVer]: http://semver.org/
[tags]: ../../tags
[LuisRusso]: https://github.com/LuisRusso
[contributors]: ../../contributors
[LICENSE file]: ./LICENSE
[pamusb]: http://www.pamusb.org/
[suckless]: https://suckless.org/
[PurpleBooth]: https://gist.github.com/PurpleBooth
[README-Template]: https://gist.github.com/PurpleBooth/109311bb0361f32d87a2
[grip]: https://github.com/joeyespo/grip
[Joe Esposito]: https://github.com/joeyespo
