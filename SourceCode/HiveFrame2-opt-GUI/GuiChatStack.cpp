#include "GuiChatStack.h"

//////////////////////////top//////////////////////////////////////
GuiChatStack_top_bar::GuiChatStack_top_bar(QStringList usrInfoStrList, QWidget *parent) : QWidget(parent)
{
  ///usrKey<<usrName<<ipAddr<<avatarPathr
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  /*QPalette palette;
  palette.setColor(QPalette::Background, QColor(192,253,123));
  //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
  setPalette(palette);
///from baidu
*/

  avatar_label = new GuiAvatarButton(usrInfoStrList[3], 90, this);
  avatar_label->setFixedHeight(50);
  avatar_label->setAlignment(Qt::AlignLeft);

  //
  QLabel *usr_name_label = new QLabel(usrInfoStrList[1]);
  QLabel *usr_ip_label = new QLabel(usrInfoStrList[2]);

  QFont usr_name_font("Futura");//Verdana
  usr_name_font.setPixelSize(15);
  usr_name_label->setFont(usr_name_font);

  QFont usr_ip_font("Futura");//Gill Sans
  usr_ip_font.setPixelSize(11);
  usr_ip_label->setFont(usr_ip_font);

  QVBoxLayout *usr_info_layout = new QVBoxLayout();
  usr_info_layout->setContentsMargins(0,0,10,10);
  usr_info_layout->addWidget(usr_name_label);
  usr_info_layout->addWidget(usr_ip_label);


  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->setContentsMargins(15,10,10,0);
  main_layout->setSpacing(10);
  main_layout->addWidget(avatar_label);
  main_layout->addLayout(usr_info_layout);

  this->setFixedHeight(67);



}

GuiChatStack_top_bar::~GuiChatStack_top_bar()
{

}

//////////////////////////mid//////////////////////////////////////

GuiChatStack_chat_widget::GuiChatStack_chat_widget(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);

  chat_bubble_layout = new QVBoxLayout();
  chat_bubble_layout->setAlignment(Qt::AlignTop);
  chat_bubble_layout->addStretch();
  chat_bubble_layout->setContentsMargins(5,30,5,30);

  ///lines
  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(4);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(4);
  top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setSpacing(5);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->addWidget(top_line);
  main_layout->addLayout(chat_bubble_layout);
  main_layout->addWidget(bottom_line);


}

GuiChatStack_chat_widget::~GuiChatStack_chat_widget()
{

}

void GuiChatStack_chat_widget::clearChatBubbles()
{
  foreach (GuiChatBubble *temp_chat_bubble_pointer, chat_bubble_list)
    {
      temp_chat_bubble_pointer->deleteLater();
    }
}

void GuiChatStack_chat_widget::addChatBubble(QString message, bool fromMe)
{
  gui_chat_bubble = new GuiChatBubble(message, !fromMe, this);
  chat_bubble_layout->addWidget(gui_chat_bubble);
  chat_bubble_list.append(gui_chat_bubble);
}

//////////////////////////bottom//////////////////////////////////////

GuiChatStack_message_editor::GuiChatStack_message_editor(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  text_editor = new QTextEdit(this);
  text_editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  text_editor->setFrameStyle(QFrame::NoFrame);

  QFont text_font("Gill Sans", 34);
  text_font.setPixelSize(16);
  text_editor->setFont(text_font);

  ///tools
  expression_label = new GuiLabelButton(this);
  image_label = new GuiLabelButton(this);
  file_label = new GuiLabelButton(this);

  expression_label->setDefaultPixmap(":/img/img/expression_label_0.png");
  expression_label->setHoveredPixmap(":/img/img/expression_label_1.png");
  //expression_label->setAlignment(Qt::AlignLeft);

  image_label->setDefaultPixmap(":/img/img/image_label_0.png");
  image_label->setHoveredPixmap(":/img/img/image_label_1.png");
  //image_label->setAlignment(Qt::AlignLeft);

  file_label->setDefaultPixmap(":/img/img/file_label_0.png");
  file_label->setHoveredPixmap(":/img/img/file_label_1.png");
  //file_label->setAlignment(Qt::AlignLeft);

  tool_layout = new QHBoxLayout();
  tool_layout->setAlignment(Qt::AlignLeft);
  tool_layout->setContentsMargins(0,5,5,5);
  tool_layout->setSpacing(15);
  tool_layout->addWidget(expression_label);
  tool_layout->addWidget(image_label);
  tool_layout->addWidget(file_label);

  edit_layout = new QVBoxLayout();
  edit_layout->setAlignment(Qt::AlignLeft);
  edit_layout->setContentsMargins(10,5,15,10);
  edit_layout->setSpacing(5);
  edit_layout->addLayout(tool_layout);
  edit_layout->addWidget(text_editor);

  ///send button
  send_btn = new GuiLabelButton();
  send_btn->setDefaultPixmap(":/img/img/send_button_0.png");
  send_btn->setHoveredPixmap(":/img/img/send_button_0.png");
  send_btn->setPressedPixmap(":/img/img/send_button_1.png");
  send_btn->setAlignment(Qt::AlignRight);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignBottom);
  main_layout->setContentsMargins(0,0,20,0);
  main_layout->setSpacing(0);
  main_layout->addLayout(edit_layout);
  main_layout->addWidget(send_btn);


  this->setMaximumHeight(130);
  this->setParent(parent);
}

