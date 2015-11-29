#ifndef RENDERER_H
#define RENDERER_H

#include "compound.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

class Renderer
{
//datastructures for renderer
private:

    //store camera data
    struct Camera
    {
        Camera() : height(1.0f)
        {}
        float height;
    };

	//store buffer data
    template<typename T>
    struct Buffer
    {
        Buffer<T>() : id(-1)
        {}
        GLuint id;
        std::vector<T> data;
    };

    template<typename T>
    struct uVar
    {
        uVar<T>() : id(-1)
        {}
        GLuint id;
        T value;
    };

	//mouseState
    typedef enum
    {
        IDLE = 0,
        ZOOM = 1
    }MOUSESTATE;

//variables
private:

	//screen dimensions
    static int mWidth;
    static int mHeight;
    static Camera   mCamera;

	//store FPS
    static float    mDeltaTime;
    static MOUSESTATE mState;

	//Buffer for visualising tree itself
    static Buffer<Point2D>  mTreeConnectionBuffer;  //display connections between nodes
    static Buffer<Point2D>  mTreeNodeBuffer;        //display nodes
    static Buffer<Point2D>  mSplineControlBuffer;
    static Buffer<float>    mSplineTBuffer;
    static Buffer<float>    mSplineOpacityBuffer;
	//Buffer for visualising pathes
    static Buffer<Point2D> mSplineBuffer;             //display pathes between nodes

    static GLuint vaoTreeConn;
    static GLuint vaoSpline;
    static GLuint vaoTreeNode;
    static GLuint progTreeConn;                         //display Tree
    static GLuint progSpline;                      //display Splines
    static GLuint progTreeNode;
    static int    stepsize;

    static uVar<float> minAlpha;
    static uVar<float> maxAlpha;
    static uVar<float> beta;

    static bool showTree;
    static bool showLeaves;
    static bool showSplines;

//functions
public:

	//init GLUT, GLEW, OpenGL
    static bool     initGLUT(int &argc,char **argv,unsigned int width, unsigned int height);

	//init Buffers
    static bool     initBuffers();

	//init Shaders and Program
    static bool     initProgram();

	//parse Tree into Buffer
    static bool     parseData(Compound* c);

	//run Window
    static void     run();

private:

	//GLUT Callbacks
    static void     display();
    static void     keyboard(unsigned char key, int x, int y);
    static void     mouseButton(int button, int state, int x, int y);
    static void     mouseMotion(int x, int y);
    static void     resize(int width,int height);
    static void     idle();

	//read Shader into String
    static std::string readFile(const std::string &source);

    static void setRadialPosition(Compound *c, TreeNode* t, float angleMin, float angleMax, float radius);


    static void fillBuffer(TreeNode* parent, TreeNode* node);
    static void renderTree();
    static void renderSplines();
    static void renderNodes();
    static void createSplines(std::vector<Point2D> &spline,const std::vector<Point2D> &controlPoints);
    static float alpha(float t, float ti, float tikj);
    static void validRange(float &p,float min, float max);

};


#endif //RENDERER_H
