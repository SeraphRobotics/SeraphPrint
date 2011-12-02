#include "xdflhandler.h"
#include "util.h"

XDFLHandler::XDFLHandler():pause_(false),vm_(),xdfldom_(),laststate_(),current_material_(0),current_command_(0)
{
}

void XDFLHandler::setVM(VMPrototype* vm){
    vm_ = vm;
    laststate_= State(vm_->nstatesize(),0.0);
}

void XDFLHandler::run()
{
    printf("\nBefore calling runXDFL()");
    runXDFL();
    exec();
}

QList<Material> XDFLHandler::getMaterials(){
    QMapIterator<int,Material> keys(mat_map);
    QList<Material> materials;
    while(keys.hasNext()){
        keys.next();
        materials.append(keys.value());
    }
    return materials;
}

void XDFLHandler::pause(bool paused){
    pause_ = paused;
}



NPath XDFLHandler::dwell(double time_in_ms){
    double nstate = vm_->nstatesize();
    NPath n(nstate,true);
    State tempstate(nstate,0.0);
    tempstate[0] = time_in_ms/1000.0;
    n.addState(tempstate);
    return n;
}

void XDFLHandler::runNPath(NPath n){
    n.setOrigin(laststate_);
    laststate_ = n.lastAbsolute();
    vm_->executeNPath(n);
}

void XDFLHandler::loadFromDom(QDomDocument document){
    xdfldom_ = document;


    QDomElement root = document.documentElement();
    if(root.isNull()){
        printf("\nNULL ROOT");
        return;
    }
    QDomNode palette = root.namedItem("Palette");

    if (palette.isNull()){
        printf("\nNULLPALETTE");
        return;
    }
    commands_ = root.namedItem("commands");
    current_command_ = 0;

    QDomNodeList materialTags  = palette.childNodes();
    for(int k=0; k<materialTags.length();k++){
        if ("material"==materialTags.at(k).nodeName().toLower()){
            Material m = materialFromDom(materialTags.at(k));
            mat_map[m.id]=m;
        }
    }
}

void XDFLHandler::setMaterial(int id){
    if (0==current_material_){
        current_material_ = id;
    }else if ((id == current_material_)||(0==id)){
        return;
    }else if (!mat_map.keys().contains(id)){
        printf("material not found");
        emit needMaterialChange(id);
        // This should be checked at loading of commands
    }else if(!material_bay_mapping_.keys().contains(id)){
        emit needMaterialChange(id);
    }else{
        // THIS MAY BE A PROBLEMATIC WAY OF HANDELING SHIFTING OF  THE TOOL BAYS
        Point Pnew = pointFromQVector(material_bay_mapping_[id]->getLocation());
        Point Pold = pointFromQVector(material_bay_mapping_[current_material_]->getLocation());
        Point delta = subtractpoints(Pnew,Pold);
        double speed = material_bay_mapping_[id]->getMaterial().property["pathspeed"].toDouble();
        current_material_ = id;
        printf("material Change");
        runNPath(vm_->xyzmotion->pathTo(delta.x,delta.y,delta.z,speed));
    }



}

bool XDFLHandler::runXDFL()
{
    printf("\nIn runXDFL()");
    runXDFL(commands_);
}

bool XDFLHandler::runXDFL(QDomNode command){
    foreach(Bay* b,vm_->bays){
        material_bay_mapping_[b->getMaterial().id] = b;
    }

    Point last_end_point;
    last_end_point.x=0;
    last_end_point.y=0;
    last_end_point.z=0;
    Point new_start_point;
    double speed;

    QDomNodeList commandTags  = command.childNodes();
    printf("\nBefore while loop.");
    fflush(stdout);
    while(current_command_<commandTags.length() && !pause_){
        printf("\nIn while loop.");
        fflush(stdout);
        while(pause_)
        {
            msleep(100);
        }

        QDomElement commandTag= commandTags.at(current_command_).toElement();

        if ("path"==commandTag.nodeName().toLower()){
            XDFLPath p = pathFromQDom(commandTag);

            if (p.isNull()){continue;}// check to see if the path is valid

            // Check to see if the material is listed in the header or if we are switching bays.
            setMaterial(p.materialID);

            // Set the new interpath speed
            // we use the speed of the queued path for the between path.
            if((0.0!=p.speed)){
                speed = p.speed;
            }else{
                speed = mat_map[p.materialID].property["pathspeed"].toDouble();
            }


            // if the start of this path is not close to the end of the last one,
            // we need to move between the points.
            new_start_point = p.start();
            if(!pointsEqual(new_start_point,last_end_point,0.1)){ // ensures that the machine doesnt jump between points
                Point delta = subtractpoints(new_start_point,last_end_point);
                runNPath(vm_->xyzmotion->pathTo(delta.x,delta.y,delta.z,speed));
            }


            NPath n(vm_->nstatesize(),false);
            //if((0==p.materialID)&&(0.0!=p.speed)){// if the path is not an extrusion path we move along it
                 n = vm_->xyzmotion->pathAlong(p,speed);
            //}else{// if it is an extrusion path we feed it to the proper bay.
                 //n = material_bay_mapping_[p.materialID]->onPath(p);
            //}
            runNPath(n);
            last_end_point=p.end();

//            /** for debuggins
//            QString teststr("");
//            QTextStream testss(&teststr,QFile::WriteOnly);
//            testss<<"NPath"<<i;
//            test(teststr,n);
//            nap(1000);
////            /**/

        }else if ("voxel"==commandTag.nodeName().toLower()){
            // if the voxel is not close to the end of the last movement,
            // we need to move between the points.

            XDFLVoxel v = voxFromQDom(commandTag);

            // Check to see if the material is listed in the header.
            setMaterial(v.id);



            new_start_point.x = v.x;
            new_start_point.y = v.y;
            new_start_point.z = v.z;

            //MAKE RELATIVE VOXEL to send to bay
            Point delta = subtractpoints(new_start_point,last_end_point);
            v.x = delta.x;
            v.y = delta.y;
            v.z = delta.z;

            //run NPATH from bay
            runNPath(material_bay_mapping_[v.id]->onVoxel(v));

            //SET LAST_END_POINT to location of voxel in ABS coordinates
            last_end_point = new_start_point;


        }else if ("dwell"==commandTag.nodeName().toLower()){
            double dwelltime = commandTag.text().toDouble();
            runNPath(dwell(dwelltime));
        }else{
        }
        current_command_++;
    }
    printf("Exiting while loop.");
    fflush(stdout);
    return true;
}

void XDFLHandler::pause()
{
    return;
}

void XDFLHandler::resume()
{
    return;
}

int XDFLHandler::getNumCommands()
{
    return commands_.childNodes().length();
}

