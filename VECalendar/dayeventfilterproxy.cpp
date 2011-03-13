#include "dayeventfilterproxy.h"
#include "calendar.h"
#include "calendarevent.h"
#include <QModelIndex>

DayEventFilterProxy::DayEventFilterProxy(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void DayEventFilterProxy::setFilterDate(const QDate &date) {
    day = date;
    invalidateFilter();
}


bool DayEventFilterProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    QModelIndex index = sourceModel()->index(source_row, DATE_INDEX, source_parent);
    return sourceModel()->data(index).toDate() == day;
}

int DayEventFilterProxy::columnCount(const QModelIndex &parent) const {
    return 3;
}

bool DayEventFilterProxy::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const {
    return source_column == TITLE_INDEX ||
           source_column == START_TIME_INDEX ||
           source_column == END_TIME_INDEX;
}


