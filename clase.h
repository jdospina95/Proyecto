#ifndef CLASE_H
#define CLASE_H

#include "mainwindow.h"

class Clase
{   

public:
    Clase(){}
    ~Clase(){}

    QString getSalon(){return m_salon;}
    void setSalon(QString salon){m_salon=salon;}

    QString getNombre(){return m_nombre;}
    void setNombre(QString nombre){m_nombre=nombre;}

    QString getProfesor(){return m_profesor;}
    void setProfesor(QString profesor){m_profesor=profesor;}

    QString getInicio(){return m_inicio;}
    void setInicio(QString inicio){m_inicio=inicio;}

    QString getFin(){return m_fin;}
    void setFin(QString fin){m_fin=fin;}

    QVector<int> getDias(){return m_dias;}
    void setDias(QVector<int> dias){m_dias=dias;}

private:
    QString m_salon;
    QString m_nombre;
    QString m_profesor;
    QString m_inicio;
    QString m_fin;
    QVector<int> m_dias;
};

#endif // CLASE_H
