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
    QSqlQuery query;
      /*query.exec("create table units (id int primary key, "
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

    query.exec("create table user (id int primary key, "
               "name varchar(30), experiencePoints int, isActive int, level int)");
    query.exec("insert into user values(1, 'sleepwalker', 0, 0, 1)");

create table save1 (id int primary key, imageFileName varchar(100), faceLeft int, vLocation int, hLocation int, hitPoints int, totalHitPoints int, actionTime numeric, actionRate int, movementRange int, attackRange int, attackPower int, status int, maskFileName varchar(100), team int, unitWorth int)

insert into save1 values(1, 'image', 1, 1, 1, 1, 2, 1.1, 1, 1, 1, 1, 2, 'mask', 1, 1)

    query.exec("create table save1 (id int primary key, imageFileName varchar(100),"
               "faceLeft int, vLocation int, hLocation int, hitPoints int,"
               "totalHitPoints int, actionTime numeric, actionRate int, "
               "movementRange int, attackRange int, attackPower int, "
               "status int, maskFileName varchar(100), team int, unitWorth int)");
    query.exec("insert into save1 values(1, 'image', 1, 1, 1, 1, 2, 1.1, 1, 1, 1, 1, 2, 'mask', 1, 1)");*/


    /*create table sprite (id int primary key, name varchar(30), imageFileName varchar(100), maskFileName varchar(100),  attackPower int, attackRange int, hitPoints int, actionRate int, actionTime numeric,  movementRange int, rate int)
    insert into sprite values(1, 'Wizard', 'sprites/wizard.png', 'sprites/mask_wizard.png', 8, 4, 6, 4, 4, 4, 2);
    insert into sprite values(2, 'Monk', 'sprites/buddhist.png', 'sprites/mask_buddhist.png', 1, 2, 3, 5, 6, 7, 8);
    insert into sprite values(3, 'Bard', 'sprites/bard.png', 'sprites/mask_bard.png', 2, 2, 2, 4, 4, 4, 4);
    insert into sprite values(4, 'Desert Soldier', 'sprites/desertsoldier.png', 'sprites/mask_desertsoldier.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(5, 'Valkyrie', 'sprites/valkyrie.png', 'sprites/mask_valkyrie.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(6, 'Thai Boxer', 'sprites/thaiboxer.png', 'sprites/mask_thaiboxer.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(7, 'Merchant', 'sprites/merchant.png', 'sprites/mask_merchant.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(8, 'Knight', 'sprites/knight.png', 'sprites/mask_knight.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(9, 'Crusader', 'sprites/crusader.png', 'sprites/mask_crusader.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(10, 'Criminal', 'sprites/criminal.png', 'sprites/mask_criminal.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(11, 'Assassin', 'sprites/assassin.png', 'sprites/mask_assassin.png', 4, 4, 4, 6, 6, 6, 6);
    insert into sprite values(12, 'Berserker', 'sprites/berserker.png', 'sprites/mask_berserker.png', 4, 4, 4, 6, 6, 6, 6);*/

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

bool Database::addUser(User user)
{
    QSqlQuery query;
    int numRows;

    query.exec("SELECT name FROM user WHERE id > 0");
    while (query.next())
    {

        QString name = query.value(0).toString();
        if (name==user.name)
            return false;
    }

    query.exec("SELECT id FROM user WHERE id > 0");
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
    query.prepare("insert into user(id, name, experiencePoints, isActive, level) "
                  "values(:id, :name, :experiencePoints, :isActive, :level)");
    query.bindValue(":id", numRows);
    query.bindValue(":name", user.name);
    query.bindValue(":experiencePoints", user.experiencePoints);
    query.bindValue(":isActive", user.isActive);
    query.bindValue(":level", user.level);
    query.exec();

    return true;
}

