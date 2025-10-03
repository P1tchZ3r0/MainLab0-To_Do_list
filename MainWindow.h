#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include "todolist.h"
#include <QShortcut>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;
    void showEvent(QShowEvent* event) override;

private slots:
    void SetTask();
    void editTask();
    void removeTask();
    void toggleTask();

private:
    QShortcut* deleteShortcut = nullptr;
    QListWidget* taskList;
    QLineEdit* taskInput;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* toggleButton;
    QPushButton* clearButton;
    ToDoList todoList;

    void setupUI();
    void connectSignals();
    void updateTaskList();
};

#endif // MAINWINDOW_H