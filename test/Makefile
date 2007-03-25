
OBJS= test_main.o \
	pixel_store_test.o

TARGET = unit_test
EXT = .exe
DEPENDS = $(OBJS:.o=.d)
INCLUDES = ../include
CXXFLAGS += -I$(INCLUDES) -g -Wall -Wunused -fno-default-inline
LIBS +=-lcppunit

.PHONY: clean depend test

all: $(TARGET)

test: all
	$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.d: %.cpp
	$(CXX) -I$(INCLUDES) -MM -MT $*.o $< > $@

depend: $(DEPENDS)

clean:
	rm -f $(OBJS) $(TARGET)$(EXT)

include $(DEPENDS)
