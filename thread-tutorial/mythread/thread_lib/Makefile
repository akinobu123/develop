# Makefile

# macros
SRCS      = CMutex.cpp CMutexAuto.cpp CCondVal.cpp\
            CQueue.cpp CThreadUseRunnable.cpp
OBJS      = $(SRCS:.cpp=.o)
TARGET    = libthread.so
CXX       = g++
CXXFLAGS  =  -O3 -Wall -fPIC
LDFLAGS   = -shared
LIBS      = -pthread

# rules
all:	$(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)
	@echo done.

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -c

clean:
	rm -rf *.o $(TARGET)


CThreadUseRunnable.h: IRunnable.h
CThreadUseRunnable.o: CThreadUseRunnable.h
CMutex.o: CMutex.h
CMutexAuto.o: CMutexAuto.h
CCondVal.o: CCondVal.h
CQueue.h: CCondVal.h
CQueue.o: CQueue.h
