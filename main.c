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


/* ******************************************************** */
/* Edit this string to the correct UUID and EVDEV directory */
#define UUIDFILE "/dev/disk/by-uuid/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"

/* ******************************************************** */

#include <stdio.h>
#include <unistd.h>

#define PAM_SM_AUTH
#include <security/pam_modules.h>
#include <security/_pam_macros.h>

/* Proper logging */
#include <syslog.h>
#include <security/pam_ext.h>

PAM_EXTERN
int pam_sm_authenticate(pam_handle_t *pamh,
			int flags,
			int argc,
			const char **argv
			)
{
  const char *user;
  const char *tty;
  int retval; /* Store return values from functions. */

  pam_syslog(pamh, LOG_USER|LOG_DEBUG , "No worries for now.\n");

  if (PAM_SUCCESS != pam_get_user(pamh, &user, NULL)
      || NULL == user
      || '\0' == *user
      || 0 != strncmp(user, "xxxx", 3)
      ){
    pam_syslog(pamh, LOG_USER|LOG_DEBUG , "Unable to get pam user.\n");
    return (PAM_AUTH_ERR);
  }

  if(pam_get_item(pamh, PAM_TTY,
  		  (const void **)(const void *)&tty) != PAM_SUCCESS
     || (NULL != tty && 0 == strncmp(tty, "ssh", 3))
     ){
    return (PAM_AUTH_ERR);
    }

  if(!access(UUIDFILE, F_OK)){
    return (PAM_SUCCESS);
  }

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
