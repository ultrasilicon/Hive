#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Global.h"
#include "UsrData.h"
#include "HiveDoubleBuffer.h"

#include <libagio/file.h>
#include <libagio/timer.h>
#include <libagio/async_event.h>

#include <unordered_map>
#include <forward_list>

#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QFontDatabase>
#include <QHostInfo>
#include <QTimer>
#include <QUuid>

#include <QDebug>


class AppDataManager;

class AppDataManager final
    : public QThread
{
  Q_OBJECT

public:
  explicit AppDataManager(QObject *parent = nullptr);
  ~AppDataManager();

  void stop();

  static void pushInboundBuffer(NetPacket *packet);
  static void pushOutboundBuffer(NetPacket *packet);

  static bool isUsrNew(const QString &uuid);

  static QHash<QString, UsrData*> usr_data_hash;

  void onUsrEntered(UsrProfile &usrProfile);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessage &m, bool fromMe);
  void onUpdateAvailable();

protected:
  void run();

private:
  void wakeLoop(DoubleBuffer<NetPacket *> *buf);
  void readInboundNetBuffer(Agio::AsyncEvent*);
  void checkSettings(Agio::Timer *);

  inline void initVariable();
  inline void loadSettings();
  inline void loadUsrList();
  inline void loadUpdates();

  inline bool touchFile(const std::string &path);
  inline bool touchDir(const std::string &dir);
  inline QString makeUuid();
  inline QJsonDocument makeDefaultSettings();
  inline QJsonDocument makeUpdateJson(const int version[]);

  inline void updateUsr(const UsrProfile &p);
  inline void deleteUsr(const QStringList usrInfoStrList);
  void writeSettings();

  Agio::Loop *loop;
  Agio::AsyncEvent *read_inbound_async;
  bool inbound_net_buffer_reading = false;

  static DoubleBuffer<NetPacket*> net_buffer_in;
  static DoubleBuffer<NetPacket*> net_buffer_out;

  static std::map<QString, int*> settings_int_hash;
  static std::map<QString, QColor*> settings_qcolor_hash;
  static std::map<QString, QString*> settings_qstring_hash;
  static std::map<QString, bool*> settings_bool_hash;

signals:
  void updateAvailable();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(Message::TextMessage messageStrList, bool fromMe);
};


#endif // DATAMANAGER_H
