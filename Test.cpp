#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkCursor2D2.h"
 
int main(int argc, char *argv[])
{
 
  //Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
 
  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Add the actor to the scene
  //renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
 
  vtkSmartPointer<vtkCursor2D2> cursor = 
      vtkSmartPointer<vtkCursor2D2>::New();
  cursor->SetModelBounds(-10,10,-10,10,0,0);
  cursor->AllOn();
  
  cursor->OutlineOn();
  /*
  unsigned char red[3] = {255,0,0};
  unsigned char green[3] = {0,255,0};
  unsigned char blue[3] = {0,0,255};
  cursor->SetPointColor(red);
  cursor->SetXAxisColor(green);
  cursor->SetYAxisColor(blue);
  */
  cursor->Update();

  vtkSmartPointer<vtkPolyDataMapper> cursorMapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cursorMapper->SetInputConnection(cursor->GetOutputPort());
  vtkSmartPointer<vtkActor> cursorActor = 
      vtkSmartPointer<vtkActor>::New();
  cursorActor->SetMapper(cursorMapper);
  renderer->AddActor(cursorActor);
  
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}