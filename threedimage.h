#ifndef THREEDIMAGE_H
#define THREEDIMAGE_H

#include <QDialog>

#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <QLabel>
#include <QImage>

namespace Ui {
class threedimage;
}

class threedimage : public QDialog
{
    Q_OBJECT

public:
    explicit threedimage(QWidget *parent = nullptr);
    ~threedimage();

private:
    Ui::threedimage *ui;
};

#endif // THREEDIMAGE_H
