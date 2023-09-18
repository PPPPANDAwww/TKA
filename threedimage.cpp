#include "threedimage.h"
#include "ui_threedimage.h"

threedimage::threedimage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::threedimage)
{
    ui->setupUi(this);
    setWindowTitle("医学三维图像显示");

    QLabel* label = new QLabel(this);

    // 创建DICOM图像读取器
    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetFileName("/Users/panda/Desktop/qt_project/TKA/src1/dicom_data/404.dcm");
    reader->Update();

    // 获取图像数据并创建QT图像对象
    vtkImageData* imageData = reader->GetOutput();

    // 将DICOM图像数据转换为QT图像数据
    QImage image(reinterpret_cast<unsigned char*>(imageData->GetScalarPointer()), imageData->GetDimensions()[0], imageData->GetDimensions()[1], QImage::Format_Grayscale8);

    // 在标签上显示图像
    label->setPixmap(QPixmap::fromImage(image));

}

threedimage::~threedimage()
{
    delete ui;
}
