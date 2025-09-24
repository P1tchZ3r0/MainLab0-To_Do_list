#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
private:
    QString Desc;
    bool complete;

public:
    Task(const QString& desc = "", bool comp = false);

    QString getDesc() const;
    bool isCompleted() const;

    void setDescription(const QString& desc);
    void setCompleted(bool comp);

    QString toString() const;
};

#endif // TASK_H
