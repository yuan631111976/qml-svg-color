#include "svg.h"
#include <QPainter>


Svg::Svg()
{
    this->m_renderer = new QSvgRenderer();
    m_smooth = true;
    m_color = QColor(0,0,0);
    this->m_renderer->setFramesPerSecond(60);
    connect(m_renderer, SIGNAL(repaintNeeded()), this, SLOT(repaint()));
    connect(this, SIGNAL(widthChanged()), this, SLOT(onWidthChanged()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(onHeightChanged()));
}

Svg::~Svg()
{
    delete m_renderer;
}

QString Svg::source(){
    return m_path;
}

void Svg::setSource(const QString &path){
    this->m_path = path;
    render();
    emit sourceChanged();
}

QColor Svg::color(){
    return m_color;
}

void Svg::setColor(const QColor &color){
    m_color = color;
    render();
}

bool Svg::smooth(){
    return m_smooth;
}

void Svg::setSmooth(bool smooth){
    m_smooth = smooth;
    repaint();
}

void Svg::render(){
    if(m_path == "")
        return;
    QString path = m_path;
    if(path.mid(0,3) == "qrc"){
        path = path.mid(3,path.length() - 3);
    }
    QFile file(path);
    if(file.open(QFile::ReadOnly)){
        QByteArray svg = file.readAll();
        file.close();

        //对于简单的图标图形来说，增加svg的fill属性
        //如果对于复杂的图片，请使用paint里注释掉的内容（更换图片像素颜色）
        QByteArray content = "<svg fill=\"";
                    content.append(m_color.name(QColor::HexRgb).toLatin1());
                    content.append("\" ");
        svg = svg.replace("<svg ", content);

        this->m_renderer->load(svg);
        repaint();
    }
}

void Svg::onWidthChanged(){
    QSize svgSize = m_renderer->defaultSize();
    this->setHeight(width() * 1.0 / svgSize.width() * svgSize.height());
    repaint();
}

void Svg::onHeightChanged(){
    QSize svgSize = m_renderer->defaultSize();
    this->setWidth(height() * 1.0 / svgSize.height() * svgSize.width() );
    repaint();
}

void Svg::repaint()
{
    int width = this->width();
    int height = this->height();

    QSize svgSize = m_renderer->defaultSize();
    if(width <= 0 && height <= 0){
        this->setSize(svgSize);
    }
    this->update();
}

void Svg::setColor(QImage &img){
    int width = img.width();
    int height = img.height();
    int r = m_color.red();
    int g = m_color.green();
    int b = m_color.blue();

    unsigned char *data = img.bits();
    for(int i = 0;i < width;i++){
        for(int j = 0;j < height;j++){
//            int gray = qGray(*data,*data+1,*data+2);
//            float v = (255 - gray) * 1.0 / 255;
//            *data++ = b * v;
//            *data++ = g * v;
//            *data++ = r * v;
//            *data++;

            *data++ = b;
            *data++ = g;
            *data++ = r;
            *data++;
        }
    }
}

void Svg::paint(QPainter *painter){
    painter->setRenderHints(QPainter::Antialiasing, m_smooth);

    QSize defSize = m_renderer->defaultSize();
    QSizeF mySize = this->boundingRect().size();
    qreal widthRatio = mySize.width() / defSize.width();
    qreal heightRatio = mySize.height() / defSize.height();
    if(widthRatio > heightRatio) {
       mySize.rwidth() = defSize.width() * heightRatio;
    }
    else if(widthRatio < heightRatio) {
       mySize.rheight() = defSize.height() * widthRatio;
    }
    QPointF newTopLeft = this->boundingRect().topLeft();
    newTopLeft.rx() += (this->boundingRect().size().width() - mySize.width()) / 2;
    newTopLeft.ry() += (this->boundingRect().size().height() - mySize.height()) / 2;
    QRectF boundingBox(newTopLeft, mySize);
    this->setImplicitWidth(mySize.width());
    this->setImplicitHeight(mySize.height());

    //如果有复杂的图形，以上不能处理的，请使用这段逻辑进行处理
//    int w = (boundingBox.width() + boundingBox.x());
//    int h = (boundingBox.height() + boundingBox.y());
//    if(m_cache.width() != w || m_cache.height() != h){
//        m_cache = QImage(w,h,QImage::Format_ARGB32_Premultiplied);
//    }
//    m_cache.fill(Qt::transparent);
//    QPainter p(&m_cache);
//    p.setRenderHints(QPainter::Antialiasing, true);
//    m_renderer->render(&p,boundingBox);
//    p.end();
//    setColor(m_cache);
//    painter->drawImage(0,0,m_cache);

    m_renderer->render(painter,boundingBox);
}
