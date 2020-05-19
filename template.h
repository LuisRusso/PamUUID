/* This is the configuration file for PamUUID. */

/* Add users that you want to authenticate to the list bellow. */
/* The format is as described. An example is given for the user John. */
/* You may modify the given line. The other lines are comments. */

/* In version 0.2.0-alpha.1 the only available authentication method is plain. */

static const Rule rules[] =
  {
   /* {"UserName", "Directory", "UUID", "Authentication mode"}, */
   /* {"UserName", "/dev/disk/by-uuid/", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx", "plain"}, */

   /* Linux, udev */
   {"John", "/dev/disk/by-uuid/", "7cec6c81-9eaa-44ad-8d6c-e607f3101627", plain},

   /* FreeBSD, devd */
   /* {"John", "/dev/diskid/", "DISK-7CEC6C819EAA44AD8D6CE607", plain}, */

  };
