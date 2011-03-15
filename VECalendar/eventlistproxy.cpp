#include <QSortFilterProxyModel>

#include "eventlistproxy.h"
#include "calendar.h"

EventListProxy::EventListProxy(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool EventListProxy::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const {
    return source_column == TITLE_INDEX ||
            source_column == START_TIME_INDEX ||
            source_column == END_TIME_INDEX ||
            source_column == DATE_INDEX;
}

