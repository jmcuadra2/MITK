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

#include "QmitkDIAppUtilityPerspective.h"
#include "berryIViewLayout.h"

void QmitkDIAppUtilityPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout)
{
  /////////////////////////////////////////////////////
  // all di-app perspectives should have the following:
  /////////////////////////////////////////////////////

  std::string editorArea = layout->GetEditorArea();

  layout->AddStandaloneView("org.mitk.views.datamanager",
    false, berry::IPageLayout::LEFT, 0.3f, editorArea);

  layout->AddStandaloneView("org.mitk.views.controlvisualizationpropertiesview",
    false, berry::IPageLayout::BOTTOM, .2f, "org.mitk.views.datamanager");

  berry::IFolderLayout::Pointer left =
    layout->CreateFolder("org.mbi.diffusionimaginginternal.leftcontrols",
    berry::IPageLayout::BOTTOM, 0.15f, "org.mitk.views.controlvisualizationpropertiesview");

  layout->AddStandaloneViewPlaceholder("org.mitk.views.imagenavigator",
    berry::IPageLayout::BOTTOM, .4f, "org.mbi.diffusionimaginginternal.leftcontrols", false);

  /////////////////////////////////////////////
  // here goes the perspective specific stuff
  /////////////////////////////////////////////

  left->AddView("org.mitk.views.volumevisualization");
  berry::IViewLayout::Pointer lo = layout->GetViewLayout("org.mitk.views.volumevisualization");
  lo->SetCloseable(false);

  left->AddView("org.mitk.views.screenshotmaker");
  lo = layout->GetViewLayout("org.mitk.views.screenshotmaker");
  lo->SetCloseable(false);

  left->AddView("org.mitk.views.moviemaker");
  lo = layout->GetViewLayout("org.mitk.views.moviemaker");
  lo->SetCloseable(false);

  left->AddView("org.blueberry.views.logview");
  lo = layout->GetViewLayout("org.blueberry.views.logview");
  lo->SetCloseable(false);
}