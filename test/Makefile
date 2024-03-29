
CPPS = $(wildcard *_test.cpp) test_main.cpp

OBJS = $(CPPS:.cpp=.o)

TARGET = unit_test
EXT = .exe
DEPENDS = $(OBJS:.o=.d)
INCLUDES = ../include
CXXFLAGS += -I$(INCLUDES) -O0 -g -Wall -Wunused -fno-default-inline
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
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXT) $(OBJS) $(LIBS) $(LIBCPPUNIT)

%.d: %.cpp
	$(CXX) -I$(INCLUDES) -MM -MT $*.o $< > $@

depend: $(DEPENDS)

clean:
	rm -f $(OBJS) $(TARGET)$(EXT)

dependclean:
	rm -f $(DEPENDS)

version:
	$(CXX) --version

performance_test_mt: performance/performance_test.cpp
	$(CXX) $(PERF_FLAGS) -DMT -DNDEBUG -O3 --param inline-unit-growth=2000 --param large-function-growth=2000 --param max-inline-insns-single=2000 -D_WIN32_WINNT=0x0501 -I../include -I../../cpp_lib -Winline -Wall $(LIBS) -o $@ $< 

performance_test: performance/performance_test.cpp
	$(CXX) $(PERF_FLAGS) -O3 -DNDEBUG --param inline-unit-growth=2000 --param large-function-growth=2000 --param max-inline-insns-single=2000 -D_WIN32_WINNT=0x0501 -I../include -I../../cpp_lib -Winline -Wall $(LIBS) -o $@ $< 


-include $(DEPENDS)
