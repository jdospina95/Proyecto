#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include "mainwindow.h"

class Actividad
{

public:
    Actividad(){}
    ~Actividad(){}

    int getDia(){return m_dia;}
    void setDia(int dia){m_dia=dia;}

    int getMes(){return m_mes;}
    void setMes(int mes){m_mes=mes;}

    int getAno(){return m_ano;}
    void setAno(int ano){m_ano=ano;}


    QString getDescripcion(){return m_descripcion;}
    void setDescripcion(QString descripcion){m_descripcion=descripcion;}


    QString getInicio(){return m_inicio;}
    void setInicio(QString inicio){m_inicio=inicio;}


    QString getFin(){return m_fin;}
    void setFin(QString fin){m_fin=fin;}

    QString getTipo(){return m_tipo;}
    void setTipo(QString tipo){m_tipo=tipo;}

private:
    int m_dia;
    int m_mes;
    int m_ano;
    QString m_descripcion;
    QString m_inicio;
    QString m_fin;
    QString m_tipo;
};

#endif // ACTIVIDAD_H
