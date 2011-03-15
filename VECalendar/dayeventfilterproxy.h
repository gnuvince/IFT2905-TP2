#ifndef DAYEVENTFILTERPROXY_H
#define DAYEVENTFILTERPROXY_H

#include <QSortFilterProxyModel>
#include <QDate>

class DayEventFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit DayEventFilterProxy(QObject *parent = 0);
    QDate filterDate() const { return day; }
    int columnCount(const QModelIndex &parent) const;
    QString get_description(const QModelIndex index) const;


protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;

signals:

public slots:
    void setFilterDate(const QDate &date);


private:
    QDate day;

};

#endif // DAYEVENTFILTERPROXY_H
