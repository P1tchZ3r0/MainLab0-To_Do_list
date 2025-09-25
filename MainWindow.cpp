#include "MainWindow.h"
#include "todolist.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QCloseEvent>
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    todoList.loadFromSettings();
    setupUI();
    new QShortcut(QKeySequence::Delete, taskList, this, &MainWindow::removeTask);
    connectSignals();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    todoList.saveList();
    event->accept();
}

void MainWindow::showEvent(QShowEvent* event) {
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
    removeButton = new QPushButton("Удалить");
    toggleButton = new QPushButton("Выполнено");

    mainLayout->addWidget(taskList);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(btnLayout);

    inputLayout->addWidget(taskInput);

    btnLayout->addWidget(removeButton);
    btnLayout->addWidget(toggleButton);

    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
}

void MainWindow::connectSignals() {
    connect(taskInput, &QLineEdit::returnPressed, this, &MainWindow::SetTask);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleTask);
    connect(taskList, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);

}

void MainWindow::updateTaskList() {
    taskList->clear();
    for (const Task& task : todoList.getTasks()) {
        QListWidgetItem* item = new QListWidgetItem(task.toString());

        
        if (task.isCompleted()) {
            item->setBackground(QColor(144, 238, 144, 100)); 
            item->setForeground(Qt::darkGreen); 

            QFont font = item->font();
            font.setStrikeOut(true);
            item->setFont(font);
        }

        taskList->addItem(item);
    }
}