GuiChatStack_message_editor::~GuiChatStack_message_editor()
{

}

void GuiChatStack_message_editor::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter)
    {
      //send_btn->setHovered();
      ////emit send!
    }
}

void GuiChatStack_message_editor::keyReleaseEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter)
    {
      send_btn->setDefault();
      ////emit send!
    }
}
//////////////////////////main//////////////////////////////////////

GuiChatStack::GuiChatStack(QStringList usrInfoStrList, QWidget *parent) : QWidget(parent)
{
  ///Data
  usr_info_str_list = usrInfoStrList;

  data_history_io = new DataHistoryIO(usrInfoStrList[0], this);
  refreshCurrentActiveIndex();

  ///UI
  top_bar = new GuiChatStack_top_bar(usr_info_str_list, this);

  chat_widget = new GuiChatStack_chat_widget(this);
  chat_scroll_area = new QScrollArea(this);
  chat_scroll_area->verticalScrollBar()->setMinimum(0);
  chat_scroll_area->verticalScrollBar()->setMaximum(500);
  chat_scroll_area->setWidgetResizable(true);
  chat_scroll_area->setWidget(chat_widget);
  QPalette palette = chat_scroll_area->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255,255));
  chat_scroll_area->setPalette(palette);
  chat_scroll_area->setFrameStyle(0);

  message_editor = new GuiChatStack_message_editor(this);


  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignCenter);
  main_layout->addWidget(top_bar);
  main_layout->addWidget(chat_scroll_area);
  main_layout->addWidget(message_editor);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

  connect(message_editor->send_btn, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));

  loadHistory(current_active_index);

  chat_scroll_area->verticalScrollBar()->setValue(500);

}

GuiChatStack::~GuiChatStack()
{

}

void GuiChatStack::refreshCurrentActiveIndex()
{
  current_active_index = data_history_io->currentActiveIndex();
}


///slots


void GuiChatStack::checkMessage(QStringList message_str_list)
{
//  QString object_key_str;//0收人
//  QString subject_key_str;//1发人
//  QString message_str;//2

  if(message_str_list[0] == GlobalData::g_myKeyStr
     && message_str_list[1] == usr_info_str_list[0])
    {
      chat_widget->addChatBubble(message_str_list[2], false);
      data_history_io->wirteMessage(message_str_list, false);
      //qDebug()<<message_str_list[0]<<message_str_list[2];
      //to me
    }
  if(message_str_list[0] == usr_info_str_list[0]
     && message_str_list[1] == GlobalData::g_myKeyStr)
    {
      chat_widget->addChatBubble(message_str_list[2], true);
      data_history_io->wirteMessage(message_str_list, true);
      //from me
    }
  refreshCurrentActiveIndex();

  chat_scroll_area->verticalScrollBar()->setValue(500);

}

void GuiChatStack::onSendButtonClicked()
{
  emit sendMessage(usr_info_str_list[0], message_editor->text_editor->toHtml());
  message_editor->text_editor->clear();
  chat_scroll_area->verticalScrollBar()->setValue(5000);

}

void GuiChatStack::loadHistory(int index)
{
  if(index <= current_active_index)
    {
      QJsonArray history_json_array = data_history_io->readMessage(index);
      for(int i = 0; i < history_json_array.count(); i++)
        {
          QJsonObject history_json_obj = history_json_array[i].toObject();
          chat_widget->addChatBubble(history_json_obj["message"].toString(), history_json_obj["fromMe"].toBool());
        }
      chat_scroll_area->verticalScrollBar()->setValue(500);

    }
  else
    {
      qDebug()<<"sth wrong happened!!!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
      return;
    }
}


