#include "qjsontablemodel.h"
#include <QJsonObject>
#include <QColor>
#include <QFont>


QJsonTableModel::QJsonTableModel( const QJsonTableModel::Header& header, QObject * parent )
    : QAbstractTableModel( parent )
    , m_header( header )
{

}

bool QJsonTableModel::setJson(const QJsonDocument &json)
{
    return setJson( json.array() );
}

bool QJsonTableModel::setJson( const QJsonArray& array )
{
    beginResetModel();
    m_json = array;
    endResetModel();
    return true;
}

QVariant QJsonTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    switch( orientation )
    {
    case Qt::Horizontal:
        return m_header[section]["title"];
    case Qt::Vertical:
        //return section + 1;
        return QVariant();
    default:
        return QVariant();
    }

}

int QJsonTableModel::rowCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return m_json.size();
}

int QJsonTableModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return m_header.size();
}


QJsonObject QJsonTableModel::getJsonObject( const QModelIndex &index ) const
{
    const QJsonValue& value = m_json[index.row() ];
    return value.toObject();
}

QVariant QJsonTableModel::data( const QModelIndex &index, int role ) const
{
    switch( role )
    {
    case Qt::DisplayRole:
    {
        QJsonObject obj = getJsonObject( index );
        const QString& key = m_header[index.column()]["index"];
        if( obj.contains( key ))
        {
            QJsonValue v = obj[ key ];

            if( v.isString() )
            {
                return v.toString();
            }
            else if( v.isDouble() )
            {
                return v.toDouble();
            }
            else
            {
                return QVariant();
            }
        }
        else
        {
            return QVariant();
        }
    }
    case Qt::BackgroundRole:
    {
        QJsonObject obj = getJsonObject( index );
        if(obj.contains("current_profit"))
        {
            if(obj["current_profit"].toDouble() <= 0)
                return QVariant(QColor(Qt::darkRed));
            else
                return QVariant(QColor(Qt::darkGreen));

        }
        else if(obj.contains("profit"))
        {
            if(obj["profit"].toDouble() <= 0)
                return QVariant(QColor(Qt::darkRed));
            else
                return QVariant(QColor(Qt::darkGreen));
        }
        else if(obj.contains("close_profit"))
        {
            if(obj["close_profit"].toDouble() <= 0)
                return QVariant(QColor(Qt::darkRed));
            else
                return QVariant(QColor(Qt::darkGreen));
        }
        return QVariant();
    }
    case Qt::FontRole:
    {
        QFont font;
        font.setBold(true);
        return font;
    }
    case Qt::ToolTipRole:
        return QVariant();
    default:
        return QVariant();
    }
}
