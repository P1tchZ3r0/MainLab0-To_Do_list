#include "task.h"

Task::Task(const QString& desc, bool comp) : Desc(desc), complete(comp) {}

QString Task::getDesc() const {
    return Desc;
}

bool Task::isCompleted() const {
    return complete;
}

void Task::setDescription(const QString& desc) {
    Desc = desc;
}

void Task::setCompleted(bool comp) {
    complete = comp;
}

QString Task::toString() const {
    return QString("%1").arg(Desc);
}