# Makefile

# macros
CC       = g++
CFLAGS   = 
LDFLAGS  = -pthread -shared -fPIC
INCLUDES =
LIBS     =
TARGET   = libthread.so
OBJS     = CMutex.o CMutexAuto.o CCondVal.o\
           CQueue.o CThreadUseRunnable.o

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
