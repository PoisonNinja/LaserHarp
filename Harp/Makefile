CXX:=g++
CXXFLAGS:=-Wall -D__LINUX_ALSA__
LDFLAGS:=-lasound -lpthread -lrtmidi

all: server.c
	$(CXX) $(CXXFLAGS) -o server server.c $(LDFLAGS)
