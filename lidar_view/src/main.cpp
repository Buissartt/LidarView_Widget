#include <QtGui>
#include <QApplication>
#include "../include/lidar_view/lidarview.hpp"
#include <ros/ros.h>

int main(int argc, char **argv)
{
    if(!ros::isInitialized())
    {
        ros::init(argc,argv, "lidar_view");
    }
    QApplication app(argc, argv);
    LidarView* lidar = new LidarView("/scan");
    lidar->show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
