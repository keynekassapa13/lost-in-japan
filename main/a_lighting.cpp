
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>


#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projective.h>

#include <rt/integrators/raytrace.h>

using namespace rt;

namespace {

void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(aaa, left, forward, texMapper, material));
    scene->add(new Quad(aaa, forward, up, texMapper, material));
    scene->add(new Quad(aaa, up, left, texMapper, material));
    Point bbb = aaa + forward + left + up;
    scene->add(new Quad(bbb, -forward, -left, texMapper, material));
    scene->add(new Quad(bbb, -up, -forward, texMapper, material));
    scene->add(new Quad(bbb, -left, -up, texMapper, material));
}

void makeWalls(Group* scene, float scale, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, texMapper, material)); //floor
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, texMapper, material)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, texMapper, material)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, texMapper, material)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, texMapper, material)); //left wall
}

void renderCornellboxA(float scale, const char* filename) {
    Image img(400, 400);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    DummyMaterial* mat = new DummyMaterial();

    // walls
    makeWalls(scene, scale, nullptr, mat);

    //short box
    makeBox(scene, Point(082.f, 000.1f, 225.f)*scale, Vector(158.f, 000.f, 047.f)*scale, Vector(048.f, 000.f, -160.f)*scale, Vector(000.f, 165.f, 000.f)*scale, nullptr, mat);

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, mat);

    //point light
    world.light.push_back(new PointLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(40000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point(490*scale,329.99f*scale,279.5f*scale),RGBColor(60000.0f*scale*scale,0,0)));
    world.light.push_back(new PointLight(Point(40*scale,329.99f*scale,279.5f*scale),RGBColor(0,60000.0f*scale*scale,0)));

    RayTracingIntegrator integrator(&world);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}

void renderCornellboxC(float scale, const char* filename) {
    Image img(400, 400);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    DummyMaterial* mat = new DummyMaterial();

    // walls
    makeWalls(scene, scale, nullptr, mat);

    //short box
    makeBox(scene, Point(082.f, 000.1f, 225.f)*scale, Vector(158.f, 000.f, 047.f)*scale, Vector(048.f, 000.f, -160.f)*scale, Vector(000.f, 165.f, 000.f)*scale, nullptr, mat);

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, mat);

    //point light
    world.light.push_back(new ProjectiveLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(40000.0f*scale*scale)));
    world.light.push_back(new ProjectiveLight(Point(490*scale,329.99f*scale,279.5f*scale),RGBColor(60000.0f*scale*scale,0,0)));
    world.light.push_back(new ProjectiveLight(Point(40*scale,329.99f*scale,279.5f*scale),RGBColor(0,60000.0f*scale*scale,0)));

    RayTracingIntegrator integrator(&world);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}

void renderCornellboxB(float scale, const char* filename) {
    Image img(400, 400);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    DummyMaterial* mat = new DummyMaterial();

    // walls
    makeWalls(scene, scale, nullptr, mat);

    //short box
    makeBox(scene, Point(082.f, 000.1f, 225.f)*scale, Vector(158.f, 000.f, 047.f)*scale, Vector(048.f, 000.f, -160.f)*scale, Vector(000.f, 165.f, 000.f)*scale, nullptr, mat);

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, mat);

    //point light
    world.light.push_back(new PointLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(20000.0f*scale*scale)));

    //spot light
    world.light.push_back(new SpotLight(Point(70.f, 400.f, 230.f)*scale, Vector(0.0f, -1.0f, 0.0f),  pi/4, 8.0f, RGBColor(0,60000.0f*scale*scale,0)));
    world.light.push_back(new SpotLight(Point(520.f, 300.f, 230.f)*scale, Vector(-1.0f, -1.0f, 0.0f),  pi/3, 3.0f, RGBColor(60000.0f*scale*scale,0,0)));

    //directional light
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);

    RayTracingIntegrator integrator(&world);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}
}

void a_lighting() {
    renderCornellboxA(0.001f, "a5-1.png");
    renderCornellboxA(0.01f, "a5-2.png");
    renderCornellboxB(0.001f, "a5-3.png");
    renderCornellboxB(0.01f, "a5-4.png");

    renderCornellboxC(0.001f, "a5-proj-1.png");
    renderCornellboxC(0.01f, "a5-proj-2.png");
}