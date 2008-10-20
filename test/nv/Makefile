
CPPS = $(wildcard *_test.cpp) test_main.cpp
LIBS = 
OBJS = $(CPPS:.cpp=.o)

TARGET = unit_test
EXT = .exe
DEPENDS = $(OBJS:.o=.d)
INCLUDES = ../../include
OPTIMIZE = -O0
CXXFLAGS += -I$(INCLUDES) -mthreads $(OPTIMIZE) -g -Wall -Wunused -fno-default-inline
ifeq ($(CXX),g++-dw2)
LIBCPPUNIT = -lcppunit-dw2
else
LIBCPPUNIT= -lcppunit
endif

.PHONY: clean depend version dependclean

all: $(TARGET)$(EXT)

check: all
	./$(TARGET)$(EXT)

$(TARGET)$(EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXT) $(OBJS) $(LIBCPPUNIT) $(LIBS)

%.d: %.cpp
	$(CXX) -I$(INCLUDES) -MM -MT $*.o $< > $@

depend: $(DEPENDS)

clean:
	rm -f $(OBJS) $(TARGET)$(EXT)

dependclean:
	rm -f $(DEPENDS)

version:
	$(CXX) --version

-include $(DEPENDS)
