#ifndef CSV_H
#define CSV_H

#include <QString>

#include "model.h"

class CSV
{
public:
    CSV(const QString &fileName);

    void read(Model *model) const;
    Model read() const;
    void write(const Model *model);

private:
    QString fileName;
};

#endif // CSV_H
