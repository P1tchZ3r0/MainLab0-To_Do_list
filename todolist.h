#ifndef TODOLIST_H
#define TODOLIST_H

#include <QList>
#include <QSettings>
#include "task.h"

class ToDoList {
private:
    QList<Task> tasks;

public:
    void SetTask(const QString& Desc);
    void DelTask(int index);
    void editTaskDescription(int index, const QString& newDesc);
    void CompleteTask(int index);
    void saveList();
    void loadFromSettings();
    const QList<Task>& getTasks() const;
};

#endif // TODOLIST_H