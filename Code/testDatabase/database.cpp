#include <QtGui>
#include <QtSql>

#include "database.h"

//! [0]
TableEditor::TableEditor(const QString &tableName, QWidget *parent)
    : QDialog(parent)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /*model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Last name"));*/

//! [0] //! [1]
    QTableView *view = new QTableView;
    view->setModel(model);
//! [1]

//! [2]
    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
//! [2]

//! [3]
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(revertButton, SIGNAL(clicked()), model, SLOT(revertAll()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
//! [3]

//! [4]
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Database test"));
}
//! [4]

//! [5]
void TableEditor::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Database test"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}


Database::Database()
{
}

bool Database::connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gamedata.db3");
//    db.setDatabaseName(":memory");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    /*QSqlQuery query;
      query.exec("create table units (id int primary key, "
                 "name varchar(20), health int, attack int)");
      query.exec("insert into units values(1, 'Male', 10, 10)");
      query.exec("insert into units values(2, 'Female', 5, 5)");
      query.exec("insert into units values(3, 'Enemy', 6, 8)");
      query.exec("insert into units values(4, 'Boss', 20, 10)");

      query.exec("create table players (id int primary key, "
                 "name varchar(30), experiencePoints int)");
      query.exec("insert into players values(1, 'sleepwalker', 0)");*/

    /*QSqlQuery query;

    query.exec("create table sprites (id int primary key, "
                "name varchar(30), pixMap varchar(100), "
                "AP int, HP int, range int)");
    query.exec("insert into sprites values(1, 'Wizard', "
               "'sprites/wizard.png', 8, 8, 8)");
    query.exec("insert into sprites values(2, 'Monk', "
               "'sprites/buddhist.png', 6, 6, 6)");
    query.exec("insert into sprites values(3, 'Bard', "
               "'sprites/bard.png', 4, 4, 4)");
    query.exec("insert into sprites values(4, 'Desert Soldier', "
               "'sprites/desertsoldier.png', 4, 6, 8)");

    query.exec("create table players (id int primary key, "
               "name varchar(30), experiencePoints int)");
    query.exec("insert into players values(1, 'sleepwalker', 0)");*/

    return true;
}

int Database::show(QString &tableName)
{
    TableEditor editor(tableName);
    editor.show();
    return editor.exec();
}

int Database::userCount()
{
    QSqlTableModel model;
    model.setTable("players");
    model.select();
    return model.rowCount();
}

bool Database::addPlayer (QString playerName)
{
    QSqlQuery query;
    int numRows;

    query.exec("SELECT name FROM players WHERE id > 0");
    while (query.next())
    {

        QString name = query.value(0).toString();
        if (name==playerName)
            return false;
    }

    query.exec("SELECT id FROM players WHERE id > 0");
    QSqlDatabase defaultDB = QSqlDatabase::database();
    if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize))
    {
        numRows = query.size();
    }
    else
    {
        query.last();
        numRows = query.at() + 1;
    }
    numRows++;
    //query.exec("insert into players values(1, 'MA')");
    query.prepare("insert into players(id, name, experiencePoints) "
                  "values(:id, :name, :experiencePoints)");
    query.bindValue(":id", numRows);
    query.bindValue(":name", playerName);
    query.bindValue(":experiencePoints", 0);
    query.exec();

    return true;
}

QString Database::spriteName(int index) const
{
    QSqlQuery query;
    query.exec("SELECT name FROM sprites");
    query.seek(index-1);
    QString name = query.value(0).toString();
    return name;
}

const QPixmap Database::spritePixMap(int index) const
{
    QSqlQuery query;
    query.exec("SELECT pixMap FROM sprites");
    query.seek(index-1);
    QString fileName = query.value(0).toString();
    QPixmap pixMap;
    pixMap.load(fileName);
    return pixMap;
}

const int Database::spriteAP(int index) const
{
    QSqlQuery query;
    query.exec("SELECT AP FROM sprites");
    query.seek(index-1);
    int AP = query.value(0).toInt();
    return AP;
}

const int Database::spriteHP(int index) const
{
    QSqlQuery query;
    query.exec("SELECT HP FROM sprites");
    query.seek(index-1);
    int HP = query.value(0).toInt();
    return HP;
}

const int Database::spriteRange(int index) const
{
    QSqlQuery query;
    query.exec("SELECT range FROM sprites");
    query.seek(index-1);
    int range = query.value(0).toInt();
    return range;
}

Sprite Database::loadSprite(QString spriteName)
{
    Sprite sprite;
    QSqlTableModel model;
    model.setTable("sprites");
//    model.setFilter("id>0");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==spriteName)
        {
            sprite.AP=record.value("AP").toInt();
            sprite.HP=record.value("HP").toInt();
            sprite.range=record.value("range").toInt();
            sprite.name=record.value("name").toString();
            sprite.pixMap.load(record.value("pixMap").toString());
            break;
        }
    }

    return sprite;
}

QString Database::userName(int index) const
{
    QSqlQuery query;
    query.exec("SELECT name FROM players");
    query.seek(index-1);
    QString name = query.value(0).toString();
    return name;
}


