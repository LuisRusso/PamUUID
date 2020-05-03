/* BSD 2-Clause License */

/* Copyright (c) 2020, Luís M. S. Russo */
/* All rights reserved. */

/* Redistribution and use in source and binary forms, with or without */
/* modification, are permitted provided that the following conditions are met: */

/* 1. Redistributions of source code must retain the above copyright notice, this */
/*    list of conditions and the following disclaimer. */

/* 2. Redistributions in binary form must reproduce the above copyright notice, */
/*    this list of conditions and the following disclaimer in the documentation */
/*    and/or other materials provided with the distribution. */

/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE */
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE */
/* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL */
/* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR */
/* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER */
/* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#define _PAMUUID_VERSION "0.1.0-alpha.2"

#include <unistd.h>
#include <string.h>

/* __linux__       Defined on Linux */
/* __sun           Defined on Solaris */
/* __FreeBSD__     Defined on FreeBSD */
/* __NetBSD__      Defined on NetBSD */
/* __OpenBSD__     Defined on OpenBSD */
/* __APPLE__       Defined on Mac OS X */
/* __hpux          Defined on HP-UX */
/* __osf__         Defined on Tru64 UNIX (formerly DEC OSF1) */
/* __sgi           Defined on Irix */
/* _AIX            Defined on AIX */

#if defined(__linux__)
#define PAM_SM_AUTH
#include <security/pam_modules.h>
#include <security/pam_constants.h>
/* #include <security/pam_ext.h> */
#endif /* defined(__linux__) */

#if defined(__FreeBSD__)
#define PAM_SM_AUTH
#include <sys/types.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <syslog.h>
#include <stdarg.h>

void
pam_syslog(pam_handle_t *pamh,
	   int priority,
	   const char *fmt,
	   ...
	   )
{
  syslog(priority, "%s", fmt);
}
#endif /* defined(__FreeBSD__) */

/* Proper logging */
#include <syslog.h>

#define LENGTH(X)               (sizeof X / sizeof X[0])

enum authentication_method{ plain };

typedef struct rule Rule;
struct rule {
  const char *UserName;
  const char *Directory;
  const char *UUID;
  enum authentication_method Method;
};

/* Include user configuration */
#include "pam_uuid.h"

PAM_EXTERN
int pam_sm_authenticate(pam_handle_t *pamh,
			int flags,
			int argc,
			const char **argv
			)
{
  const char *user;
  const char *tty;

  pam_syslog(pamh, LOG_USER|LOG_DEBUG , "PamUUID: activated by authenticate.\n");

  if(pam_get_item(pamh, PAM_TTY,
		  (const void **)(const void *)&tty) != PAM_SUCCESS
     || (NULL != tty && 0 == strncmp(tty, "ssh", 3))
     ){
    pam_syslog(pamh, LOG_USER|LOG_DEBUG , "PamUUID: FAILED, call by ssh.\n");
    return (PAM_AUTH_ERR);
  }

  if (PAM_SUCCESS != pam_get_user(pamh, &user, NULL)
      || NULL == user
      || '\0' == *user
      ){
    pam_syslog(pamh, LOG_USER|LOG_DEBUG , "PamUUID: FAILED, unable to get user.\n");
    return (PAM_AUTH_ERR);
  }

  for(int i = 0; i < LENGTH(rules); i++){
    if(0 == strcmp(user, rules[i].UserName)){
      int k = 1;
      k += strlen(rules[i].Directory);
      k += strlen(rules[i].UUID);
      char FileName[k];
      FileName[0] = '\0';
      strcpy(FileName, rules[i].Directory);
      strcat(FileName, rules[i].UUID);

      if(0 == access(FileName, F_OK)){
	pam_syslog(pamh, LOG_USER|LOG_DEBUG , "PamUUID: Access granted.\n");
	return (PAM_SUCCESS);
      }
    }
  }

  pam_syslog(pamh, LOG_USER|LOG_DEBUG , "PamUUID: FAILED, no authentication rule.\n");
  return (PAM_AUTH_ERR);
}

PAM_EXTERN
int pam_sm_setcred(pam_handle_t *pamh,
		   int flags,
		   int argc,
		   const char **argv
		   )
{
  return (PAM_SUCCESS);
}
