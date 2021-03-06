#ifndef GUIMAINBLOCK_H
#define GUIMAINBLOCK_H

#include "GlobalType.h"
#include "ChatStack.h"
#include "Gui/Frameworks/Widgets/ColorPicker.h"

#include "HomeStack_welcome.h"
#include "HomeStack_list.h"
#include "HomeStack_storage.h"
#include "SettingsStack_messaging.h"
#include "SettingsStack_profile.h"
#include "SettingsStack_questions.h"
#include "SettingsStack_update.h"

#include <QStackedWidget>


class MainBlock : public QWidget
{
  Q_OBJECT

public:
  explicit MainBlock(QWidget *parent = nullptr);
  ~MainBlock();

  ChatStack *chat_stack;
  QStackedWidget *stacked_widget;
  HomeStack_welcome *home_stack_welcome;
  HomeStack_list *home_stack_list;

  void displayStaticStack(GUI::StaticStackType staticStackType);
  void displayChatStack(const QString &usrKey);

private:
  GUI::StaticStackType current_static_stack_type = GUI::StaticStackType::NULL_Stack;
  QHash<GUI::StaticStackType, QWidget*> static_stack_hash;

  void onMessageToSend(QString *usrKey, QString *message);
  void clearStackMap(GUI::StaticStackType &reservation);
  inline void createStaticStack(GUI::StaticStackType staticStackType);

signals:
  void sendMessage(QString usrKey, QString message);
};

#endif // GUIMAINBLOCK_H
