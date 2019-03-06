#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include "libParsley/PTimer.h"
#include "libParsley/PUdpSocket.h"


#include "HiveProtocol.h"

class HiveUdpServer
  : public Parsley::UdpSocket
{
public:
  HiveUdpServer(const char *ip, const int &port, Parsley::Loop *l);
  ~HiveUdpServer();

  void start();
  void stop();

private:
  void onTimedOut(Parsley::Timer* t);

};

#endif // HIVEUDPSERVER_H
