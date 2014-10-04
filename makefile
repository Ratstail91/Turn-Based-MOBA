#for use on Windows:

#MKDIR=mkdir
#RM=del /y

OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C src
	$(MAKE) -C tools

debug: export CXXFLAGS+=-g
debug: clean all

release: export CXXFLAGS+=-static-libgcc -static-libstdc++
release: clean all package

#For use on my machine ONLY
package:
	rar a -r -ep Tortuga.rar $(OUTDIR)/*.exe  $(OUTDIR)/*.dll
	rar a -r Tortuga.rar rsc/* copyright.txt

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
