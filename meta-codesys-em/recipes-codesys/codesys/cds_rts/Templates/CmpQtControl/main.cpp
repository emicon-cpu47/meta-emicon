#include <qapplication.h>
#include <qpushbutton.h>
#include <QtGui>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
  int qt_show_Message(void *handle);
  void *qt_create_dialog(void *handle, int tx, int ty, int bx, int by);
  void qt_move_dialog(void *handle, int x, int y);
  void qt_show_dialog(void *handle);
  void qt_hide_dialog(void *handle);
}
#endif

int qt_show_Message(void *handle)
{
  int x, y;
  QWidget *pQWidget =(QWidget *)handle;

/*
  QMessageBox::about(pQWidget,"About CmpQtControl", 
  "This Component was coded for educational purposes.\n");
*/
  x = pQWidget->x();
  y = pQWidget->y();
  printf("Window position: x = %d, y = %d\n", x, y);

 return 0;
}

void *qt_create_dialog(void *handle, int tx, int ty, int bx, int by)
{
  QWidget *pQWidget =(QWidget *)handle;

  QFileDialog *pdialog = new QFileDialog(pQWidget);
  pdialog->setFileMode(QFileDialog::AnyFile);
  pdialog->setGeometry( tx, ty, bx-tx, by-ty );
  pdialog->setModal(0);
  pdialog->hide();
  
  return pdialog;  
}

void qt_hide_dialog(void *handle)
{
  ((QFileDialog*)handle)->hide();
}

void qt_show_dialog(void *handle)
{
  ((QFileDialog*)handle)->show();
}

void qt_move_dialog(void *handle, int x, int y)
{
  QFileDialog *pdialog = (QFileDialog *)handle;
  
  pdialog->move(x, y);
  printf("Move to %d, %d\n", x, y);
}