bool Database::addUser (QString userName)
{
    QSqlQuery query;
    int numRows;

    query.exec("SELECT name FROM user WHERE id > 0");
    while (query.next())
    {

        QString name = query.value(0).toString();
        if (name==userName)
            return false;
    }

    query.exec("SELECT id FROM user WHERE id > 0");
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
    query.prepare("insert into user(id, name, experiencePoints, isActive, level) "
                  "values(:id, :name, :experiencePoints, :isActive, :level)");
    query.bindValue(":id", numRows);
    query.bindValue(":name", userName);
    query.bindValue(":experiencePoints", 0);
    query.bindValue(":isActive", 0);
    query.bindValue(":level", 1);
    query.exec();

    return true;
}

QString Database::spriteName(int index) const
{
    QSqlQuery query;
    query.exec("SELECT name FROM sprite");
    query.seek(index-1);
    QString name = query.value(0).toString();
    return name;
}


QString Database::spriteFileName(int index) const
{
    QSqlQuery query;
    query.exec("SELECT imageFileName FROM sprite");
    query.seek(index-1);
    QString fileName = query.value(0).toString();
    return fileName;
}

const int Database::spriteAttackPower(int index) const
{
    QSqlQuery query;
    query.exec("SELECT attackPower FROM sprite");
    query.seek(index-1);
    int AP = query.value(0).toInt();
    return AP;
}

const int Database::spriteHitPoints(int index) const
{
    QSqlQuery query;
    query.exec("SELECT hitPoints FROM sprite");
    query.seek(index-1);
    int HP = query.value(0).toInt();
    return HP;
}

const int Database::spriteAttackRange(int index) const
{
    QSqlQuery query;
    query.exec("SELECT attackRange FROM sprite");
    query.seek(index-1);
    int attackRange = query.value(0).toInt();
    return attackRange;
}

const int Database::spriteMovementRange(int index) const
{
    QSqlQuery query;
    query.exec("SELECT movementRange FROM sprite");
    query.seek(index-1);
    int movementRange = query.value(0).toInt();
    return movementRange;
}

const int Database::spriteRate(int index) const
{
    QSqlQuery query;
    query.exec("SELECT rate FROM sprite");
    query.seek(index-1);
    int rate = query.value(0).toInt();
    return rate;
}

const int Database::spriteActionRate(int index) const
{
    QSqlQuery query;
    query.exec("SELECT actionRate FROM sprite");
    query.seek(index-1);
    int actionRate = query.value(0).toInt();
    return actionRate;
}

const float Database::spriteActionTime(int index) const
{
    QSqlQuery query;
    query.exec("SELECT actionTime FROM sprite");
    query.seek(index-1);
    float actionTime = query.value(0).toInt();
    return actionTime;
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
            sprite.attackPower=record.value("AP").toInt();
            sprite.hitPoints=record.value("HP").toInt();
            sprite.attackRange=record.value("range").toInt();
            sprite.name=record.value("name").toString();
            sprite.image.load(record.value("pixMap").toString());
            break;
        }
    }

    return sprite;
}

QString Database::userName(int index) const
{
    QSqlQuery query;
    query.exec("SELECT name FROM user");
    query.seek(index-1);
    QString name = query.value(0).toString();
    return name;
}


void Database::saveUnits(QString userName, QList<Unit> units)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();
    QString saveName;

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            saveName=record.value("id").toString();
            break;
        }
    }
    saveName.prepend("save");



    model.setTable(saveName);
    int row=0, line=0;
    model.select();
    model.removeRows(row, model.rowCount());
    model.submitAll();

    while(line<units.size())
    {
        model.insertRows(row,1);
        model.setData(model.index(row,0), line+1);
        model.setData(model.index(row,1), units[line].imageFileName);
        model.setData(model.index(row,2), units[line].faceLeft);
        model.setData(model.index(row,3), units[line].vLocation);
        model.setData(model.index(row,4), units[line].hLocation);
        model.setData(model.index(row,5), units[line].hitPoints);
        model.setData(model.index(row,6), units[line].totalHitPoints);
        model.setData(model.index(row,7), units[line].actionTime);
        model.setData(model.index(row,8), units[line].actionRate);
        model.setData(model.index(row,9), units[line].movementRange);
        model.setData(model.index(row,10), units[line].attackRange);
        model.setData(model.index(row,11), units[line].attackPower);
        model.setData(model.index(row,12), units[line].status);
        model.setData(model.index(row,13), units[line].maskFileName);
        model.setData(model.index(row,14), units[line].team);
        model.setData(model.index(row,15), units[line].unitWorth);
        model.submitAll();
        line++;

    }

}


