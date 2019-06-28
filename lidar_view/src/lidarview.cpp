#include <QVBoxLayout>

#include <rviz/visualization_manager.h>
#include <rviz/display.h>
#include <rviz/render_panel.h>
#include <string>

#include "../include/lidar_view/lidarview.hpp"

LidarView::LidarView( std::string topicToRead, QWidget* parent ) : QWidget( parent )
{
  render_panel = new rviz::RenderPanel();
  QVBoxLayout* main_layout = new QVBoxLayout;
  main_layout->addWidget( render_panel );

  // Set the top-level layout for this LidarView widget.
  setLayout( main_layout );

  // Next we initialize the main RViz classes.
  //
  // The VisualizationManager is the container for Display objects,
  // holds the main Ogre scene, holds the ViewController, etc.  It is
  // very central and we will probably need one in every usage of
  // librviz.
  manager = new rviz::VisualizationManager( render_panel );
  render_panel->initialize( manager->getSceneManager(), manager );
  render_panel->setMinimumSize(200,400);
  manager->initialize();
  manager->startUpdate();

  // Create a laser display.
  laser_display = manager->createDisplay( "rviz/LaserScan", "Laser scan", true );
  ROS_ASSERT( laser_display != NULL ); // Vérifie que le display n'est pas vide

  // Setup des paramètres
  manager->setFixedFrame("laser");
  laser_display->subProp("Topic")->setValue(topicToRead.c_str());
  laser_display->subProp("Style")->setValue("Points");
  laser_display->subProp("Size (Pixels)")->setValue("3");
  laser_display->subProp("Alpha")->setValue("1");
  laser_display->subProp("Decay Time")->setValue("0");
  laser_display->subProp("Position Transformer")->setValue("XYZ");
  laser_display->subProp("Color Transformer")->setValue("Intensity");
  laser_display->subProp("Channel Name")->setValue("x");
  laser_display->subProp("Invert Rainbow")->setValue("true");
  laser_display->subProp("Autocompute Intensity Bounds")->setValue("true");
}

LidarView::~LidarView()
{
  delete manager;
}
