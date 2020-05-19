# BSD 2-Clause License

# Copyright (c) 2020, Luís M. S. Russo
# All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.

# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.POSIX:
.PHONY: install deinstall clean

LIBDIR = $$( \
    case $$(uname -s) in \
        ( Linux ) echo '/lib/security' ;; \
        ( FreeBSD ) echo '/usr/lib' ;; \
        ( * ) echo './' ;; \
    esac )

pam_uuid.so: pam_uuid.c pam_uuid.h
	cc -fPIC -fno-stack-protector -c pam_uuid.c
	ld -x --shared -o pam_uuid.so pam_uuid.o

pam_uuid.h:
	cp template.h pam_uuid.h

# Run as root
install: pam_uuid.so
	if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR) ; fi
	cp pam_uuid.so $(LIBDIR)

clean:
	-rm -f pam_uuid.h.gch pam_uuid.o pam_uuid.so

deinstall:
	rm $(LIBDIR)/pam_uuid.so
