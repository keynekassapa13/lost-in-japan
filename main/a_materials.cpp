
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>

#include <rt/textures/constant.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt/materials/cooktorrance.h>

#include <rt/integrators/recraytrace.h>

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

Texture* redtex;
Texture* greentex;
Texture* bluetex;
Texture* blacktex;
Texture* whitetex;

void initTextures() {
    redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    whitetex = new ConstantTexture(RGBColor::rep(1.0f));
}

}

void a7prepMaterials1(Material** materials) {
    materials[0] = new LambertianMaterial(blacktex, whitetex);
    materials[1] = new LambertianMaterial(blacktex, redtex);
    materials[2] = new LambertianMaterial(blacktex, greentex);

    materials[3] = new LambertianMaterial(blacktex, whitetex);

    materials[4] = new LambertianMaterial(blacktex, whitetex);
}

void a7prepMaterials2(Material** materials) {
    materials[0] = new LambertianMaterial(blacktex, whitetex);
    materials[1] = new LambertianMaterial(blacktex, redtex);
    materials[2] = new LambertianMaterial(blacktex, greentex);

    materials[3] = new PhongMaterial(whitetex, 10.0f);
    materials[4] = new MirrorMaterial(0.0f, 0.0f);
}


void a7prepMaterials3(Material** materials) {
    materials[0] = new LambertianMaterial(blacktex, whitetex);
    materials[1] = new LambertianMaterial(blacktex, redtex);

    CombineMaterial* green = new CombineMaterial();
    green->add(new LambertianMaterial(blacktex, greentex), 0.5f);
    green->add(new PhongMaterial(whitetex, 2.0f), 0.5f);
    materials[2] = green;

    materials[3] = new MirrorMaterial(2.485f, 3.433f);

    MirrorMaterial* mirror = new MirrorMaterial(0.0f, 0.0f);
    PhongMaterial* phong = new PhongMaterial(whitetex, 10.0f);
    CombineMaterial* combined = new CombineMaterial();
    combined->add(materials[0],0.2f);
    combined->add(phong,0.62f);
    combined->add(mirror,0.18f);
    materials[4] = combined;
}

void a7prepMaterials4(Material** materials) {
    materials[0] = new LambertianMaterial(blacktex, whitetex);
    materials[1] = new LambertianMaterial(blacktex, redtex);
    materials[2] = new LambertianMaterial(blacktex, greentex);

    materials[3] = new CookTorranceMaterial(greentex, .1, 0.8, 0.2);
}

void a7renderCornellbox(float scale, const char* filename, Material** materials) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);


    Material* grey = materials[0];
    Material* leftWallMaterial = materials[1];
    Material* rightWallMaterial = materials[2];
    
    Material* sphereMaterial = materials[3];
    Material* floorMaterial = materials[4];

    //walls
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, floorMaterial)); //floor
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, nullptr, grey)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, grey)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, rightWallMaterial)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, leftWallMaterial)); //left wall

    scene->add(new Sphere(Point(150.0f, 100.0f, 150.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, grey);

    //point light
    world.light.push_back(new PointLight(Point((278)*scale,529.99f*scale,(279.5f)*scale),RGBColor::rep(150000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point((278)*scale,229.99f*scale,(-359.5f)*scale),RGBColor::rep(50000.0f*scale*scale)));

    world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,279.5f*scale),RGBColor(40000.0f*scale*scale,0,0)));
    world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,249.5f*scale),RGBColor(5000.0f*scale*scale,30000.0f*scale*scale,5000.0f*scale*scale)));

    RecursiveRayTracingIntegrator integrator(&world);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}


void a_materials() {
    Material** materials = new Material*[5];
    initTextures();
    a7prepMaterials1(materials);
    a7renderCornellbox(0.001f, "a6-1a.png", materials);
    a7prepMaterials2(materials);
    a7renderCornellbox(0.001f, "a6-1b.png", materials);
    a7prepMaterials3(materials);
    a7renderCornellbox(0.001f, "a6-1c.png", materials);

    a7prepMaterials4(materials);
    a7renderCornellbox(0.001f, "a6-cook-torrance.png", materials);

    delete [] materials;
}
