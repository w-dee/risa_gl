
OBJS= \
	test_main.o \
	pixel_test.o \
	pixel_store_test.o \
	iterator_test.o \
	aligned_allocator_test.o \
	fragment_range_test.o \
	rectangle_test.o \
	memory_chunk_test.o \
	colormap_test.o \
	alpha_copy_test.o \
	color_copy_test.o \
	alpha_blend_test.o \
	building_blocks_test.o \
	add_blend_test.o \
	add_alpha_blend_test.o \

TARGET = unit_test
EXT = .exe
DEPENDS = $(OBJS:.o=.d)
INCLUDES = ../include
CXXFLAGS += -I$(INCLUDES) -g -Wall -Wunused -fno-default-inline
LIBS +=-lcppunit

.PHONY: clean depend version dependclean

all: $(TARGET)$(EXT)

check: all
	./$(TARGET)$(EXT)

$(TARGET)$(EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXT) $(OBJS) $(LIBS)

%.d: %.cpp
	$(CXX) -I$(INCLUDES) -MM -MT $*.o $< > $@

depend: $(DEPENDS)

clean:
	rm -f $(OBJS) $(TARGET)$(EXT)

dependclean:
	rm -f $(DEPENDS)

version:
	$(CXX) --version

include $(DEPENDS)
