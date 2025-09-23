#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
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
    void editTaskDescription(int index, const QString& newDesc) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].setDescription(newDesc);
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
    void editTask(QListWidgetItem* item) {
        int currentRow = taskList->currentRow();
        if (currentRow < 0) {
            return;
        }

        QString currentText = todoList.getTasks()[currentRow].getDesc();
        QString newText = QInputDialog::getText(this, "Редактирование задачи", "Новое описание", QLineEdit::Normal, currentText);

        if (!newText.trimmed().isEmpty() && newText != currentText) {
            todoList.editTaskDescription(currentRow, newText.trimmed());
            updateTaskList();
        }

    }
    void removeTask() {
        int currentRow = taskList->currentRow();
        if (currentRow >= 0) {
            todoList.DelTask(currentRow);
            updateTaskList();
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

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QHBoxLayout *inputLayout = new QHBoxLayout();
        QHBoxLayout *btnLayout = new QHBoxLayout();
        
        taskList = new QListWidget();
        taskInput = new QLineEdit();
        addButton = new QPushButton("Добавить");
        removeButton = new QPushButton("Удалить");
        toggleButton = new QPushButton("Выполнено");
        clearButton = new QPushButton("Удалить выполненные");

        mainLayout->addWidget(taskList);
        mainLayout->addLayout(inputLayout);
        mainLayout->addLayout(btnLayout);

        inputLayout->addWidget(taskInput);
        inputLayout->addWidget(addButton);

        btnLayout->addWidget(removeButton);
        btnLayout->addWidget(toggleButton);
        btnLayout->addWidget(clearButton);
        
    }
    void connectSignals() {
        connect(addButton, &QPushButton::clicked, this, &MainWindow::SetTask);
        connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
        connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleTask);
        connect(clearButton, &QPushButton::clicked, this, &MainWindow::DelCompleted);
        connect(taskList, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);
    }
    void updateTaskList() {
        taskList->clear();
        for (const Task& task : todoList.getTasks()) {
            taskList->addItem(task.toString());
        }
    }
};


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window; window.show(); return app.exec();
    return 0;

}
#include "main.moc"