#include "unittests.h"
#include "util.h"
void testNPaths(VMPrototype *vm){
//     DIRECT PATHING


        NPath np(5,false);

        State o(5,-1.0);
        o[0]=0;
        np.setOrigin(o);
        State s1(5,-2.0);
        s1[0]=1;

        State s2(5,-1.0);
        s2[0]=1;
        State s3(5,-0.0);
        s3[0]=1;
        np.addState(s1);
        np.addState(s2);
        np.addState(s3);
        np.setOrigin(np.lastAbsolute());
        test(np);
        vm->executeNPath(np);



}
void testScripting(VirtualPrinter *vm){
    //SCRIPTING

        QString script_;
        { // load the source file into the DOM document
          QFile scriptFile("../../../media/TestScript.js");
          if (!scriptFile.open(QFile::ReadOnly |QIODevice::Text)) {
              printf("\nFAILED TO LOAD SCRIPT");
              return;
          }
          QTextStream in(&scriptFile);
          script_ = in.readAll();
          scriptFile.close();
        }

        QString errors = runScript(vm,script_);
        printf("Script: %s",script_.toStdString().c_str());
        printf("Script Engine Errors: %s",errors.toStdString().c_str());
}

void testVoxels(VMPrototype *vm){
    //// XDFL VOXEL
        Material m;
        m.id =1;
        m.name="test";
        m.Q = 1;
        m.property["pathspeed"] = "50";
        m.property["compressionVolume"] = "1.0";

        vm->bays[0]->setMaterial(m);

        XDFLVoxel vox;
        vox.id = 1;
        vox.volume=1;
        vox.x=0;
        vox.y=30;
        vox.z=0;


        NPath voxpath = vm->bays[0]->onVoxel(vox);
        vm->executeNPath(voxpath);


        voxpath.setOrigin(voxpath.lastAbsolute());

        vm->executeNPath(voxpath);
        printf("\n");
        voxpath.toAbsolute();
        //voxpath.setOrigin(voxpath.lastAbsolute());
        printf("\n NPATH SHIFTED");
        voxpath.toRelative();
        voxpath.lastAbsolute();
        test(voxpath);
        printf("\n");
}
void testXDFLPaths(VMPrototype *vm){
//    XDFL PATH
        XDFLPath path1;
        XDFLPath path2;
        NPath pathed1;
        NPath pathed2;
        {
        Point p1,p2,p3;
        p1.x=0;
        p1.y=0;
        p1.z=0;
        p2.x=0;
        p2.y=-6;
        p2.z=0;
        p3.x=0;
        p3.y=-70;
        p3.z=0;
        path1.points.append(p1);
        path1.points.append(p2);
        path1.points.append(p3);
        path1.materialID=1;
        }

//        pathed1 = vm.xyzmotion->pathAlong(path1,70);
//        vm.executeNPath(pathed1);

        Material m;
        m.id =1;
        m.name="test-silicone";
        m.Q = 20;// near silicone mm^3/s
        m.property["pathspeed"] = "30";//mm/2
        m.property["compressionVolume"]="2.52";//mm^3
        vm->bays[0]->setMaterial(m);

        pathed1 = vm->bays[0]->onPath(path1);
        vm->executeNPath(pathed1);
        //test(pathed1);

    }
void testXDFLParsing(VMPrototype *vm){
    QDomDocument xdflDom;
    QString xdflFilePath="../../../media/testxdfl-test.xdfl";
    // load the XDFL file into the DOM document
    {
      QFile xdflFile(xdflFilePath);
      if (!xdflFile.open(QFile::ReadOnly)) {
          printf("\nFAILED TO OPEN XDFL FILE\n");
          return;
      }
      xdflDom.setContent(&xdflFile);
      xdflFile.close();
    }

    XDFLHandler *handler = new XDFLHandler();
    printf("\nhandler made");
    handler->setVM(vm);
    handler->loadFromDom(xdflDom);
    printf("\nDomLoaded");
    QList<Material> testing = handler->getMaterials();
    vm->bays[0]->setMaterial(testing[0]);

    printf("\nGOT TO START");
    //handler->runXDFL();
    handler->start();

    while(!handler->isFinished())
    {

    }

}
