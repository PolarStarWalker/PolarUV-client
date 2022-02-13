#ifndef CLIENT_YAWINDICATOR_HPP
#define CLIENT_YAWINDICATOR_HPP

#include <QOpenGLWidget>
#include <QPainter>
#include <QPainterPath>


class YawIndicator : public QOpenGLWidget {
public:
    explicit YawIndicator(QWidget *parent) : QOpenGLWidget(parent) {

        this->_lineWidth = 4;
        this->_outlineWidth = 1;
        this->_fontSize = 16;
        this->_textOffsetY = 2;
        this->_centerLineHeight = 10;
        this->_borderOffsetX1 = 0;
        this->_borderOffsetX2 = 20;
        this->_borderOffsetY1 = 45;
        this->_borderOffsetY2 = 60;
        this->_edgeOffset = 2;
        this->_angleRectWidth = 80;
        this->_angleRectHeight = 30;
        this->_valueRectWidth = 60;
        this->_valueRectHeight = 30;
        this->_step = 15;
        this->_distance = 60;

        this->resize(640, 110);

        this->setAttribute(Qt::WA_AlwaysStackOnTop);
        this->setAttribute(Qt::WA_TranslucentBackground);
    }

    ~YawIndicator() override {

    }

protected:
    void initializeGL() override {
        float yawAngle = 0.0f;

        int32_t textOffsetX;
        if (yawAngle < 10) textOffsetX = 9;
        else if (yawAngle < 100) textOffsetX = 16;
        else textOffsetX = 27;

        QFont font("Times", _fontSize);
        font.setBold(true);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.save();

        /// Painting angle
        QPainterPath anglePath;
        anglePath.addText((float) this->width() / 2 - (float) textOffsetX,
                          (float) this->height() - _valueRectHeight - 5 + (float) (_valueRectHeight + _fontSize) / 2 +
                          _textOffsetY,
                          font,
                          QString::number((int32_t) yawAngle));
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(anglePath);

        /// Painting center value
        QPainterPath centerValuePath;
        int32_t valueOffset = ((int32_t) yawAngle) % _step;
        int32_t scaleOffset = (valueOffset * (_valueRectWidth + _distance)) / _step;
        painter.translate((float) this->width() / 2 - (float) scaleOffset, 0);
        int32_t centerValue = ((int32_t) yawAngle) - valueOffset;
        centerValuePath.addText(-textOffsetX,
                                (float) (this->height() - _borderOffsetY2 + _fontSize) / 2 + _textOffsetY,
                                font,
                                QString::number(centerValue));
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(centerValuePath);

        /// Painting left values
        int32_t currentX = (this->width() / 2) - scaleOffset;
        int8_t translationNumber = 1;
        while (currentX >= ((_valueRectWidth + _distance))) {
            painter.translate(-(_valueRectWidth + _distance), 0);
            // Checking value
            int32_t value = (((int32_t) yawAngle) - valueOffset) - (_step * translationNumber);
            if (value < 0) value = 360 + value;
            else if (value > 360) value = value - 360;
            // Calculating text offset
            int32_t valueOffsetX;
            if (value < 10) valueOffsetX = 9;
            else if (value < 100) valueOffsetX = 16;
            else valueOffsetX = 27;
            // Creating path
            QPainterPath valuePath;
            valuePath.addText(-valueOffsetX,
                              (float) (this->height() - _borderOffsetY2 + _fontSize) / 2 + _textOffsetY,
                              font,
                              QString::number(value));
            // Painting
            painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.setBrush(Qt::white);
            painter.drawPath(valuePath);
            //
            translationNumber++;
            currentX -= _valueRectWidth;
        }

        /// Translating back to the center
        for (size_t i = 0; i < translationNumber - 1; i++) {
            painter.translate(_valueRectWidth + _distance, 0);
            currentX += _valueRectWidth;
        }
        translationNumber = 1;

        /// Painting right values
        while (currentX <= (this->width() - ((_valueRectWidth + _distance)))) {
            painter.translate(_valueRectWidth + _distance, 0);
            // Checking value
            int32_t value = (((int32_t) yawAngle) - valueOffset) + (_step * translationNumber);
            if (value < 0) value = 360 - value;
            else if (value == 360) value = 0;
            else if (value > 360) value = value - 360;
            // Calculating text offset
            int32_t valueOffsetX;
            if (value < 10) valueOffsetX = 9;
            else if (value < 100) valueOffsetX = 16;
            else valueOffsetX = 27;
            // Creating path
            QPainterPath valuePath;
            valuePath.addText(-valueOffsetX,
                              (float) (this->height() - _borderOffsetY2 + _fontSize) / 2 + _textOffsetY,
                              font,
                              QString::number(value));
            // Painting
            painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.setBrush(Qt::white);
            painter.drawPath(valuePath);
            //
            translationNumber++;
            currentX += _valueRectWidth;
        }

        /// Translating back to X = 0
        painter.restore();

        /// Painting the main frame
        QPainterPath framesPath;
        QVector<QPointF> framePolygon = {
                // Outer contour
                QPointF(_borderOffsetX1,
                        0),
                QPointF(_borderOffsetX1,
                        this->height() - _borderOffsetY2),
                QPointF(_borderOffsetX2,
                        this->height() - _borderOffsetY1),
                QPointF(this->width() - _borderOffsetX2,
                        this->height() - _borderOffsetY1),
                QPointF(this->width() - _borderOffsetX1,
                        this->height() - _borderOffsetY2),
                QPointF(this->width() - _borderOffsetX1,
                        0),
                // Inner contour
                QPointF(this->width() - _borderOffsetX1 - _lineWidth,
                        0),
                QPointF(this->width() - _borderOffsetX1 - _lineWidth,
                        this->height() - _borderOffsetY2 - _edgeOffset),
                QPointF(this->width() - _borderOffsetX2 - _edgeOffset,
                        this->height() - _borderOffsetY1 - _lineWidth),
                QPointF((float) (this->width() + _lineWidth) / 2,
                        this->height() - _borderOffsetY1 - _lineWidth),
                QPointF((float) (this->width() + _lineWidth) / 2,
                        this->height() - _borderOffsetY1 - _lineWidth - _centerLineHeight),
                QPointF((float) (this->width() - _lineWidth) / 2,
                        this->height() - _borderOffsetY1 - _lineWidth - _centerLineHeight),
                QPointF((float) (this->width() - _lineWidth) / 2,
                        this->height() - _borderOffsetY1 - _lineWidth),
                QPointF(_borderOffsetX2 + _edgeOffset,
                        this->height() - _borderOffsetY1 - _lineWidth),
                QPointF(_borderOffsetX1 + _lineWidth,
                        this->height() - _borderOffsetY2 - _edgeOffset),
                QPointF(_borderOffsetX1 + _lineWidth, 0),
        };
        framesPath.addPolygon(QPolygonF(framePolygon));

        /// Painting the angle frame
        QVector<QPointF> angleFramePolygon = {
                // Inner contour
                // 5   1|6   2
                //
                // 4         3
                QPointF((float) this->width() / 2,
                        this->height() - _angleRectHeight - 5),
                QPointF((float) (this->width() + _angleRectWidth) / 2,
                        this->height() - _angleRectHeight - 5),
                QPointF((float) (this->width() + _angleRectWidth) / 2,
                        this->height() - 5),
                QPointF((float) (this->width() - _angleRectWidth) / 2,
                        this->height() - 5),
                QPointF((float) (this->width() - _angleRectWidth) / 2,
                        this->height() - _angleRectHeight - 5),
                QPointF((float) this->width() / 2,
                        this->height() - _angleRectHeight - 5),
                // Outer contour
                // 2   1|6   5
                //
                // 3         4
                QPointF((float) this->width() / 2,
                        this->height() - _angleRectHeight - 5 - _lineWidth),
                QPointF((float) (this->width() - _angleRectWidth) / 2 - _lineWidth,
                        this->height() - _angleRectHeight - 5 - _lineWidth),
                QPointF((float) (this->width() - _angleRectWidth) / 2 - _lineWidth,
                        this->height() - 5 + _lineWidth),
                QPointF((float) (this->width() + _angleRectWidth) / 2 + _lineWidth,
                        this->height() - 5 + _lineWidth),
                QPointF((float) (this->width() + _angleRectWidth) / 2 + _lineWidth,
                        this->height() - _angleRectHeight - 5 - _lineWidth),
                QPointF((float) this->width() / 2,
                        this->height() - _angleRectHeight - 5 - _lineWidth),
        };
        framesPath.addPolygon(angleFramePolygon);
        painter.setPen(QPen(Qt::black, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(framesPath);

        /// Painting the patch to angle frame (hiding polygon outline)
        QPainterPath patchPath;
        patchPath.addRect((float) (this->width() - _lineWidth) / 2,
                          this->height() - _angleRectHeight - 5 - _lineWidth + _outlineWidth,
                          _lineWidth,
                          _lineWidth - (_outlineWidth * 2));

        painter.setPen(QPen(Qt::white, _outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(patchPath);
    }

    void paintGL() override {}

    void resizeGL(int w, int h) override {

    }

private:
    int32_t _lineWidth;
    int32_t _outlineWidth;
    int32_t _fontSize;
    int32_t _textOffsetY;
    int32_t _centerLineHeight;
    int32_t _borderOffsetX1;
    int32_t _borderOffsetX2;
    int32_t _borderOffsetY1;
    int32_t _borderOffsetY2;
    int32_t _edgeOffset;
    int32_t _angleRectWidth;
    int32_t _angleRectHeight;
    int32_t _valueRectWidth;
    int32_t _valueRectHeight;
    int32_t _step;
    int32_t _distance;
};

#endif //CLIENT_YAWINDICATOR_HPP
