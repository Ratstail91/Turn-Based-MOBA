#config
INCLUDES+=.
LIBS+=
CXXFLAGS+=-std=c++11 $(addprefix -I,$(INCLUDES))

#objects
OBJDIR=obj
OBJ+=$(addprefix $(OBJDIR)/,$(CXXSRC:.cpp=.o))

#output
OUTDIR=../out

#targets
flip: flip.o $(OUT)
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/$@ $< $(LIBS)

$(OBJ): | $(OBJDIR)

$(OUT): | $(OUTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
