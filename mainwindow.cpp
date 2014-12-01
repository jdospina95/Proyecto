#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                               <<"Tipo"
                                               <<"Dia"
                                               <<"Mes"
                                               <<"Año"
                                               <<"Inicio"
                                               <<"Fin"
                                               <<"Descripcion");

    cargar();

    ui->tClases->setRowCount(14);
    ui->tClases->setColumnCount(6);
    ui->tClases->setHorizontalHeaderLabels(QStringList()
                                               <<"Lunes"
                                               <<"Martes"
                                               <<"Miercoles"
                                               <<"Jueves"
                                               <<"Viernes"
                                               <<"Sabado");
    ui->tClases->setVerticalHeaderLabels(QStringList()
                                               <<"7:00 AM"
                                               <<"8:00 AM"
                                               <<"9:00 AM"
                                               <<"10:00 AM"
                                               <<"11:00 AM"
                                               <<"12:00 M"
                                               <<"1:00 PM"
                                               <<"2:00 PM"
                                               <<"3:00 PM"
                                               <<"4:00 PM"
                                               <<"5:00 PM"
                                               <<"6:00 PM"
                                               <<"7:00 PM"
                                               <<"8:00 PM");
    cargarClases();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Calendario_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_salir_clicked()
{
}

void MainWindow::on_actividades_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_clases_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionNueva_Actividad_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionNueva_Clase_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_aceptar_clicked()
{
    QString tipoActividad = (ui->comboBox->itemText(ui->comboBox->currentIndex()));
    QString horaInicio = (ui->horaInicio->time().toString("h:mm ap"));
    QString horaFin = (ui->horaFin->time().toString("h:mm ap"));
    int dia = (ui->dia->value());
    int mes = (ui->mes->value());
    int ano = (ui->ano->value());
    QString descripcionActividad = (ui->plainTextEdit->toPlainText());

    Actividad actividad;

    actividad.setTipo(tipoActividad);
    const int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(currentRow + 1);
    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(tipoActividad));

    actividad.setInicio(horaInicio);
    QString shoraInicio = tr("%1").arg(horaInicio);
    ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(shoraInicio));

    actividad.setFin(horaFin);
    QString shoraFin = tr("%1").arg(horaFin);
    ui->tableWidget->setItem(currentRow, 5, new QTableWidgetItem(shoraFin));

    actividad.setDia(dia);
    QString sdia = tr("%1").arg(dia);
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(sdia));

    actividad.setMes(mes);
    QString smes = tr("%1").arg(mes);
    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(smes));

    actividad.setAno(ano);
    QString sano = tr("%1").arg(ano);
    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(sano));

    actividad.setDescripcion(descripcionActividad);
    ui->tableWidget->setItem(currentRow, 6, new QTableWidgetItem(descripcionActividad));


    //QCheckBox *checkbox = new QCheckBox;
    //ui->tableWidget->setCellWidget(currentRow, 7, checkbox);


    ui->stackedWidget->setCurrentIndex(1);

    grabar();

}

void MainWindow::on_cancelar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_cAceptar_clicked()
{
    QString salon = (ui->nSalon->toPlainText());
    QString nombre = (ui->nombreClase->toPlainText());
    QString profesor = (ui->nombreProfe->toPlainText());
    QString inicio = (ui->inicio->time().toString("h"));
    QString fin = (ui->fin->time().toString("h"));
    QVector<int> dias;

    if (ui->lunes->isChecked()==true){
        dias.append(1);
    }
    if (ui->martes->isChecked()==true){
        dias.append(2);
    }
    if (ui->miercoles->isChecked()==true){
        dias.append(3);
    }
    if (ui->jueves->isChecked()==true){
        dias.append(4);
    }
    if (ui->viernes->isChecked()==true){
        dias.append(5);
    }
    if (ui->sabado->isChecked()==true){
        dias.append(6);
    }

    Clase mClase;

    mClase.setSalon(salon);
    mClase.setNombre(nombre);
    mClase.setProfesor(profesor);
    mClase.setInicio(inicio);
    mClase.setFin(fin);
    mClase.setDias(dias);

    for (int j=inicio.toInt(); j< fin.toInt(); ++j)
    {
         for (int i=0; i< dias.length(); ++i)
         {
             ui->tClases->setItem((j-7), (dias[i]-1), new QTableWidgetItem(nombre));
         }
    }

    grabarClases();

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_cCancelar_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::grabar()
{
    QFile file("excel.csv");

        if (file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream data( &file );
            QStringList strList;
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {
                strList <<
                           ui->tableWidget->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString() + " ";
            }
            data << strList.join(";") << "\n";
            for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
            {
                strList.clear();
                for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
                {   QTableWidgetItem* item = ui->tableWidget->item(r,c);
                    if (!item || item->text().isEmpty())
                    {
                        ui->tableWidget->setItem(r,c,new QTableWidgetItem(""));
                    }
                    strList << ui->tableWidget->item( r, c )->text()+ " ";

                }
                data << strList.join( ";" )+"\n";
            }
            statusBar()->showMessage(tr("File saved successfully."), 3000);
            file.close();
        }
}

void MainWindow::cargar()
{
       QString fileName = "excel.csv";
       QString data;
       QFile importedCSV(fileName);
       QStringList rowOfData;
       QStringList rowData;
       data.clear();
       rowOfData.clear();
       rowData.clear();

       if (importedCSV.open(QFile::ReadOnly))
       {
           data = importedCSV.readAll();
           rowOfData = data.split("\n");
           importedCSV.close();
       }

       ui->tableWidget->setRowCount(rowOfData.size()-2);
       for (int x = 1; x < rowOfData.size(); x++)
       {
           rowData = rowOfData.at(x).split(";");
           for (int y = 0; y < rowData.size(); y++)
           {
               ui->tableWidget->setItem(x-1,y,new QTableWidgetItem(rowData[y]));
           }
       }
       ui->tableWidget->repaint();
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    QString dia = ui->calendarWidget->selectedDate().toString();
    qDebug()<<dia;
}

void MainWindow::grabarClases()
{
    QFile file("clases.csv");

        if (file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream data( &file );
            QStringList strList;
            for( int c = 0; c < ui->tClases->columnCount(); ++c )
            {
                strList <<
                           ui->tClases->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString() + " ";
            }
            data << strList.join(";") << "\n";
            for( int r = 0; r < ui->tClases->rowCount(); ++r )
            {
                strList.clear();
                for( int c = 0; c < ui->tClases->columnCount(); ++c )
                {   QTableWidgetItem* item = ui->tClases->item(r,c);
                    if (!item || item->text().isEmpty())
                    {
                        ui->tClases->setItem(r,c,new QTableWidgetItem(""));
                    }
                    strList << ui->tClases->item( r, c )->text()+ " ";

                }
                data << strList.join( ";" )+"\n";
            }
            statusBar()->showMessage(tr("File saved successfully."), 3000);
            file.close();
        }
}

void MainWindow::cargarClases()
{
    QString fileName = "clases.csv";
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    ui->tClases->setRowCount(rowOfData.size()-2);
    for (int x = 1; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        for (int y = 0; y < rowData.size(); y++)
        {
            ui->tClases->setItem(x-1,y,new QTableWidgetItem(rowData[y]));
        }
    }
    ui->tClases->repaint();
}
