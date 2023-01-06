.PHONY: init clean
OUTDIR		= dist/
LIBDIR		= $(OUTDIR)/lib/
LIBDIR_		= lib/
LIB			= SHA-1_x64
CC			= gcc
CBIT_FLAG	= -m64
CFLAGS		= -l $(LIB) -L $(LIBDIR) $(CBIT_FLAG) -Wl,-rpath,$$ORIGIN/$(LIBDIR_) -O3 
CDLL_FLAGS	=  $(CBIT_FLAG) -fPIC -shared -O3 

$(OUTDIR)/crypto : $(LIBDIR)/libSHA-1_x64.so src/crypto.c
	$(CC) src/crypto.c $(CFLAGS) -o $(OUTDIR)/crypto

$(LIBDIR)/libSHA-1_x64.so : src/SHA-1_x64.c
	$(CC) src/SHA-1_x64.c $(CDLL_FLAGS) -o $(LIBDIR)/libSHA-1_x64.so

init: clean
	mkdir -p $(OUTDIR) $(LIBDIR)
clean: 
	rm -r -f $(OUTDIR)/crypto $(LIBDIR)/
