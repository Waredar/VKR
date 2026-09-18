#pragma once

#include "SpiralHeatExchanger.h"
#include <QString>

class CalcResultSerializer
{
public:
    static QString save(const CalculationResult& res, const QString& filePath);
    static CalculationResult load(const QString& filePath, QString& outError);
    static QString savePdf(const CalculationResult& res, const QString& filePath);

private:
    static QString buildHtmlReport(const CalculationResult& res);
};