QList<Unit> Database::loadUnits(QString userName)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();
    QString loadName;

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            loadName=record.value("id").toString();
            break;
        }
    }
    loadName.prepend("save");

    Unit units;
    QList<Unit> u;

    model.setTable(loadName);
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        units.imageFileName = record.value("imageFileName").toString();
        units.faceLeft = record.value("faceLeft").toInt();
        units.vLocation = record.value("vLocation").toInt();
        units.hLocation = record.value("hLocation").toInt();
        units.hitPoints = record.value("hitPoints").toInt();
        units.totalHitPoints = record.value("totalHitPoints").toInt();
        units.actionTime = record.value("actionTime").toFloat();
        units.actionRate = record.value("actionRate").toInt();
        units.movementRange = record.value("movementRange").toInt();
        units.attackPower = record.value("attackPower").toInt();
        units.attackRange =record.value("attackRange").toInt();
        units.status = record.value("status").toInt();
        units.maskFileName = record.value("maskFileName").toString();
        units.team = record.value("team").toInt();
        units.unitWorth = record.value("unitWorth").toInt();
        units.image.load(record.value("imageFileName").toString());
        units.mask_image.load(record.value("maskFileName").toString());

        u<<units;
    }
    return u;
}


User Database::loadUser(const QString &userName)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();
    User userData;

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            userData.name = record.value("name").toString();
            userData.experiencePoints = record.value("experiencePoints").toInt();
            userData.isActive = record.value("isActive").toBool();
            userData.level = record.value("level").toInt();
            break;
        }
    }
    return userData;
}


void Database::saveLevel(QString &userName, int level)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            record.setValue("level", level);
            model.setRecord(i, record);
            model.submitAll();
            break;
        }
    }
}


void Database::saveXP(QString &userName, int xp)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            record.setValue("experiencePoints", xp);
            model.setRecord(i, record);
            model.submitAll();
            break;
        }
    }
}


int Database::loadXP(QString &userName) const
{
    int exp;
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            exp = record.value("experiencePoints").toInt();
            break;
        }
    }
    return exp;
}


void Database::saveUser(QString &userName, User user)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            record.setValue("experiencePoints", user.experiencePoints);
            record.setValue("isActive", user.isActive);
            record.setValue("level", user.level);
            model.setRecord(i, record);
            model.submitAll();
            break;
        }
    }
}

void Database::activateUser(QString &userName)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            record.setValue("isActive", true);
            model.setRecord(i, record);
            model.submitAll();
            break;
        }
    }
}

void Database::deactivateUser(QString &userName)
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("name").toString()==userName)
        {
            record.setValue("isActive", false);
            model.setRecord(i, record);
            model.submitAll();
            break;
        }
    }
}

User Database::loadActiveUser()
{
    QSqlTableModel model;
    model.setTable("user");
    model.select();
    User userData;

    for (int i=0; i<model.rowCount(); ++i)
    {
        QSqlRecord record = model.record(i);
        if (record.value("isActive").toBool() == true)
        {
            userData.name = record.value("name").toString();
            userData.experiencePoints = record.value("experiencePoints").toInt();
            userData.isActive = record.value("isActive").toBool();
            userData.level = record.value("level").toInt();
            break;
        }
    }
    return userData;
}
