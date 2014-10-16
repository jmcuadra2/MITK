/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkFiberBundleXWriter.h"
#include <vtkSmartPointer.h>
#include <vtkCleanPolyData.h>
#include <itksys/SystemTools.hxx>
#include <mitkTrackvis.h>
#include <itkSize.h>

#include <mitkAbstractFileWriter.h>
#include <mitkCustomMimeType.h>

mitk::FiberBundleXWriter::FiberBundleXWriter()
  : mitk::AbstractFileWriter(mitk::FiberBundleX::GetStaticNameOfClass())
{
  std::string category = "Fiber Bundle File";
  mitk::CustomMimeType customMimeType;
  customMimeType.SetCategory(category);
  customMimeType.AddExtension("fib");
  customMimeType.AddExtension("afib");
  customMimeType.AddExtension("vtk");
  customMimeType.AddExtension("avtk");
  customMimeType.AddExtension("trk");

  this->SetDescription(category);
  this->SetMimeType(customMimeType);

  RegisterService();
}

mitk::FiberBundleXWriter::FiberBundleXWriter(const mitk::FiberBundleXWriter & other)
  :mitk::AbstractFileWriter(other)
{}

mitk::FiberBundleXWriter::~FiberBundleXWriter()
{}

mitk::FiberBundleXWriter * mitk::FiberBundleXWriter::Clone() const
{
  return new mitk::FiberBundleXWriter(*this);
}

void mitk::FiberBundleXWriter::Write()
{

  std::ostream* out;
  std::ofstream outStream;

  if( this->GetOutputStream() )
  {
    out = this->GetOutputStream();
  }else{
    outStream.open( this->GetOutputLocation().c_str() );
    out = &outStream;
  }

  if ( !out->good() )
  {
    mitkThrow() << "Stream not good.";
  }

  try
  {
    const std::string& locale = "C";
    const std::string& currLocale = setlocale( LC_ALL, NULL );
    setlocale(LC_ALL, locale.c_str());


    std::locale previousLocale(out->getloc());
    std::locale I("C");
    out->imbue(I);

    std::string filename = this->GetOutputLocation().c_str();

    mitk::FiberBundleX::ConstPointer input = dynamic_cast<const mitk::FiberBundleX*>(this->GetInput());
    std::string ext = itksys::SystemTools::GetFilenameLastExtension(this->GetOutputLocation().c_str());

    if (ext==".fib" || ext==".vtk")
    {
        MITK_INFO << "Writing fiber bundle as binary VTK";
        vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
        writer->SetInputData(input->GetFiberPolyData());
        writer->SetFileName(this->GetOutputLocation().c_str());
        writer->SetFileTypeToBinary();
        writer->Write();
    }
    else if (ext==".afib")
    {
        itksys::SystemTools::ReplaceString(filename,".afib",".fib");
        MITK_INFO << "Writing fiber bundle as ascii VTK";
        vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
        writer->SetInputData(input->GetFiberPolyData());
        writer->SetFileName(this->GetOutputLocation().c_str());
        writer->SetFileTypeToASCII();
        writer->Write();
    }
    else if (ext==".avtk")
    {
        itksys::SystemTools::ReplaceString(filename,".avtk",".vtk");
        MITK_INFO << "Writing fiber bundle as ascii VTK";
        vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
        writer->SetInputData(input->GetFiberPolyData());
        writer->SetFileName(this->GetOutputLocation().c_str());
        writer->SetFileTypeToASCII();
        writer->Write();
    }
    else if (ext==".trk")
    {
        MITK_INFO << "Writing fiber bundle as TRK";
        TrackVisFiberReader trk;
        trk.create(filename, input.GetPointer());
        trk.writeHdr();
        trk.append(input.GetPointer());
    }

    setlocale(LC_ALL, currLocale.c_str());
    MITK_INFO << "Fiber bundle written";
  }
  catch(...)
  {
    throw;
  }
}
