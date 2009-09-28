TARGET=wxWin
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
CXXFLAGS= -g `wx-config --cxxflags` -I../../include
LIBS= -g `wx-config --libs` -I../../include

.PHONY:
	clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

.cpp.o: $(OBJS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
