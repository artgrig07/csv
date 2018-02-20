#include "csv.h"


CSV::CSV(const QString &fileName) :
    fileName(fileName)
{}

void CSV::read(Model *model) const
{
    // TODO
}

Model CSV::read() const
{
    Model model;
    read(&model);
    return model;
}

void CSV::write(const Model *model)
{
    // TODO
}
