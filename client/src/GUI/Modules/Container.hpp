//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_CONTAINER_HPP
#define BABEL_CONTAINER_HPP


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QBoxLayout>

class Container : public QGroupBox
{
public:
    ~Container() = default;
    /**
     * Constructor for Container
     * @param layout
     * @param alignment1
     * @param alignment2
     */
    Container(QBoxLayout *layout = new QVBoxLayout, Qt::Alignment alignment1 = Qt::AlignVCenter, Qt::Alignment alignment2 = Qt::AlignHCenter);

    /**
     * add new Widget to _layout
     * @param widget
     * @param alignment
     * @return
     */
    QWidget *addWidget(QWidget *widget, Qt::Alignment alignment = Qt::AlignLeft);

    /**
     * add new Widget to _layout
     * @param item
     * @param alignment
     * @return
     */
    QLayoutItem *addItem(QLayoutItem *item, Qt::Alignment alignment = Qt::AlignLeft);

    /**
     * remove widget from list and _layout
     * @param widget
     */
    void removeWidget(QWidget *widget);

private:
    std::vector<QWidget *> _listWidget;
    std::vector<QLayoutItem *> _listItem;
protected:
    QBoxLayout *_layout;
};


#endif //BABEL_CONTAINER_HPP
