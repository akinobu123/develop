# Makefile

# macros
CC       = g++
CFLAGS   = 
LDFLAGS  = -pthread -shared -fPIC
INCLUDES =
LIBS     =
TARGET   = libthread.so
OBJS     = CQueue.o CCondVal.\
           CMutexAuto.o CMutex.o oCThreadUseRunnable.o

# rules
all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


CThreadUseRunnable.h: IRunnable.h
CThreadUseRunnable.o: CThreadUseRunnable.h
CMutex.o: CMutex.h
CMutexAuto.o: CMutexAuto.h
CCondVal.o: CCondVal.h
CQueue.h: CCondVal.h
CQueue.o: CQueue.h
