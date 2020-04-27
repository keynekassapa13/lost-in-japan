
#include <core/image.h>
#include <core/color.h>
#include <core/random.h>

#include <rt/world.h>
#include <rt/motionblur.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/integrators/recraytrace.h>
#include <rt/primmod/bmap.h>

#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>

#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>

#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/triangle.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>

#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/combine.h>
#include <rt/materials/cooktorrance.h>
#include <rt/materials/mirror.h>

#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>

#include <algorithm>

using namespace rt;


MatLib* getBackBuildingMatlib() {
    // https://sketchfab.com/3d-models/japanese-house-20-5ae0121e33b54b7789c6b9113da444bf
    MatLib* matlib = new MatLib;

    Texture* lambert12_bclr = new ConstantTexture(RGBColor(0.36f, 0.15f, 0.08f));
    Texture* lambert17_bclr = new ConstantTexture(RGBColor::rep(0.169f));
    Texture* lambert21_bclr = new ConstantTexture(RGBColor(0.36f, 0.23f, 0.22f));
    Texture* lambert23_bclr = new ConstantTexture(RGBColor::rep(0.233f));
    Texture* lambert3_bclr = new ConstantTexture(RGBColor(0.618f, 0.622f, 0.673f));
    Texture* lambert33_bclr = new ConstantTexture(RGBColor::rep(0.01f));
    Texture* lambert37_bclr = new ConstantTexture(RGBColor::rep(0.346f));
    Texture* lambert39_bclr = new ConstantTexture(RGBColor::rep(0.895f));
    Texture* lambert43_bclr = new ConstantTexture(RGBColor::rep(0.042f));
    Texture* lambert44_bclr = new ConstantTexture(RGBColor::rep(0.857f));
    Texture* lambert46_bclr = new ConstantTexture(RGBColor::rep(0.125f));
    Texture* lambert9_bclr = new ConstantTexture(RGBColor::rep(0.329f));
    Texture* lambert6_bclr = new ConstantTexture(RGBColor(0.045f, 0.023f, 0.012f));
    Texture* lambert8_bclr = new ConstantTexture(RGBColor(0.876f, 0.845f, 0.747f));
    Texture* lambert4_bclr = new ConstantTexture(RGBColor(0.2f, 0.095f, 0.067f));

    Texture* phong1_bclr = new ConstantTexture(RGBColor::rep(0.5f));
    Texture* phong13_bclr = new ConstantTexture(RGBColor::rep(0.329f));
    Texture* phong14_bclr = new ConstantTexture(RGBColor::rep(0.838f));
    Texture* phong15_bclr = new ConstantTexture(RGBColor(0.169f, 0.022f, 0.022f));
    Texture* phong16_bclr = new ConstantTexture(RGBColor::rep(0.007));
    Texture* phong19_bclr = new ConstantTexture(RGBColor::rep(0.133));
    Texture* phong2_bclr = new ConstantTexture(RGBColor(0.378f, 0.042f, 0.036f));
    Texture* phong20_bclr = new ConstantTexture(RGBColor(0.186f, 0.412f, 0.5f));
    Texture* phong21_bclr = new ConstantTexture(RGBColor(0.187f, 0.132f, 0.103f));
    Texture* phong22_bclr = new ConstantTexture(RGBColor::rep(0.125f));
    Texture* phong23_bclr = new ConstantTexture(RGBColor::rep(0.254f));
    Texture* phong25_bclr = new ConstantTexture(RGBColor(0.2f, 0.04f, 0.04f));
    Texture* phong26_bclr = new ConstantTexture(RGBColor(0.08f, 0.01f, 0.01f));
    Texture* phong27_bclr = new ConstantTexture(RGBColor::rep(0.767f));
    Texture* phong28_bclr = new ConstantTexture(RGBColor::rep(0.297f));
    Texture* phong30_bclr = new ConstantTexture(RGBColor::rep(0.5f));
    Texture* phong31_bclr = new ConstantTexture(RGBColor(0.146f, 0.190f, 0.207f));
    Texture* phong32_bclr = new ConstantTexture(RGBColor::rep(0.422f));
    Texture* phong33_bclr = new ConstantTexture(RGBColor::rep(0.191f));
    Texture* phong34_bclr = new ConstantTexture(RGBColor::rep(0.075));
    Texture* phong36_bclr = new ConstantTexture(RGBColor::rep(0.5f));
    Texture* phong39_bclr = new ConstantTexture(RGBColor(0.519f, 0.860f, 1.0f));
    Texture* phong5_bclr = new ConstantTexture(RGBColor(0.526f, 0.694f, 0.767f));
    Texture* phong6_bclr = new ConstantTexture(RGBColor(0.112f, 0.342f, 0.404f));
    Texture* phong7_bclr = new ConstantTexture(RGBColor(0.063f, 0.193f, 0.228f));
    Texture* phong8_bclr = new ConstantTexture(RGBColor(0.018f, 0.011f, 0.011f));
    Texture* null = new ConstantTexture(RGBColor::rep(0));

    Texture* surf1_bclr = new ConstantTexture(RGBColor(1.0f, 0.979f, 0.66f));
    Texture* surf3_bclr = new ConstantTexture(RGBColor(1.0f, 0.943f, 0.878f));
    Texture* surf4_bclr = new ConstantTexture(RGBColor(0.519f, 0.86f, 1.0f));
    Texture* surf5_bclr = new ConstantTexture(RGBColor(1.0f, 0.943f, 0.712f));

    CombineMaterial* combined_mirror_yellow = new CombineMaterial();
    MirrorMaterial* mirror_mat = new MirrorMaterial(2.f, 3.f);
    Texture* yellow_tex = new ConstantTexture(RGBColor(0.467f, 0.14f, 0.09f));
    LambertianMaterial* yellow_lam = new LambertianMaterial(yellow_tex, yellow_tex);
    combined_mirror_yellow->add(mirror_mat, 0.9f);
    combined_mirror_yellow->add(yellow_lam, 0.1f);

    CombineMaterial* combined_mirror_blue = new CombineMaterial();
    Texture* blue_tex = new ConstantTexture(RGBColor(0.005f, 0.014f, 0.05f) * 10.0f);
    LambertianMaterial* blue_lam = new LambertianMaterial(blue_tex, blue_tex);
    combined_mirror_blue->add(mirror_mat, 0.4f);
    combined_mirror_blue->add(blue_lam, 0.6f);

    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* box4 = new ImageTexture("models/tex/Concrete.png");

    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);

    matlib->insert(std::pair<std::string, Material*>("lambert12", new CookTorranceMaterial(lambert12_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert17", new CookTorranceMaterial(lambert17_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert21", new CookTorranceMaterial(lambert23_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert23.001", new CookTorranceMaterial(lambert23_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert3.001", new CookTorranceMaterial(lambert3_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert33", new CookTorranceMaterial(lambert33_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert33.001", new CookTorranceMaterial(lambert33_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert37.001", new CookTorranceMaterial(lambert37_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert39.000", new CookTorranceMaterial(box4, 0.6, 0.4, 0.2) ));
    matlib->insert(std::pair<std::string, Material*>("lambert39.001", combined_mirror_yellow));
    matlib->insert(std::pair<std::string, Material*>("lambert39.002", new CookTorranceMaterial(phong1_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert43.001", new CookTorranceMaterial(lambert43_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert44.001", new CookTorranceMaterial(lambert44_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert46.001", new CookTorranceMaterial(lambert46_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert9.001", new CookTorranceMaterial(lambert9_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert6.001", new CookTorranceMaterial(lambert6_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert8.001", new CookTorranceMaterial(lambert8_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("lambert4", new CookTorranceMaterial(lambert4_bclr, 0.1, 0.8, 0.2)));

    matlib->insert(std::pair<std::string, Material*>("phong1.001",  new CookTorranceMaterial(phong1_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong13", new CookTorranceMaterial(phong13_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong13.001", new CookTorranceMaterial(phong13_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong14", new CookTorranceMaterial(phong14_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong15", new CookTorranceMaterial(phong15_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong16", new CookTorranceMaterial(phong16_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong19.001", new CookTorranceMaterial(phong19_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong2.001", new LambertianMaterial(phong2_bclr, black1)));
    matlib->insert(std::pair<std::string, Material*>("phong20.001", new CookTorranceMaterial(phong20_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong21.001", new CookTorranceMaterial(phong21_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong22.001", new CookTorranceMaterial(phong22_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong23", new CookTorranceMaterial(phong23_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong25", new CookTorranceMaterial(phong25_bclr, 0.8, 0.2, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong26", new CookTorranceMaterial(phong26_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong27.001", new CookTorranceMaterial(phong27_bclr, 0.8, 0.2, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong28.001", new CookTorranceMaterial(phong28_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong30.001", new CookTorranceMaterial(phong30_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong31.001", new CookTorranceMaterial(phong31_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong32.001", new CookTorranceMaterial(phong32_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong33.001", new CookTorranceMaterial(phong33_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong34.001", new CookTorranceMaterial(phong34_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong36.001", new CookTorranceMaterial(phong36_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong39", new CookTorranceMaterial(phong39_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong5", new CookTorranceMaterial(phong5_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong6", new CookTorranceMaterial(phong6_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong7", new CookTorranceMaterial(phong7_bclr, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("phong8", new CookTorranceMaterial(phong8_bclr, 0.1, 0.8, 0.2)));

    matlib->insert(std::pair<std::string, Material*>("surfaceShader1", new LambertianMaterial(light, light)));
    matlib->insert(std::pair<std::string, Material*>("surfaceShader3", new LambertianMaterial(surf3_bclr, surf4_bclr)));
    matlib->insert(std::pair<std::string, Material*>("surfaceShader4", new LambertianMaterial(surf4_bclr, surf4_bclr)));
    matlib->insert(std::pair<std::string, Material*>("surfaceShader5", new LambertianMaterial(surf5_bclr, surf4_bclr)));

    return matlib;
}

MatLib* getBuildingMatlib() {
    // https://sketchfab.com/3d-models/automapping-ae098bdddb0d42d688d423c153f7f7d5
    MatLib* matlib = new MatLib;

    Texture* black1 = new ConstantTexture(RGBColor(0.1f, 0.1f, 0.1f));
    Texture* black_rubber = new ConstantTexture(RGBColor::rep(0.063f));
    Texture* box3 = new ConstantTexture(RGBColor(0.5f, 0.06f, 0.06f));
    ImageTexture* blinn11 = new ImageTexture("models/tex/plastic2.png");
    ImageTexture* box4 = new ImageTexture("models/tex/Concrete.png");
    ImageTexture* box6 = new ImageTexture("models/tex/Concrete.png");
    Texture* steel = new ConstantTexture(RGBColor::rep(0.07f));
    Texture* clay = new ConstantTexture(RGBColor(0.07f, 0.01f, 0.01f));

    ImageTexture* concrete = new ImageTexture("models/tex/Concrete.png");
    ImageTexture* concrete_2 = new ImageTexture("models/tex/concrete1.png");

    Texture* dirt = new ConstantTexture(RGBColor::rep(0.25f));
    Texture* floor = new ConstantTexture(RGBColor(0.25f, 0.18f, 0.05f));
    Texture* front1 = new ConstantTexture(RGBColor::rep(0.8f));
    ImageTexture* grass = new ImageTexture("models/tex/grass.png");
    ImageTexture* int1 = new ImageTexture("models/tex/int_blue.png");
    Texture* paint1 = new ConstantTexture(RGBColor(0.479f, 0.065f, 0.065f));
    Texture* paint2 = new ConstantTexture(RGBColor(0.05f, 0.15f, 0.03f));
    Texture* paint3 = new ConstantTexture(RGBColor(0.53f, 0.47f, 0.1f));
    Texture* seiling = new ConstantTexture(RGBColor::rep(0.33f));
    ImageTexture* wood = new ImageTexture("models/tex/wood.png");
    ImageTexture* wood3 = new ImageTexture("models/tex/wood3.png");

    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f));
    Texture* light2 = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.7f);

    matlib->insert(std::pair<std::string, Material*>("black1.001", new LambertianMaterial(black1, black1)));
    matlib->insert(std::pair<std::string, Material*>("black_rubber.001", new LambertianMaterial(black_rubber, black_rubber)));
    matlib->insert(std::pair<std::string, Material*>("black_rubber.002", new LambertianMaterial(black_rubber, black_rubber)));
    matlib->insert(std::pair<std::string, Material*>("black_rubber1.001", new LambertianMaterial(light2, light2)));
    matlib->insert(std::pair<std::string, Material*>("blinn11.001",  new CookTorranceMaterial(blinn11, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("box3.001", new CookTorranceMaterial(box3, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("box4.001", new CookTorranceMaterial(box4, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("box5.001", new CookTorranceMaterial(box4, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("box6.001", new CookTorranceMaterial(box6, 0.1, 0.8, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("floor.001",  new CookTorranceMaterial(floor, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("front1.001",  new CookTorranceMaterial(front1, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("glass.001", new MirrorMaterial(2.f, 3.f)));
    matlib->insert(std::pair<std::string, Material*>("rubiroid.001", new MirrorMaterial(2.f, 3.f)));
    matlib->insert(std::pair<std::string, Material*>("clay.001", new CookTorranceMaterial(clay, 0.6, 0.4, 0.2)));

    matlib->insert(std::pair<std::string, Material*>("concrete.001", new CookTorranceMaterial(concrete, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("concrete_2.001", new CookTorranceMaterial(concrete_2, 0.8, 0.1, 0.2)));

    matlib->insert(std::pair<std::string, Material*>("dirt.001",  new CookTorranceMaterial(dirt, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("grass.001",  new CookTorranceMaterial(grass, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("int1.001",  new CookTorranceMaterial(int1, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("paint1.001",  new CookTorranceMaterial(paint1, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("paint2.001",  new CookTorranceMaterial(paint2, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("paint3.001",  new CookTorranceMaterial(paint3, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("seiling.001", new CookTorranceMaterial(seiling, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("steel.001", new CookTorranceMaterial(steel, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("steel1.001", new CookTorranceMaterial(steel, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("wood.001",  new CookTorranceMaterial(wood, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("wood2.001",  new CookTorranceMaterial(wood3, 0.8, 0.1, 0.2)));
    matlib->insert(std::pair<std::string, Material*>("wood3.001",  new CookTorranceMaterial(wood3, 0.8, 0.1, 0.2)));

    matlib->insert(std::pair<std::string, Material*>("light.001",  new LambertianMaterial(light, light)));

    Texture* null = new ConstantTexture(RGBColor::rep(0));
    matlib->insert(std::pair<std::string, Material*>("lambert12", new CookTorranceMaterial(paint1, 0.77, 0.1, 0.2)));

    return matlib;
}

MatLib* getManMatlib() {

    // https://www.cgtrader.com/free-3d-models/character/man/low-poly-medieval-cart-game-ready
    // https://sketchfab.com/3d-models/elegant-umbrella-ca9bb8c8ffc640c6a9be8ad5f341c9c4
    MatLib* matlib = new MatLib;
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.015f));

    matlib->insert(std::pair<std::string, Material*>("GTP_BMan_Jack_07_Stg_Lsn_Adl_Ccs_Gry_Mgr_BlendMaterial", new CookTorranceMaterial(black1, 0.9, 0.05, 0.1)));
    matlib->insert(std::pair<std::string, Material*>("initialShadingGroup.002", new CookTorranceMaterial(black1, 0.95, 0.05, 0.1)));
    return matlib;
}

MatLib* getBuildingAddMatlib() {
    // https://sketchfab.com/3d-models/apartment-b74b36d5ae2842919f29903a2bd5bbe2
    MatLib* matlib = new MatLib;
    RGBColor yellow_clr =  RGBColor(0.467f, 0.014f, 0.09f);
    Texture* yellow_tex = new ConstantTexture(yellow_clr);
    Texture* grey_tex = new ConstantTexture(RGBColor::rep(0.4f));
    matlib->insert(std::pair<std::string, Material*>("window.001", new MirrorMaterial(2.f, 3.f)));
    matlib->insert(std::pair<std::string, Material*>("window",  new MirrorMaterial(2.f, 3.f)));
    matlib->insert(std::pair<std::string, Material*>("white", new CookTorranceMaterial(grey_tex, 0.1, 0.8, 0.2)));
    return matlib;
}

void a_competition() {

    // High Res
    Image img(1200, 1600);
    // Low Res
    // Image img(600, 800);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    BVH* scene = new BVH();
    world.scene = scene;

    // Camera for building 1
    // PerspectiveCamera* cam = new PerspectiveCamera(Point(0.6f, 0.4f, 0.2f), Vector(-0.5f, 0, 1), Vector(0, 1, 0), pi/3, pi/4);

    // Main Camera
    PerspectiveCamera* cam = new PerspectiveCamera(Point(0.2f, 0.2f, -0.15f), Vector(0, 0, 1), Vector(0, 1, 0), pi/3, pi/4);
    // DOFPerspectiveCamera* cam = new DOFPerspectiveCamera(Point(0.2f, 0.2f, -0.15f), Vector(0, 0, 1), Vector(0, 1, 0), pi/3, pi/4, 0.7f, 0.0155f);

    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.1f));
    Texture* greytex = new ConstantTexture(RGBColor::rep(0.2f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    // ------------------------------------------ ALL OBJECT -------------------------------------------
    // Object
    MatLib* matlib_japan = getBackBuildingMatlib();
    loadOBJ(scene, "models/", "japanHouse.obj", matlib_japan);

    MatLib* matlib_building = getBuildingMatlib();
    loadOBJ(scene, "models/", "building.obj", matlib_building);

    MatLib* matlib_man = getManMatlib();
    loadOBJ(scene, "models/", "man.obj", matlib_man);

    MatLib* matlib_building_add = getBuildingAddMatlib();
    loadOBJ(scene, "models/", "buildingadd.obj", matlib_building_add);

    // Bump Map Floor
    ImageTexture* bumptex = new ImageTexture("models/stones_bump.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    Material* grey_cook = new CookTorranceMaterial(greytex, 0.6f, 0.4f, 0.1f);

    Material* fuzzy_mat = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f);
    Material* glass_mat = new GlassMaterial(2.f);
    CombineMaterial* sea = new CombineMaterial();
    sea->add(grey_cook, 0.5f);
    sea->add(fuzzy_mat, 0.4f);
    sea->add(glass_mat, 0.1f);

    scene->add(
        new BumpMapper(
          new Triangle(Point(-1.5f, 0.f, 0.f) * 2.0f, Point(-1.5f, 0.f, 3.0f) * 2.0f, Point(1.5f, 0.f, 0.f) * 3.0f, nullptr, sea),
            bumptex, Point(0.0f,0.0f,0.0f) * 4.5f, Point(0.0f, 3.0f, 0.0f) * 4.5f, Point(4.0f, 0.0f, 0.0f) * 4.5f, 1.0f)
            );

    // Right Wall Bump Map
    scene->add(
        new Triangle(Point(-0.35f, 0.f, 1.15f), Point(-0.35f, 0.2f, 1.15f), Point(-0.35f, 0.f, 3.f), nullptr, grey_cook)
    );
    scene->add(
        new Triangle(Point(-0.35f, 0.2f, 3.f), Point(-0.35f, 0.f, 3.f), Point(-0.35f, 0.2f, 1.15f), nullptr, grey_cook)
    );

    // Make Rain
    Texture* greytex2 = new ConstantTexture(RGBColor::rep(0.7f));
    Material* grey_mat = new LambertianMaterial(blacktex, greytex2);
    Material* grey_cook_rain = new CookTorranceMaterial(greytex2, 0.2f, 0.8f, 0.3f);
    CombineMaterial* watery_floor = new CombineMaterial();
    watery_floor->add(grey_mat,0.2);
    watery_floor->add(fuzzy_mat, 0.4);
    watery_floor->add(grey_cook_rain, 0.4);
    for (int i = 0; i < 1500; i ++) {
        MotionBlur* sphere = new MotionBlur();
        float random_size = rt::random() * 0.0001 / 2 + 0.001f;
        float random_x = rt::random() * 1.2 - 0.7;
        float random_y = rt::random() * 0.7 + 0.1;
        float random_z = rt::random() * 1.2 + 0.2;
        sphere->add(new Sphere(Point(random_x, random_y, random_z), random_size, nullptr, watery_floor));
        sphere->translate(Vector(0.0f, -0.01f, 0.0f));
        scene->add(sphere);
    }

    // Back Wall
    Material* grey_cook_2 = new CookTorranceMaterial(new ConstantTexture(RGBColor::rep(0.03f)), 0.95f, 0.05f, 0.1f);
    scene->add(new Quad(Point(-1.1f, 0.f, 2.7f), Vector(0.f, 1.9f, -1.f), Vector(2.8f, 0.f, 0.f), nullptr, grey_cook_2));

    // ------------------------------------------ LIGHTING -------------------------------------------

    RGBColor yellow_clr =  RGBColor(0.467f, 0.14f, 0.09f);
    RGBColor blue_clr = RGBColor(0.035f, 0.252f, 1.0f);
    RGBColor red_clr = RGBColor(1.0f, 0.02f, 0.02f);

    // Area Light
    ConstantTexture* lightsrctex = new ConstantTexture(blue_clr * 7.0f);
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
    Quad* light = new Quad(Point(0.213, 1.7f, 0.97f), Vector(0.5f, 0, 0) * 2.0f, Vector(0, 0, 0.5f) * 2.0f, nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);

    // BL1 Point Light fixed
    world.light.push_back(new PointLight(Point(0.35f, 0.18f, 0.6f), yellow_clr * 0.25)); // BL1 yellow

    // BL2 Point Light fixed
    world.light.push_back(new PointLight(Point(0.0f, 0.9f, 1.5f), blue_clr * 0.8f)); // BL2 sign blue
    world.light.push_back(new PointLight(Point(1.0f, 0.4f, 0.8f), yellow_clr * 1.f)); // BL2 lighting left yellow

    // Back Light
    world.light.push_back(new PointLight(Point(0.5f, 0.45f, 2.0f), blue_clr * 2.f));

    // BL1 Spot Light fixed
    world.light.push_back(new SpotLight(Point(0.385f, 0.31f, 0.35f), Vector(0.0f, -1.0f, 0.0f),  pi/5, 9.0f, yellow_clr * 0.65));  // BL1 yellow
    world.light.push_back(new SpotLight(Point(0.3f, 0.35f, 0.8f), Vector(-0.3f, -1.0f, -0.8f),  pi/12, 1.0f, yellow_clr * 1.8f));  // BL1 for the man

    // BL2 Spot Light fixed
    world.light.push_back(new SpotLight(Point(-0.28f, 0.3f, 1.31f), Vector(0.0f, -1.0f, 0.3f),  pi/12, 3.0f,  yellow_clr * 0.3f));  // BL2 yellow
    world.light.push_back(new SpotLight(Point(-0.13f, 0.28f, 1.23f), Vector(0.0f, -1.0f, 0.3f),  pi/4, 3.0f, yellow_clr * 0.1f));  // BL2 up right 1
    world.light.push_back(new SpotLight(Point(-0.09f, 0.28f, 1.23f), Vector(0.0f, -1.0f, 0.3f),  pi/4, 3.0f, yellow_clr * 0.1f));  // BL2 up right 2

    // Directional Light
    world.light.push_back(new DirectionalLight(Vector(0.2f ,-0.5f , 1.0f).normalize(), RGBColor(1.0f, 1.0f, 1.0f) * 0.15f)); // white
    world.light.push_back(new DirectionalLight(Vector(-0.2f ,-0.5f , 1.0f).normalize(), yellow_clr * 1.f)); // yellow

    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    Renderer engine(cam, &integrator);
    engine.setSamples(25);
    engine.render(img);
    img.writePNG("competition-group16.png");
}
