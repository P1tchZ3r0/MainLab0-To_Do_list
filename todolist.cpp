#include "todolist.h"

void ToDoList::SetTask(const QString& Desc) {
    tasks.append(Task(Desc));
}

void ToDoList::DelTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.removeAt(index);
    }
}

void ToDoList::editTaskDescription(int index, const QString& newDesc) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].setDescription(newDesc);
    }
}

void ToDoList::CompleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].setCompleted(!tasks[index].isCompleted());
    }
}

void ToDoList::saveList() {
    QSettings settings("P1tch_z3r0", "To-Do List");
    settings.beginWriteArray("Tasks");
    for (int i = 0; i < tasks.size(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("desc", tasks[i].getDesc());
        settings.setValue("completed", tasks[i].isCompleted());
    }
    settings.endArray();
}

void ToDoList::loadFromSettings() {
    QSettings settings("P1tch_z3r0", "To-Do List");
    int size = settings.beginReadArray("Tasks");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString desc = settings.value("desc").toString();
        bool completed = settings.value("completed").toBool();
        tasks.append(Task(desc, completed));
    }
    settings.endArray();
}

const QList<Task>& ToDoList::getTasks() const {
    return tasks;
}