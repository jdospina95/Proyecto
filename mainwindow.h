#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QAbstractTableModel>
#include "actividad.h"
#include "clase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Calendario_clicked();

    void on_salir_clicked();

    void on_actividades_clicked();

    void on_clases_clicked();

    void on_actionNueva_Actividad_triggered();

    void on_actionNueva_Clase_triggered();

    void on_aceptar_clicked();

    void on_cancelar_clicked();

    void on_cAceptar_clicked();

    void on_cCancelar_clicked();

    void grabar();

    void cargar();

    void on_calendarWidget_selectionChanged();

    void grabarClases();

    void cargarClases();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
