#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include <QColor>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    setupUI();
    connectSignals();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    todoList.saveList();
    event->accept();
}

void MainWindow::showEvent(QShowEvent* event) {
    todoList.loadFromSettings();
    updateTaskList();
    QWidget::showEvent(event);
}

void MainWindow::SetTask() {
    QString text = taskInput->text().trimmed();
    if (!text.isEmpty()) {
        todoList.SetTask(text);
        updateTaskList();
        taskInput->clear();
    }
}

void MainWindow::editTask() {
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

void MainWindow::removeTask() {
    int currentRow = taskList->currentRow();
    if (currentRow >= 0) {
        todoList.DelTask(currentRow);
        updateTaskList();
    }
}

void MainWindow::toggleTask() {
    int currentRow = taskList->currentRow();
    if (currentRow >= 0) {
        todoList.CompleteTask(currentRow);
        updateTaskList();
    }
}

void MainWindow::DelCompleted() {
    for (int i = todoList.getTasks().size() - 1; i >= 0; i--) {
        if (todoList.getTasks()[i].isCompleted()) {
            todoList.DelTask(i);
        }
    }
    updateTaskList();
}

void MainWindow::setupUI() {
    setWindowTitle("To-Do List");
    resize(400, 500);
    setMinimumSize(300, 200);
    setMaximumSize(800, 600);

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(15);
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(0, 2);
    setGraphicsEffect(shadow);
    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* inputLayout = new QHBoxLayout();
    QHBoxLayout* btnLayout = new QHBoxLayout();

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

void MainWindow::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::SetTask);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleTask);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::DelCompleted);
    connect(taskList, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);
}

void MainWindow::updateTaskList() {
    taskList->clear();
    for (const Task& task : todoList.getTasks()) {
        taskList->addItem(task.toString());
    }
}