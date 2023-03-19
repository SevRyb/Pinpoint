#ifndef EMOJIWINDOW_H
#define EMOJIWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScrollArea>

class EmojiWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EmojiWindow(QWidget *parent = nullptr);
    ~EmojiWindow();
private:
    QVBoxLayout *m_mainVBoxLay;
    QScrollArea *m_scrollArea;
    QGridLayout *m_gridLay;
    QWidget *m_scrollAreaContainer;
signals:
    void insertEmoji(const QString &emoji);
};

#endif // EMOJIWINDOW_H
