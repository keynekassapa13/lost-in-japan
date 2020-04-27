
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <cmath>

#include <rt/groups/simplegroup.h>
#include <rt/cameras/perspective.h>
#include <rt/primmod/bmap.h>
#include <rt/textures/imagetex.h>
#include <rt/solids/triangle.h>
#include <rt/integrators/casting.h>

using namespace rt;

void bump(Camera* cam, Texture* bumptex, const char* filename) {
    static const float scale = 0.001f;
    static const float bumbscale = 0.008f;
    Image img(800, 800);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    

    //floor
    scene->add(
        new BumpMapper(
            new Triangle(Point(000.f,000.f,000.f)*scale, Point(000.f,000.f,560.f)*scale, Point(550.f,000.f,000.f)*scale, nullptr, nullptr),
            bumptex, Point(0.0f,0.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f), bumbscale)
            );
    scene->add(
        new BumpMapper(
            new Triangle(Point(550.f,000.f,560.f)*scale, Point(550.f,000.f,000.f)*scale, Point(000.f,000.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(1.0f,1.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), bumbscale)
            ); 

    //ceiling
    scene->add(
        new BumpMapper(
            new Triangle(Point(000.f,550.f,000.f)*scale, Point(550.f,550.f,000.f)*scale, Point(000.f,550.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(0.0f,0.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), bumbscale)
        ); 
    scene->add(
        new BumpMapper(
            new Triangle(Point(550.f,550.f,560.f)*scale, Point(000.f,550.f,560.f)*scale, Point(550.f,550.f,000.f)*scale, nullptr, nullptr),
            bumptex, Point(1.0f,1.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f), bumbscale)
        ); 

    //back wall
    scene->add(
        new BumpMapper(
            new Triangle(Point(000.f,000.f,560.f)*scale, Point(000.f,550.f,560.f)*scale, Point(550.f,000.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(0.0f,0.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f), bumbscale)
        ); 
    scene->add(
        new BumpMapper(
            new Triangle(Point(550.f,550.f,560.f)*scale, Point(550.f,000.f,560.f)*scale, Point(000.f,550.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(1.0f,1.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), bumbscale)
            ); 

    //right wall
    scene->add(
        new BumpMapper(
            new Triangle(Point(000.f,000.f,000.f)*scale, Point(000.f,550.f,000.f)*scale, Point(000.f,000.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(0.0f,0.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f), bumbscale)
        );
    scene->add(
        new BumpMapper(
            new Triangle(Point(000.f,550.f,560.f)*scale, Point(000.f,000.f,560.f)*scale, Point(000.f,550.f,000.f)*scale, nullptr, nullptr),
            bumptex, Point(1.0f,1.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), bumbscale)
            );

    //left wall
    scene->add(
        new BumpMapper(
            new Triangle(Point(550.f,000.f,000.f)*scale, Point(550.f,000.f,560.f)*scale, Point(550.f,550.f,000.f)*scale, nullptr, nullptr),
            bumptex, Point(0.0f,0.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), bumbscale)
            ); 
    scene->add(
        new BumpMapper(
            new Triangle(Point(550.f,550.f,560.f)*scale, Point(550.f,550.f,000.f)*scale, Point(550.f,000.f,560.f)*scale, nullptr, nullptr),
            bumptex, Point(1.0f,1.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f), bumbscale)
        ); 

    RayCastingIntegrator integrator(&world);

    Renderer engine(cam, &integrator);
    engine.render(img);
    engine.setSamples(9);
    img.writePNG(filename);
}




void a_bumpmappers() {
    ImageTexture* bumptex = new ImageTexture("models/stones_bump.png", ImageTexture::REPEAT, ImageTexture::NEAREST);
    ImageTexture* bumptexsmooth = new ImageTexture("models/stones_bump.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    Camera* cam1 = new PerspectiveCamera(Point(0.048f, 0.043f, -0.050f), Vector(-0.3f, -0.3f, 0.7f), Vector(0, 1, 0), 0.686f, 0.686f);
    bump(cam1, bumptex, "a8-1a.png");
    bump(cam1, bumptexsmooth, "a8-1b.png");
    Camera* cam2 = new PerspectiveCamera(Point(0.278f, 0.273f, -0.800f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);
    bump(cam2, bumptexsmooth, "a8-2.png");

}