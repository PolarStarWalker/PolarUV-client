#include "DisplayWidget.hpp"

#include <QPainter>
#include <QPainterPath>


void DisplayWidget::PaintTextInfo(QPainter &painter,
                                  int width,
                                  int height,
                                  std::array<int8_t, 4> calibration) {

    constexpr const float fontSize = 16.0f;
    constexpr const float outlineWidth = 1.0f;

    QFont font("Times", (int) fontSize);
    font.setBold(true);

    /// Вывод информации о калибровке
    QPainterPath calibrationPath;
    calibrationPath.addText(10,
                            height - 10,
                            font,
                            QString("Калибровка [%1,%2,%3,%4]").
                                    arg(calibration[0]).
                                    arg(calibration[1]).
                                    arg(calibration[2]).
                                    arg(calibration[3]));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(calibrationPath);

    /// Вывод состояния стабилизации
    QPainterPath stabilizationPath;
    stabilizationPath.addText(width - 210,
                              height - 10,
                              font,
                              QString("Стабилизация"));
    painter.setPen(QPen(Qt::black, outlineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.drawPath(stabilizationPath);
}

