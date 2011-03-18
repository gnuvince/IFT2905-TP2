#include <QSortFilterProxyModel>

#include "eventlistproxy.h"
#include "calendar.h"

EventListProxy::EventListProxy(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool EventListProxy::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const {
    Q_UNUSED(source_parent);
    return source_column == TITLE_INDEX ||
            source_column == START_TIME_INDEX ||
            source_column == END_TIME_INDEX ||
            source_column == DATE_INDEX;
}


QString EventListProxy::get_description(const QModelIndex index) const {
    return (static_cast<Calendar*>(sourceModel()))->get_description(mapToSource(index));
}
