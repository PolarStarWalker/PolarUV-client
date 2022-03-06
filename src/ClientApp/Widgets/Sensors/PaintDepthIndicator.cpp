#include "SensorsWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void SensorsWidget::PaintDepthIndicator(QPainter &painter, int width, int height, float depth, int valueRange) {

    float lineWidth = 4.0f;
    float outlineWidth = 1.0f;
    float fontSize = 16.0f;
    float textOffsetY = 2.0f;
    float edgeOffset = 2.0f;

    float depthHeight = 640.0f;
    float offsetFromCenter = 378.0f;
    float depthBorderOffsetY2 = 20.0f;
    float depthBorderOffsetX2 = 20.0f;
    float horizontalLineLength = 60.0f;
    float depthRectWidth = 110.0f;
    float depthRectHeight = 40.0f;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    //QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing);
    painter.save();

    /// Counting indicator borders
    float indicatorLeftBorder = (float) width / 2 + offsetFromCenter;
    float indicatorTopBorder = ((float) height - depthHeight) / 2;

    /// Painting the marker
    float y;
    if (depth > (float) valueRange) y = depthHeight / 2 + 270;
    else if (depth < 0) y = (float) depthHeight / 2 - 270;
    else y = ((float) depthHeight / 2 - 270) + (540 * depth / (float) valueRange);
    QPainterPath markerPath;
    QVector<QPointF> markerPolygon = {
            QPointF(indicatorLeftBorder + 30,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10,
                    indicatorTopBorder + y - depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + y - depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + y - depthRectHeight / 2 + lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + edgeOffset,
                    indicatorTopBorder + y - depthRectHeight / 2 + lineWidth),
            QPointF(indicatorLeftBorder + 30 + lineWidth,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10 + edgeOffset,
                    indicatorTopBorder + y + depthRectHeight / 2 - lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + y + depthRectHeight / 2 - lineWidth),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + y),
            QPointF(indicatorLeftBorder + 30 + 10 + depthRectWidth + lineWidth,
                    indicatorTopBorder + y + depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30 + 10,
                    indicatorTopBorder + y + depthRectHeight / 2),
            QPointF(indicatorLeftBorder + 30,
                    indicatorTopBorder + y)
    };
    markerPath.addPolygon(QPolygonF(markerPolygon));
    markerPath.addText(indicatorLeftBorder + 30 + 10 - 1,
                       indicatorTopBorder + y + fontSize / 2 + textOffsetY,
                       font,
                       QString("%1м").arg(depth, 0, 'f', 2));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(markerPath);

    /// Painting the patch to marker frame
    QPainterPath patchPath;
    patchPath.addRect(indicatorLeftBorder + 30 + 10 + depthRectWidth + 1,
                      indicatorTopBorder + y - 1,
                      lineWidth - 2, lineWidth);
    painter.setPen(QPen(Qt::white, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(patchPath);

    /// Painting the scale and its values
    painter.translate(0, depthHeight / 2);
    int j = 0;
    QPainterPath scalePath;
    for (int i = -270; i <= 270; i += 108) {
        scalePath.addRect(indicatorLeftBorder,
                          indicatorTopBorder + (float) i - lineWidth / 2,
                          25, lineWidth);
        if (abs((depthHeight / 2 + (float) i) - y) >= 45) { // if the marker is far enough
            scalePath.addText(indicatorLeftBorder + 25 + 10,
                              indicatorTopBorder + (float) i + fontSize / 2,
                              font,
                              QString::number(j) + QString("м"));
        }
        j = j + (int) (valueRange / 5);
    }
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(scalePath);

    /// Painting the frame
    painter.restore();
    QPainterPath framePath;
    QVector<QPointF> framePolygon = {
            // Outer contour
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2,
                    indicatorTopBorder),
            QPointF(indicatorLeftBorder,
                    indicatorTopBorder + depthBorderOffsetY2),
            QPointF(indicatorLeftBorder,
                    indicatorTopBorder + depthHeight - depthBorderOffsetY2),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2,
                    indicatorTopBorder + depthHeight),
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + depthHeight),
            // Inner contour
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + depthHeight - lineWidth),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2 + edgeOffset,
                    indicatorTopBorder + depthHeight - lineWidth),
            QPointF(indicatorLeftBorder + lineWidth,
                    indicatorTopBorder + depthHeight - depthBorderOffsetY2 - edgeOffset),
            QPointF(indicatorLeftBorder + lineWidth,
                    indicatorTopBorder + depthBorderOffsetY2 + edgeOffset),
            QPointF(indicatorLeftBorder + depthBorderOffsetX2 + edgeOffset,
                    indicatorTopBorder + lineWidth),
            QPointF(indicatorLeftBorder + depthBorderOffsetY2 + horizontalLineLength,
                    indicatorTopBorder + lineWidth),
    };
    framePath.addPolygon(QPolygonF(framePolygon));
    framePath.closeSubpath();
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(framePath);
}