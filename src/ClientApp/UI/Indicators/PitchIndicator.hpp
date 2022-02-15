#ifndef CLIENT_PITCHINDICATOR_HPP
#define CLIENT_PITCHINDICATOR_HPP

#include <QOpenGLWidget>
#include <QPainter>
#include <QPainterPath>

class PitchIndicator final : public QOpenGLWidget {
public:
    explicit PitchIndicator(QWidget *parent) : QOpenGLWidget(parent) {

        _lineWidth = 4;
        _outlineWidth = 1;
        _fontSize = 16;
        _textOffsetY = 2;
        _borderOffsetY1 = 5;
        _borderOffsetY2 = 20;
        _borderOffsetX1 = 5;
        _borderOffsetX2 = 20;
        _edgeOffset = 2;
        _horizontalLineLength = 60;
        _depthRectWidth = 80;
        _depthRectHeight = 40;

        resize(130, 640);

        setAttribute(Qt::WA_AlwaysStackOnTop);
        setAttribute(Qt::WA_TranslucentBackground);
    }

    ~PitchIndicator() final = default;

protected:
    void initializeGL() final {  }

    void paintGL() final {
        float pitchAngle = 0.0f;

        QFont font("Times", (int32_t) _fontSize);
        font.setBold(true);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.save();

        auto y = (int32_t) pitchAngle;
        if (y < 0) y = 0;
        else if ((0 <= y) && (y < 90)) y = y * 3;             // Смотрит вперед, верхняя полусфера
        else if ((90 <= y) && (y < 270)) y = (y - 180) * 3;   // Смотрит назад
        else if ((270 <= y) && (y <= 360)) y = (y - 360) * 3; // Смотрит вперед, нижняя полусфера
        else if (y > 360) y = 360;

        /// Painting the marker
        painter.translate(0, (float) this->height() / 2);
        QPainterPath markerPath;
        QVector<QPointF> markerPolygon = {
                QPointF((float) this->width() - _borderOffsetX1 - 30,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10,
                        (float) y - _depthRectHeight / 2),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth - _lineWidth,
                        (float) y - _depthRectHeight / 2),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth - _lineWidth,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth,
                        (float) y - _depthRectHeight / 2 + _lineWidth),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _edgeOffset,
                        (float) y - _depthRectHeight / 2 + _lineWidth),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - _lineWidth,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _edgeOffset,
                        (float) y + _depthRectHeight / 2 - _lineWidth),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth,
                        (float) y + _depthRectHeight / 2 - _lineWidth),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth - _lineWidth,
                        (float) y),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth - _lineWidth,
                        (float) y + _depthRectHeight / 2),
                QPointF((float) this->width() - _borderOffsetX1 - 30 - 10,
                        (float) y + _depthRectHeight / 2),
                QPointF((float) this->width() - _borderOffsetX1 - 30,
                        (float) y)
        };
        markerPath.addPolygon(QPolygonF(markerPolygon));
        // Calculating text offset
        float textOffsetX;
        if (-90 <= (int32_t) (y / 3) && (int32_t) (y / 3) < -9) textOffsetX = 70.0f;       // 4 символа (включая °)
        else if (0 <= (int32_t) (y / 3) && (int32_t) (y / 3) < 10) textOffsetX = 52.0f;    // 2 символа (включая °)
        else textOffsetX = 62.0f;                                                          // 3 символа (включая °)
        //
        markerPath.addText((float) this->width() - _borderOffsetX1 - 30 - 10 - textOffsetX,
                           (float) y + _fontSize / 2 + _textOffsetY,
                           font,
                           QString::number((int32_t) (y / 3)) + QString("°"));
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(markerPath);

        /// Painting the patch to marker frame
        QPainterPath patchPath;
        patchPath.addRect((float) this->width() - _borderOffsetX1 - 30 - 10 - _depthRectWidth - 3,
                          y - 1,
                          _lineWidth - 2,
                          _lineWidth);
        painter.setPen(QPen(Qt::white, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(patchPath);

        /// Painting the scale and its values
        QPainterPath scalePath;
        for (int32_t i = -270; i <= 270; i += 90) {
            scalePath.addRect((float) this->width() - _borderOffsetX1 - 25,
                              (float) i - _lineWidth / 2,
                              25,
                              _lineWidth);
            // Calculating text offset
            float textOffsetX;
            if (-90 <= (i / 3) && (i / 3) < -9) textOffsetX = 57.0f;       // 4 символа (включая °)
            else if (0 <= (i / 3) && (i / 3) < 10) textOffsetX = 28.0f;    // 2 символа (включая °)
            else textOffsetX = 45.0f;                                  // 3 символа (включая °)
            //
            if (abs(i - (int32_t) y) >= 45) { // if the marker is far enough
                scalePath.addText((float) this->width() - _borderOffsetX1 - 25 - 10 - textOffsetX,
                                  (float) i + _fontSize / 2,
                                  font,
                                  QString::number(i / 3) + QString("°"));
            }
        }
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(scalePath);

        /// Painting the frame
        painter.restore();
        QPainterPath framePath;
        QVector<QPointF> framePolygon = {
                // Outer contour
                QPointF((float) this->width() - _borderOffsetY2 - _horizontalLineLength,
                        _borderOffsetY1),
                QPointF((float) this->width() - _borderOffsetX2,
                        _borderOffsetY1),
                QPointF((float) this->width() - _borderOffsetX1,
                        _borderOffsetY2),
                QPointF((float) this->width() - _borderOffsetX1,
                        (float) this->height() - _borderOffsetY2),
                QPointF((float) this->width() - _borderOffsetX2,
                        (float) this->height() - _borderOffsetY1),
                QPointF((float) this->width() - _borderOffsetY2 - _horizontalLineLength,
                        (float) this->height() - _borderOffsetY1),
                // Inner contour
                QPointF((float) this->width() - _borderOffsetY2 - _horizontalLineLength,
                        (float) this->height() - _borderOffsetY1 - _lineWidth),
                QPointF((float) this->width() - _borderOffsetX2 - _edgeOffset,
                        (float) this->height() - _borderOffsetY1 - _lineWidth),
                QPointF((float) this->width() - _borderOffsetX1 - _lineWidth,
                        (float) this->height() - _borderOffsetY2 - _edgeOffset),
                QPointF((float) this->width() - _borderOffsetX1 - _lineWidth,
                        _borderOffsetY2 + _edgeOffset),
                QPointF((float) this->width() - _borderOffsetX2 - _edgeOffset,
                        _borderOffsetY1 + _lineWidth),
                QPointF((float) this->width() - _borderOffsetY2 - _horizontalLineLength,
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

#endif //CLIENT_PITCHINDICATOR_HPP
