# Makefile

# macros
SRCS      = CRunnable.cpp main.cpp
OBJS      = $(SRCS:.cpp=.o)
TARGET    = sample1.out
CXX       = g++
CXXFLAGS  =  -O3 -Wall -fPIC
LDFLAGS   = 
INCLUDES  = -I../thread_lib -I.
LIBS      = -L../thread_lib -lthread -pthread

# rules
all:	$(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)
	@echo done.

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -c

clean:
	rm -rf *.o $(TARGET)
