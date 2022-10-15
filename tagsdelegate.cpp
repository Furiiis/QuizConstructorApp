#include "tagsdelegate.h"

TagsDelegate::TagsDelegate()
{

}

TagsDelegate::TagsDelegate(const std::vector<Tag> tags) //DEPRICATED
{

}

void TagsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(QRectF(10, 10, 100, 50), 10, 10);
    QPen pen(Qt::black, 10);
    painter->setPen(pen);
    painter->fillPath(path, Qt::red);
    painter->drawPath(path);
}
