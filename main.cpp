#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
class Task {
private:
    QString Desc;
    bool complete;
public:
    Task(const QString& desc = "", bool comp = false) : Desc(desc), complete(comp)
    {
    }
    //Геттеры
    QString getDesc() const { return Desc; }
    bool isCompleted() const { return complete; }
    //Сеттеры
    void setDescription(const QString& desc) { Desc = desc; }
    void setCompleted(bool comp) { complete = comp; }
    //Вывод GUI
    QString toString() const {
        return QString("%1 %2").arg(complete ? "[V]" : "[]").arg(Desc);
    }
};
class ToDoList {
private:
    QList<Task> tasks;
public:
    void SetTask(const QString& Desc) {
        tasks.append(Task(Desc));
    }
    void DelTask(int& index) {
        if (index >= 0 and index < tasks.size()) {
            tasks.removeAt(index);
        }
    }
    void CompleteTask(int& index) {
        if (index >= 0 and index < tasks.size()) {
            tasks[index].setCompleted(!tasks[index].isCompleted());
        }
    }
    const QList<Task>& getTasks() const {
        return tasks;
    }
};

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parrent = nullptr) : QWidget(parrent) {
        setupUI();
        connectSignals();
    }
private slots:
    void SetTask() {
        QString text = taskInput->text().trimmed();
        if (!text.isEmpty()) {
            todoList.SetTask(text);
            updateTaskList();
            taskInput->clear();
        }
    }
    void toggleTask() {
        int currentRow = taskList->currentRow();
        if (currentRow >= 0) {
            todoList.CompleteTask(currentRow);
            updateTaskList();
        }
    }
    void DelCompleted() {
        for (int i = todoList.getTasks().size() - 1; i >= 0; i--) {
            if (todoList.getTasks()[i].isCompleted()) {
                todoList.DelTask(i);
            }
        }
        updateTaskList();
    }
private:
    QListWidget* taskList;
    QLineEdit* taskInput;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* toggleButton;
    QPushButton* clearButton;
    ToDoList todoList;
    void setupUI() {

    }
    void connectSignals() {

    }
    void updateTaskList() {

    }
};


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window; window.show(); return app.exec();
    
    //Task task1("Первая", false);
    //Task task2("Вторая", true);

    //qDebug() << "Задача 1:" << task1.toString();
    //qDebug() << "Задача 2:" << task2.toString();

    //qDebug() << "\n=== ТЕСТ ГЕТТЕРОВ ===";
    //qDebug() << "Описание задачи 1:" << task1.GetDesc();
    //qDebug() << "Выполнена задача 1:" << task1.IsComplete();
    //qDebug() << "Описание задачи 2:" << task2.GetDesc();
    //qDebug() << "Выполнена задача 2:" << task2.IsComplete();

    //qDebug() << "\n=== ТЕСТ СЕТТЕРОВ ===";
    //task1.setDescription("Измененное описание");
    //task1.setCompleted(true);
    //qDebug() << "После изменений - Задача 1:" << task1.toString();



    return 0;



}
