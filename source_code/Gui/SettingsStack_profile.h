#ifndef GUISETTINGSSTACK_PROFILE_H
#define GUISETTINGSSTACK_PROFILE_H

#include "Gui/Frameworks/ScrollStack.h"
#include "GlobalData.h"

#include <QListWidget>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>


class SettingsStack_profile : public ScrollStack
{
  Q_OBJECT

public:
  explicit SettingsStack_profile(QWidget *parent = 0);
  ~SettingsStack_profile();

private:
  QHash<QString , QString> avatar_hash;
  QList<QRadioButton *> avatar_radio_btn_list;
  AvatarComposer *avatar_composer;

private slots:
  void onRadioClicked(QAbstractButton *abstractButton);
  void onUsrNameChanged(QString usr_name);
};

#endif // GUISETTINGSSTACK_PROFILE_H
