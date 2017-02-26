TOP=.
include $(TOP)/graphics.cfg

VPATH = obj


SOURCES = \
main.cpp \
Utils.cpp

# all the .o files need to be listed here.  Leave backslash off last list item
APPOBJS = \
$(VPATH)/main.o \
$(VPATH)/Utils.o

APPDEP = $(APPOBJS:.o=.d)
OBJECTS = $(APPOBJS)

APP = prog

# MAKEDEPEND = g++ -M $(CPPFLAGS) -o $*.d $<

all: $(APP)

# $(CXX) -MD creates a .d file and a .o file in the VPATH directory
$(APPDEP):      $(VPATH)/%.d:   %.cpp
	-mkdir -p $(VPATH)
	$(CXX) -MD $(CXXFLAGS)  -o $(@:.d=.o) $<

$(OBJECTS): $(VPATH)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(APP):  $(OBJECTS) 
	$(LD) -o $@ $(OBJECTS) $(GLIBS)

clean:
	rm -rf *.o *.d $(APP) $(VPATH)

# this generates errors on the first pass, but then these .d files
# get created for the second pass.  
include $(OBJECTS:.o=.d)
