#ifndef CLIENT_DEPTHINDICATOR_HPP
#define CLIENT_DEPTHINDICATOR_HPP

#include <QOpenGLWidget>
#include <QPainter>
#include <QPainterPath>


class DepthIndicator : public QOpenGLWidget {
public:
    explicit DepthIndicator(QWidget *parent) : QOpenGLWidget(parent) {

        this->_valueRange = 10;

        this->_lineWidth = 4;
        this->_outlineWidth = 1;
        this->_fontSize = 16;
        this->_textOffsetY = 2;
        this->_borderOffsetY1 = 5;
        this->_borderOffsetY2 = 20;
        this->_borderOffsetX1 = 5;
        this->_borderOffsetX2 = 20;
        this->_edgeOffset = 2;
        this->_horizontalLineLength = 60;
        this->_depthRectWidth = 80;
        this->_depthRectHeight = 40;

        this->resize(130, 640);

        this->setAttribute(Qt::WA_AlwaysStackOnTop);
        this->setAttribute(Qt::WA_TranslucentBackground);
    }

    ~DepthIndicator() override = default;

protected:
    void initializeGL() override { }

    void paintGL() override {
        float depth = 0.0f;

        // this->valueRange = ...

        QFont font("Times", (int32_t) _fontSize);
        font.setBold(true);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.save();

        /// Painting the marker
        float y;
        if (depth > _valueRange) y = (float) this->height() / 2 + 270;
        else if (depth < 0) y = (float) this->height() / 2 - 270;
        else y = ((float) this->height() / 2 - 270) + (540 * depth / _valueRange);
        QPainterPath markerPath;
        QVector<QPointF> markerPolygon = {
                QPointF(_borderOffsetX1 + 30,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10,
                        y - _depthRectHeight / 2),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth + _lineWidth,
                        y - _depthRectHeight / 2),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth + _lineWidth,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth,
                        y - _depthRectHeight / 2 + _lineWidth),
                QPointF(_borderOffsetX1 + 30 + 10 + _edgeOffset,
                        y - _depthRectHeight / 2 + _lineWidth),
                QPointF(_borderOffsetX1 + 30 + _lineWidth,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10 + _edgeOffset,
                        y + _depthRectHeight / 2 - _lineWidth),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth,
                        y + _depthRectHeight / 2 - _lineWidth),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth + _lineWidth,
                        y),
                QPointF(_borderOffsetX1 + 30 + 10 + _depthRectWidth + _lineWidth,
                        y + _depthRectHeight / 2),
                QPointF(_borderOffsetX1 + 30 + 10,
                        y + _depthRectHeight / 2),
                QPointF(_borderOffsetX1 + 30,
                        y)
        };
        markerPath.addPolygon(QPolygonF(markerPolygon));
        markerPath.addText(_borderOffsetX1 + 30 + 10 - 1,
                           y + _fontSize / 2 + _textOffsetY,
                           font,
                           QString("%1м").arg(depth, 0, 'f', 2));
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(markerPath);

        /// Painting the patch to marker frame
        QPainterPath patchPath;
        patchPath.addRect(_borderOffsetX1 + 30 + 10 + _depthRectWidth + 1,
                           y - 1,
                           _lineWidth - 2,
                           _lineWidth);
        painter.setPen(QPen(Qt::white, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(patchPath);

        /// Painting the scale and its values
        painter.translate(0, (float) this->height() / 2);
        int32_t j = 0;
        QPainterPath scalePath;
        for (int32_t i = -270; i <= 270; i += 108) {
            scalePath.addRect(_borderOffsetX1,
                              (float) i - _lineWidth / 2,
                              25,
                              _lineWidth);
            if (abs((this->height() / 2 + i) - (int32_t) y) >= 45) { // if the marker is far enough
                scalePath.addText(_borderOffsetX1 + 25 + 10,
                                  (float) i + _fontSize / 2,
                                  font,
                                  QString::number(j) + QString("м"));
            }
            j = j + (int32_t) (_valueRange / 5);
        }
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(scalePath);

        /// Painting the frame
        painter.restore();
        QPainterPath framePath;
        QVector<QPointF> framePolygon = {
                // Outer contour
                QPointF(_borderOffsetY2 + _horizontalLineLength,
                        _borderOffsetY1),
                QPointF(_borderOffsetX2,
                        _borderOffsetY1),
                QPointF(_borderOffsetX1,
                        _borderOffsetY2),
                QPointF(_borderOffsetX1,
                        (float) this->height() - _borderOffsetY2),
                QPointF(_borderOffsetX2,
                        (float) this->height() - _borderOffsetY1),
                QPointF(_borderOffsetY2 + _horizontalLineLength,
                        (float) this->height() - _borderOffsetY1),
                // Inner contour
                QPointF(_borderOffsetY2 + _horizontalLineLength,
                        (float) this->height() - _borderOffsetY1 - _lineWidth),
                QPointF(_borderOffsetX2 + _edgeOffset,
                        (float) this->height() - _borderOffsetY1 - _lineWidth),
                QPointF(_borderOffsetX1 + _lineWidth,
                        (float) this->height() - _borderOffsetY2 - _edgeOffset),
                QPointF(_borderOffsetX1 + _lineWidth,
                        _borderOffsetY2 + _edgeOffset),
                QPointF(_borderOffsetX2 + _edgeOffset,
                        _borderOffsetY1 + _lineWidth),
                QPointF(_borderOffsetY2 + _horizontalLineLength,
                        _borderOffsetY1 + _lineWidth),
        };
        framePath.addPolygon(QPolygonF(framePolygon));
        framePath.closeSubpath();
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(framePath);
    }

    void resizeGL(int w, int h) override {

    }

private:
    float _valueRange;

    float _lineWidth;
    float _outlineWidth;
    float _fontSize;
    float _textOffsetY;
    float _borderOffsetY1;
    float _borderOffsetY2;
    float _borderOffsetX1;
    float _borderOffsetX2;
    float _edgeOffset;
    float _horizontalLineLength;
    float _depthRectWidth;
    float _depthRectHeight;
};

#endif
