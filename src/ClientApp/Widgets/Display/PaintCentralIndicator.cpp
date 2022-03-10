#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintCentralIndicator(QPainter &painter, int width, int height, float rollAngle, float pitchAngle) {

    constexpr const float lineWidth = 4.0f;
    constexpr const float outlineWidth = 1.0f;
    constexpr const float fontSize = 16.0f;
    constexpr const float textOffsetY = 2.0f;
    constexpr const float edgeOffset = 2.0f;

    constexpr const float offsetFromCenter = 378.0f;
    constexpr const float centralHeight = 640.0f;
    constexpr const float horizonLineLength = 320.0f;
    constexpr const float divisionLineLength1 = 160.0f;
    constexpr const float divisionLineLength2 = 80.0f;
    constexpr const float circleRadius = 10.0f;
    constexpr const float centralBorderOffsetY2 = 20.0f;
    constexpr const float centralBorderOffsetX2 = 20.0f;
    constexpr const float horizontalLineLength = 60.0f;
    constexpr const float rectWidth = 110.0f;
    constexpr const float rectHeight = 40.0f;

    float y = pitchAngle;
    if (y < 0) y = 0;
    else if (y > 360) y = 360;
    else if ((0 <= y) && (y < 90)) y = y * 3;
    else if ((90 <= y) && (y < 270)) y = (y - 180) * 3;
    else if ((270 <= y) && (y <= 360)) y = (y - 360) * 3;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    painter.save();
    painter.translate((float) width / 2, (float) height / 2);
    painter.rotate(-rollAngle);

    /// Counting indicator borders
    float indicatorRightBorder = (float) width / 2 - offsetFromCenter;
    float indicatorTopBorder = ((float) height - centralHeight) / 2;

    /// Painting the horizon
    QPainterPath horizonPath;
    QVector<QPointF> leftHorizonPolygon{
            QPointF((float) -horizonLineLength / 2,
                    y - (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - (float) lineWidth,
                    y - (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - (float) lineWidth,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) -circleRadius - 5,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) -circleRadius - 5,
                    y + (float) lineWidth / 2),
            QPointF((float) -circleRadius - 5 - 5,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) -circleRadius - 5 - 5 - 1 - (float) lineWidth,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) -circleRadius - 5 - 1 - (float) lineWidth,
                    y + (float) lineWidth / 2),
            QPointF((float) -horizonLineLength / 2,
                    y + (float) lineWidth / 2),
            QPointF((float) -horizonLineLength / 2,
                    y - (float) lineWidth / 2),
    };
    horizonPath.addPolygon(QPolygonF(leftHorizonPolygon));
    QVector<QPointF> rightHorizonPolygon{
            QPointF((float) horizonLineLength / 2,
                    y - (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + (float) lineWidth,
                    y - (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + (float) lineWidth,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) circleRadius + 5,
                    y - (float) lineWidth / 2 - 10),
            QPointF((float) circleRadius + 5,
                    y + (float) lineWidth / 2),
            QPointF((float) circleRadius + 5 + 5,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) circleRadius + 5 + 5 + 1 + (float) lineWidth,
                    y + (float) lineWidth / 2 + 10),
            QPointF((float) circleRadius + 5 + 1 + (float) lineWidth,
                    y + (float) lineWidth / 2),
            QPointF((float) horizonLineLength / 2,
                    y + (float) lineWidth / 2),
            QPointF((float) horizonLineLength / 2,
                    y - (float) lineWidth / 2),
    };
    horizonPath.addPolygon(QPolygonF(rightHorizonPolygon));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(horizonPath);

    /// Painting upper divisions
    for (auto i = (int) y + 45; i <= 270; i += 45) {
        QPainterPath divisionPath;
        float length = (((((int32_t) y - i) / 45) % 2) == 0) ? divisionLineLength1 : divisionLineLength2;
        QVector<QPointF> leftDivisionPolygon{
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(leftDivisionPolygon));
        QVector<QPointF> rightDivisionPolygon{
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(rightDivisionPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(divisionPath);
    }

    /// Painting lower divisions
    for (auto i = (int32_t) y - 45; i >= -270; i -= 45) {
        QPainterPath divisionPath;
        float length = (((((int32_t) y - i) / 45) % 2) == 0) ? divisionLineLength1 : divisionLineLength2;
        QVector<QPointF> leftDivisionPolygon{
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) -circleRadius - 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) -length / 2,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(leftDivisionPolygon));
        QVector<QPointF> rightDivisionPolygon{
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i - (float) lineWidth / 2),
                QPointF((float) length / 2,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i + (float) lineWidth / 2),
                QPointF((float) circleRadius + 5,
                        (float) i - (float) lineWidth / 2),
        };
        divisionPath.addPolygon(QPolygonF(rightDivisionPolygon));
        painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
        painter.setBrush(Qt::white);
        painter.drawPath(divisionPath);
    }

    painter.restore();
    painter.save();

    painter.translate((float) width / 2, (float) height / 2);

    /// Painting the circle
    QPainterPath circlePath;
    circlePath.moveTo(circleRadius, 0);
    circlePath.arcTo(-circleRadius,
                     -circleRadius,
                     circleRadius * 2,
                     circleRadius * 2,
                     0, 360);
    circlePath.moveTo(circleRadius - lineWidth, 0);
    circlePath.arcTo((-circleRadius + lineWidth),
                     (-circleRadius + lineWidth),
                     (circleRadius - lineWidth) * 2,
                     (circleRadius - lineWidth) * 2,
                     0, 360);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(circlePath);

    /// Painting the arc
    QPainterPath arcPath;
    arcPath.moveTo(0, (float) centralHeight / 2 + 20);
    arcPath.arcTo((float) -centralHeight / 2 - 20,
                  (float) -centralHeight / 2 - 20,
                  centralHeight + 40,
                  centralHeight + 40,
                  270, rollAngle);
    //arcPath.moveTo(0, (float) _centralHeight / 2 + 20 + (float) _lineWidth);
    arcPath.arcTo((float) -centralHeight / 2 - 20 - (float) lineWidth,
                  (float) -centralHeight / 2 - 20 - (float) lineWidth,
                  (float) centralHeight + 40 + (float) lineWidth * 2,
                  (float) centralHeight + 40 + (float) lineWidth * 2,
                  270 + rollAngle, -rollAngle);
    //arcPath.closeSubpath();
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(arcPath);


    painter.restore();
    painter.save();

    painter.translate(0, (float) height / 2);

    /// Painting the marker
    QPainterPath markerPath;
    QVector<QPointF> markerPolygon = {
            QPointF((float) indicatorRightBorder - 30,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10,
                    (float) y - rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y - rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y - rectHeight / 2 + lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - edgeOffset,
                    (float) y - rectHeight / 2 + lineWidth),
            QPointF((float) indicatorRightBorder - 30 - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - edgeOffset,
                    (float) y + rectHeight / 2 - lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y + rectHeight / 2 - lineWidth),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y),
            QPointF((float) indicatorRightBorder - 30 - 10 - rectWidth - lineWidth,
                    (float) y + rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30 - 10,
                    (float) y + rectHeight / 2),
            QPointF((float) indicatorRightBorder - 30,
                    (float) y)
    };
    markerPath.addPolygon(QPolygonF(markerPolygon));
    // Calculating text offset
    float textOffsetX;
    if (-90 <= (int32_t) (y / 3) && (int32_t) (y / 3) < -9) textOffsetX = 70.0f;       // 4 символа (включая °)
    else if (0 <= (int32_t) (y / 3) && (int32_t) (y / 3) < 10) textOffsetX = 52.0f;    // 2 символа (включая °)
    else textOffsetX = 62.0f;                                                          // 3 символа (включая °)
    //
    markerPath.addText((float) indicatorRightBorder - 30 - 10 - textOffsetX,
                       (float) y + fontSize / 2 + textOffsetY,
                       font,
                       QString::number((int32_t) (y / 3)) + QString("°"));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(markerPath);

    /// Painting the patch to marker frame
    QPainterPath patchPath;
    patchPath.addRect((float) indicatorRightBorder - 30 - 10 - rectWidth - 3,
                      (float) y - 1,
                      lineWidth - 2,
                      lineWidth);
    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(patchPath);

    /// Painting the scale and its values
    QPainterPath scalePath;
    for (int32_t i = -270; i <= 270; i += 90) {
        scalePath.addRect((float) indicatorRightBorder - 25,
                          (float) i - lineWidth / 2,
                          25,
                          lineWidth);
        // Calculating text offset
        float textOffsetX2;
        if (-90 <= (i / 3) && (i / 3) < -9) textOffsetX2 = 57.0f;       // 4 символа (включая °)
        else if (0 <= (i / 3) && (i / 3) < 10) textOffsetX2 = 28.0f;    // 2 символа (включая °)
        else textOffsetX2 = 45.0f;                                      // 3 символа (включая °)
        //
        if (abs(i - (int32_t) y) >= 45) { // if the marker is far enough
            scalePath.addText((float) indicatorRightBorder - 25 - 10 - textOffsetX2,
                              (float) i + fontSize / 2,
                              font,
                              QString::number(i / 3) + QString("°"));
        }
    }
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(scalePath);

    painter.restore();

    /// Painting the frame
    QPainterPath framePath;
    QVector<QPointF> framePolygon = {
            // Outer contour
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    indicatorTopBorder),
            QPointF(indicatorRightBorder - centralBorderOffsetX2,
                    indicatorTopBorder),
            QPointF(indicatorRightBorder,
                    indicatorTopBorder + centralBorderOffsetY2),
            QPointF(indicatorRightBorder,
                    (float) height - indicatorTopBorder - centralBorderOffsetY2),
            QPointF(indicatorRightBorder - centralBorderOffsetX2,
                    (float) height - indicatorTopBorder),
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    (float) height - indicatorTopBorder),
            // Inner contour
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    (float) height - indicatorTopBorder - lineWidth),
            QPointF(indicatorRightBorder - centralBorderOffsetX2 - edgeOffset,
                    (float) height - indicatorTopBorder - lineWidth),
            QPointF(indicatorRightBorder - lineWidth,
                    (float) height - indicatorTopBorder - centralBorderOffsetY2 - edgeOffset),
            QPointF(indicatorRightBorder - lineWidth,
                    indicatorTopBorder + centralBorderOffsetY2 + edgeOffset),
            QPointF(indicatorRightBorder - centralBorderOffsetX2 - edgeOffset,
                    indicatorTopBorder + lineWidth),
            QPointF(indicatorRightBorder - centralBorderOffsetY2 - horizontalLineLength,
                    indicatorTopBorder + lineWidth),
    };
    framePath.addPolygon(QPolygonF(framePolygon));
    framePath.closeSubpath();
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(framePath);

    int32_t offsetX;
    if (rollAngle < -99) offsetX = 38;
    else if ((-99 <= rollAngle && rollAngle < -9) || (100 < rollAngle)) offsetX = 30;
    else if ((-9 <= rollAngle && rollAngle < 0) || (10 <= rollAngle && rollAngle < 100)) offsetX = 22;
    else offsetX = 14;

    /// Painting angle
    QPainterPath rollAnglePath;
    rollAnglePath.addText((float) width / 2 - (float) offsetX,
                          (float) height / 2 + (float) centralHeight / 2 + 70,
                          font,
                          QString::number((int32_t) rollAngle) + QString("°"));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAnglePath);

    /// Painting the roll angle frame
    QPainterPath rollAngleFramePath;
    QVector<QPointF> rollAngleFramePolygon = {
            // Inner contour
            // 5   1|6   2
            //
            // 4         3
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40),
            QPointF((float) (width + 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40),
            QPointF((float) (width + 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + 40),
            QPointF((float) (width - 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + 40),
            QPointF((float) (width - 90) / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40),
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40),
            // Outer contour
            // 2   1|6   5
            //
            // 3         4
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + (float) lineWidth),
            QPointF((float) (width - 90) / 2 + (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + (float) lineWidth),
            QPointF((float) (width - 90) / 2 + (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + 40 - (float) lineWidth),
            QPointF((float) (width + 90) / 2 - (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + 40 - (float) lineWidth),
            QPointF((float) (width + 90) / 2 - (float) lineWidth,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + (float) lineWidth),
            QPointF((float) width / 2,
                    (float) height / 2 + (float) centralHeight / 2 + 40 + (float) lineWidth),
    };
    rollAngleFramePath.addPolygon(rollAngleFramePolygon);
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAngleFramePath);

    /// Painting the patch to roll angle frame (hiding polygon outline)
    QPainterPath rollAnglePatchPath;
    rollAnglePatchPath.addRect(
            ((float) width - lineWidth) / 2,
            (float) height / 2 + (float) centralHeight / 2 + 40 + (float) outlineWidth,
            lineWidth,
            lineWidth - (outlineWidth * 2));

    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(rollAnglePatchPath);

}

