#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <Eigen/Eigen>

#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h>
#endif
#include "Model.h"
#include "SimpleHiz.h"
#include "FullHiz.h"
#include "ScanlineZBuffer.h"
#include "ZBuffer.h"
#include "BaseZBuffer.h"
#include "Utils.h"
// #include "intervalZBuffer.h"

int width = 720; 
int height = 720;
std::string objPath; 
int method;

void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    ZBuffer* zbuffer;
    Model model(objPath);
    std::string methodname;
    switch (method)
    {
        case 1: zbuffer=new BaseZBuffer(width,height,model);    methodname="BaseZBuffer";       break;
        case 2: zbuffer=new ScanlineZBuffer(width,height,model);methodname="ScanlineZBuffer";   break;
        case 3: zbuffer=new SimpleHiz(width,height,model);      methodname="SimpleHiz";         break;
        case 4: zbuffer=new FullHiz(width,height,model);        methodname="FullHiz";           break;
        default:
            break;
    }
    spdlog::critical("start scan convension using "+methodname);
    double start = Utils::cpuSecond();
    zbuffer->scan();
    double end = Utils::cpuSecond();
    spdlog::critical("scan finished! time elapsed: {:.6f}s", end-start);
    Eigen::MatrixXf tmp = zbuffer->pixelMat.transpose().cast<float>();
    // std::cout<<tmp<<std::endl;
    float *pixel = tmp.data();
    glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixel); 
    glFlush();
}

int main(int argc, char **argv){
    std::cout<<"********************************************************************"<<std::endl;
    std::cout<<"Welcome to use the z-buffer series test developed by chenhong liang!"<<std::endl;
    std::cout<<"*   usage: ./CG_ZBUFFER [1/2/3/4] [objPath]                        *"<<std::endl;
    std::cout<<"*   1:BaseZBuffer       2:ScanlineZBuffer                          *"<<std::endl;
    std::cout<<"*   3: SimpleModelHiz   4:FullHiz                                  *"<<std::endl;
    std::cout<<"********************************************************************"<<std::endl;
    if(argc != 3){
        std::cout << "usage: ./CGCourseCode1_cpp  [1/2/3/4/5]   [objPath]" << std::endl;
        exit(-1);
    }

    method=argv[1][0]-'0';
    objPath = argv[2];

    //打印所有的日志
    spdlog::set_level(spdlog::level::trace); 
    spdlog::info("初始化界面");
    glutInit(&argc, argv); 
    // setting up the display RGB color model
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 
    // configure window position and size 
    glutInitWindowPosition(200, 200); 
    glutInitWindowSize(width, height); 
    // create window 
    glutCreateWindow("Z-buffer Series");
    // call the drawing function 
    glutDisplayFunc(draw); 
    glutMainLoop(); 

    return 0;
}