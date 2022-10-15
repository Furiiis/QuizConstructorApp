#ifndef TAGSDELEGATE_H
#define TAGSDELEGATE_H

#include <qstyleditemdelegate.h>
#include <tag.h>
#include <qpainter.h>

class TagsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    TagsDelegate();
    TagsDelegate(const std::vector<Tag> tags);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // TAGSDELEGATE_H
