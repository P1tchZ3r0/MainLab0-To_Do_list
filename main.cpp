#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
class Task {
private:
    QString Desc;
    bool complete;
public:
    Task(const QString& desc = "", bool comp = false) : Desc(desc), complete(comp)
    {
    }
    //Геттеры
    QString GetDesc() const { return Desc; }
    bool IsComplete() const { return complete; }
    //Сеттеры
    void setDescription(const QString& desc) { Desc = desc; }
    void setCompleted(bool comp) { complete = comp; }
    //Вывод GUI
    QString ToString() const {
        return QString("%1 %2").arg(complete ? "[V]" : "[]").arg(Desc);
    }
};

int main(int argc, char* argv[]) {

}