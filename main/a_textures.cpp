
#include <core/image.h>
#include <core/float4.h>

#include <rt/solids/infiniteplane.h>
#include <rt/solids/quad.h>

#include <rt/groups/simplegroup.h>

#include <rt/cameras/perspective.h>

#include <rt/textures/imagetex.h>
#include <rt/materials/flatmaterial.h>
#include <rt/integrators/raytrace.h>

#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/textures/checkerboard.h>
#include <rt/textures/perlin.h>

using namespace rt;

namespace {

    class QuadMapper : public CoordMapper {
    public:
        QuadMapper(const Vector& offset, const Vector& scale = Vector::rep(1.f)) : offset(offset), scale(scale) { }
        virtual Point getCoords(const Intersection& hit) const {
            Float4 p = Float4(scale) * Float4(hit.local()) + Float4(offset);
            return Point(p[0], p[1], p[2]);
        }

    private:
        Vector offset;
        Vector scale;
    };

    Group* imageDebugTextures(ImageTexture::BorderHandlingType bh) {

        SimpleGroup* scene = new SimpleGroup();
        Image img(4, 4);
        img.clear(RGBColor::rep(0.4f));
        img(1, 1) = RGBColor(1.f, 0.f, 0.f);
        img(2, 1) = RGBColor(0.f, 1.f, 0.f);
        img(1, 2) = RGBColor(0.f, 0.f, 1.f);
        img(2, 2) = RGBColor(1.f, 1.f, 1.f);

        FlatMaterial* nearest = new FlatMaterial(new ImageTexture(img, bh, ImageTexture::NEAREST));
        FlatMaterial* bilinear = new FlatMaterial(new ImageTexture(img, bh, ImageTexture::BILINEAR));

        CoordMapper* mapper = new QuadMapper(Vector::rep(-1.f), Vector::rep(4.0f));

        scene->add(new Quad(Point(-0.7f, 2.0f, -1.4f), Vector(1.6f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 1.6f), mapper, nearest));
        scene->add(new Quad(Point(-0.7f, 0.62f, -2.56f), Vector(1.6f, 0.0f, 0.0f), Vector(0.f, 1.28f, 0.96f), mapper, bilinear));

        return scene;
    }

    Group* imageTexturesBorder() {

        SimpleGroup* scene = new SimpleGroup();      

        ImageTexture* clampTex = new ImageTexture("models/stones_diffuse.png", ImageTexture::CLAMP, ImageTexture::NEAREST);
        FlatMaterial* clamp = new FlatMaterial(clampTex);

        ImageTexture* mirrorTex = new ImageTexture("models/stones_diffuse.png", ImageTexture::MIRROR, ImageTexture::BILINEAR);
        FlatMaterial* mirror = new FlatMaterial(mirrorTex);

        scene->add(new InfinitePlane(Point(0.0f,0.0f,-0.004f), Vector(-0.02f, -0.02f, 1.0f), nullptr, clamp));
        scene->add(new InfinitePlane(Point(0.0f,0.0f,-0.001f), Vector(0.02f, -0.02f, 1.0f), nullptr, mirror));


        return scene;
    }

    Group* imageTexturesInterpolate() {

        SimpleGroup* scene = new SimpleGroup();      

        ImageTexture* nearTex = new ImageTexture("models/stones_diffuse.png", ImageTexture::REPEAT, ImageTexture::NEAREST);
        FlatMaterial* near = new FlatMaterial(nearTex);

        ImageTexture* interTex = new ImageTexture("models/stones_diffuse.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
        FlatMaterial* inter = new FlatMaterial(interTex);

        scene->add(new InfinitePlane(Point(0.1f, -1.5f,0.15f), Vector(0.1f, 0.0f, 1.0f), nullptr, near));
        scene->add(new InfinitePlane(Point(0.1f, -1.5f,0.15f), Vector(-0.1f, 0.0f, 1.0f), nullptr, inter));

        return scene;
    }


    Group* proceduralTextures() {
        SimpleGroup* scene = new SimpleGroup();

        CheckerboardTexture* checkerboardTex = new CheckerboardTexture(RGBColor(1.0f,0.9f,0.7f), RGBColor(0.2f,0.2f,0.0f));
        FlatMaterial* checkerboard = new FlatMaterial(checkerboardTex);

        PerlinTexture* perlinTex = new PerlinTexture(RGBColor(1.0f,1.0f,0.9f), RGBColor(0.5f,0.5f,1.0f));
        perlinTex->addOctave(0.5f, 5.0f);
        perlinTex->addOctave(0.25f, 10.0f);
        perlinTex->addOctave(0.125f, 20.0f);
        perlinTex->addOctave(0.125f, 40.0f);
        FlatMaterial* perlin = new FlatMaterial(perlinTex);

        scene->add(new InfinitePlane(Point(0.0f,0.0f,-0.018f), Vector(0.01f, 0.0f, 1.0f), nullptr, checkerboard));
        scene->add(new InfinitePlane(Point(0.0f,0.0f,-0.02f), Vector(-0.01f, 0.0f, 1.0f), nullptr, perlin));

        return scene;
    }

}


void a_textures() {
    Image img(800, 800);
    World world;
    PerspectiveCamera cam(Point(0.1f, -1.5f, 0.225f), Vector(0.f, 1.f, -0.5f), Vector(0.f, 0.f, 1.f), 1.0f, 1.0f);
    RayTracingIntegrator integrator(&world);
    Renderer engine(&cam, &integrator);

    world.scene = proceduralTextures();
    engine.render(img);
    img.writePNG("a6-2a.png");

    world.scene = imageTexturesBorder();
    engine.render(img);
    img.writePNG("a6-2b.png");

    world.scene = imageTexturesInterpolate();
    engine.render(img);
    img.writePNG("a6-2c.png");

    world.scene = imageDebugTextures(ImageTexture::CLAMP);
    engine.render(img);
    img.writePNG("a6-2d.png");

    world.scene = imageDebugTextures(ImageTexture::REPEAT);
    engine.render(img);
    img.writePNG("a6-2e.png");

    world.scene = imageDebugTextures(ImageTexture::MIRROR);
    engine.render(img);
    img.writePNG("a6-2f.png");
}
