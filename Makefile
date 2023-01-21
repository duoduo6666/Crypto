.PHONY: init clean
BUILDDIR	= build/
DISTDIR		= dist/
LIBDIR		= $(BUILDDIR)/lib/
LIBDIR_		= lib/
LIB			= SHA-1_x64
CC			= gcc
CBIT_FLAG	= -m64
CFLAGS		= -l $(LIB) -L $(LIBDIR) $(CBIT_FLAG) -Wl,-rpath,'$$ORIGIN/$(LIBDIR_)' -O3 
CDLL_FLAGS	=  $(CBIT_FLAG) -fPIC -shared -O3 

$(BUILDDIR)/crypto : $(LIBDIR)/libSHA-1_x64.so src/crypto.c
	$(CC) src/crypto.c $(CFLAGS) -o $(BUILDDIR)/crypto

$(LIBDIR)/libSHA-1_x64.so : src/SHA-1_x64.c
	$(CC) src/SHA-1_x64.c $(CDLL_FLAGS) -o $(LIBDIR)/libSHA-1_x64.so

init: clean
	mkdir -p $(BUILDDIR) $(LIBDIR) $(DISTDIR)
clean: 
	rm -r -f $(BUILDDIR)/crypto $(LIBDIR)/ $(DISTDIR)/

pack: $(BUILDDIR)/crypto
	cd $(BUILDDIR) && tar -cvf ../$(DISTDIR)/crypto-linux-amd64.tar ./*
