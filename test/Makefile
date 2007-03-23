
OBJS= test_main.o \
	pixel_store_test.o

TARGET= unit_test

DEPENDS= $(OBJS:.o=.d)
CXXFLAGS+= -I../include -g -Wall -Wunused -fno-default-inline
LIBS+=-lcppunit

.PHONY: %.d clean depend dependclean

all: $(TARGET)

test: all
	$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.d: %.cpp
	$(CXX)  -I../include -MM -MT $(<:.cpp=.o) $< > $(<:.cpp=.d)

clean:
	rm -f $(OBJS) $(TARGET)

depend: $(DEPENDS)

dependclean:
	rm -f $(DEPENDS)

include $(DEPENDS)