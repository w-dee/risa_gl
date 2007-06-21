
OBJS= \
	test_main.o \
	pixel_test.o \
	pixel_store_test.o \
	iterator_test.o \
	aligned_allocator_test.o \
	fragment_range_test.o \
	rectangle_test.o \
	memory_chunk_test.o \
	primitive_test.o \
	colormap_test.o

TARGET = unit_test
EXT = .exe
DEPENDS = $(OBJS:.o=.d)
INCLUDES = ../include
CXXFLAGS += -I$(INCLUDES) -g -Wall -msse2 -Wunused -fno-default-inline
LIBS +=-lcppunit

.PHONY: clean depend version

all: $(TARGET)

tests: all
	./$(TARGET)$(EXT)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.d: %.cpp
	$(CXX) -I$(INCLUDES) -MM -MT $*.o $< > $@

depend: $(DEPENDS)

clean:
	rm -f $(OBJS) $(TARGET)$(EXT)

version:
	$(CXX) --version

include $(DEPENDS)
