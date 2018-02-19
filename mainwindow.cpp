#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализируем tableView
    viewModel = new TableModel();
    ui->tableView->setModel(viewModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // Нажатие "Открыть БД"
    connect(ui->buttonOpen, &QPushButton::released,
            this, &MainWindow::handleButtonOpenClick);

    // Выбор таблицы в "Просмотр"
    connect(ui->selectView, &QComboBox::currentTextChanged,
            this, &MainWindow::handleSelectViewSelect);

    // Нажатие "Сохранить" в "Экспорт"
    connect(ui->buttonExport, &QPushButton::released,
            this, &MainWindow::handleButtonExportClick);

    // Нажатие "Открыть" в "Импорт"
    connect(ui->buttonImport, &QPushButton::released,
            this, &MainWindow::handleButtonImportClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Нажатие "Открыть БД"
void MainWindow::handleButtonOpenClick()
{
    // Открываем диалог выбора БД
    const QString &fileName = QFileDialog::getOpenFileName(this, tr("Открыть БД"), QDir::homePath());
    if (fileName.isEmpty()) return;

    // Открываем БД
    // TODO

    // Читаем список таблиц
    // TODO
    const QStringList &tableNames = QStringList("__test__");

    // Добавляем таблицы в selectView и selectExport
    ui->selectView->addItems(tableNames);
    ui->selectExport->addItems(tableNames);

    // Открываем "Просмотр"
    ui->rootWidget->setCurrentWidget(ui->widgetWork);
}

// Выбор таблицы в "Просмотр"
void MainWindow::handleSelectViewSelect(const QString &tableName)
{
    // Очищаем tableView
    viewModel->clear();

    // Проверяем что таблица выбрана
    if (!tableName.isEmpty()) return;

    // Читаем таблицу из БД
    // TODO
}

// Нажатие "Сохранить" в "Экспорт"
void MainWindow::handleButtonExportClick()
{
    // Получаем tableName из selectExport
    const QString &tableName = ui->selectExport->currentText();
    if (tableName.isEmpty()) return;

    // Открываем диалог сохранения CSV
    const QString &fileName = QFileDialog::getSaveFileName(this, tr("Сохранить CSV"), QDir::home().absoluteFilePath(tableName + ".csv"));
    if (fileName.isEmpty()) return;

    // Читаем таблицу из БД
    // TODO

    // Сохраняем CSV
    // TODO
}

// Нажатие "Открыть" в "Импорт"
void MainWindow::handleButtonImportClick()
{
    // Получаем tableName из inputImport
    const QString &tableName = ui->inputImport->text();
    if (tableName.isEmpty()) return;

    // Открываем диалог выбора CSV
    const QString &fileName = QFileDialog::getOpenFileName(this, tr("Открыть CSV"), QDir::homePath());
    if (fileName.isEmpty()) return;

    // Читаем CSV
    // TODO

    // Сохраняем таблицу в БД
    // TODO

    // Добавляем таблицу в selectView и selectExport
    ui->selectView->addItem(tableName);
    ui->selectExport->addItem(tableName);
}
