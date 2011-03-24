#ifndef EVENTLISTPROXY_H
#define EVENTLISTPROXY_H

#include <QSortFilterProxyModel>

class EventListProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit EventListProxy(QObject *parent = 0);
    QString getDescription(const QModelIndex index) const;

protected:
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;

signals:

public slots:

};

#endif // EVENTLISTPROXY_H
