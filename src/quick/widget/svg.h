#ifndef SVG_H
#define SVG_H

#include <QQuickPaintedItem>
#include <QSvgRenderer>
#include <QImage>

class Svg : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth)
public:
    Svg();
    ~Svg();

    QString source();
    void setSource(const QString &path);

    QColor color();
    void setColor(const QColor &color);

    bool smooth();
    void setSmooth(bool smooth);

protected:
    virtual void paint(QPainter *painter);

signals:
    void sourceChanged();

public slots:
    void repaint();

    void onWidthChanged();
    void onHeightChanged();
private :
    QColor m_color;
    QString m_path;
    QImage m_cache;
    bool m_smooth;
    QSvgRenderer *m_renderer;


private:
    void render();
    void setColor(QImage &);
};

#endif // SVG_H
