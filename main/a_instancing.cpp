#include <core/image.h>
#include <rt/cameras/perspective.h>
#include <rt/groups/group.h>
#include <rt/groups/simplegroup.h>
#include <rt/primmod/instance.h>
#include <rt/integrators/casting.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/solids/infiniteplane.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>

using namespace rt;

void addTree(Group* g, int trunkTessel, float trunkHeight, float trunkRadius, float crownHeight, float crownRadius, int crownTessel, int crownSteps) {
    Vector ex(1.0f, 0.0f, 0.0f);
    Vector ey(0.0f, 0.0f, 1.0f);
    Vector ez(0.0f, 1.0f, 0.0f);

    //trunk
    float trunkStep = (2 * pi) / trunkTessel;

    for (int i = 0; i < trunkTessel; ++i) {
        float angle = i * trunkStep;
        float angleNext = (i+1) * trunkStep;
        
        Point start(trunkRadius * sin(angle), 0.0f, trunkRadius * cos(angle));
        Point end(trunkRadius * sin(angleNext), 0.0f, trunkRadius * cos(angleNext));
        g->add(new Quad(start, end-start, Vector(0.0f, trunkHeight, 0.0f), nullptr, nullptr));
    }

    float crownStep = (2 * pi) / crownTessel;

    //crown
    for (int i = 0; i < crownSteps; ++i) {
        float height = trunkHeight + i * crownHeight / crownSteps;
        
        float x = float(crownSteps-i-1)/crownSteps;
        float stepRadius = crownRadius * sin(x*pi);
        if (stepRadius > 0.0f) {
            float sphereRadius = 1.5f * pi * stepRadius / crownTessel;
            for (int j = 0; j < crownTessel; ++j) {
                float angle = j * crownStep;
                g->add(new Sphere(
                    Point(stepRadius * sin(angle), height, stepRadius * cos(angle)),
                    sphereRadius,
                    nullptr, nullptr)
                );
            }
        }
        g->add(new Sphere(Point(0.0f, trunkHeight, 0.0f), trunkRadius, nullptr, nullptr));
        g->add(new Sphere(Point(0.0f, trunkHeight + crownHeight - crownStep*1.5f, 0.0f), trunkRadius, nullptr, nullptr));
    }
}

void a_instancing() {
    Image img(800, 600);

    SimpleGroup* tree = new SimpleGroup();
    addTree(tree, 16, 3.0f, 0.5f, 5.0f, 2.0f, 8, 8);
    tree->rebuildIndex();

    SimpleGroup* scene = new SimpleGroup();

    Instance* normal = new Instance(tree);
    scene->add(normal);

    float circleRadius = 18.0f;
    for (int i = 0; i < 11; ++i) {
        float angle = 2.0f * i * pi / 11.0f;
        Instance* itree = new Instance(tree);
        itree->scale(Vector(1.0f, 1.0f + sin(i) * 0.3f, 1.0f));
        itree->translate(Vector(sin(angle) * circleRadius, 0.0f, cos(angle) * circleRadius));
        scene->add(itree);
    }

    {
        Instance* broken = new Instance(tree);
        broken->rotate(Vector(0.3f, 0.0f, 0.7f),-1.0f);
        broken->translate(Vector(5.0f, -0.5f, 0.0f));
        scene->add(broken);
    }

    {
        Instance* broken = new Instance(tree);
        broken->rotate(Vector(0.7f, 0.0f, -0.3f),-1.0f);
        broken->translate(Vector(5.0f, -0.5f, 0.0f));
        scene->add(broken);
    }

    {
        Instance* flat = new Instance(tree);
        flat->scale(Vector(0.3f, 1.5f, 1.5f));
        flat->translate(Vector(-11.0f, 0.0f, 0.0f));
        scene->add(flat);
    }

    scene->add(new InfinitePlane(Point(0,0,0), Vector(0, 1, 0), nullptr, nullptr));
    scene->rebuildIndex();

    World world;
    world.scene = scene;
    RayCastingIntegrator integrator(&world);

    PerspectiveCamera cam(Point(-3.75f, 20, 40), Vector(0.1f, -0.5f, -1), Vector(0, 1, 0), pi/4, pi/3);
    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG("a4-1.png");
}