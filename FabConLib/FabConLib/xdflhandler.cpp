#include "xdflhandler.h"
#include "testing/util.h"
#include <QApplication>


XDFLHandler::XDFLHandler():handlerstate_(XDFLHandler::Stopped),estimationDone_(false),
    estimatedTime_(0),estimatedVolume_(0),current_material_(0),current_command_(0)

{
    last_end_point_ = FabPoint();
}

XDFLHandler::XDFLHandler(VMPrototype* vm, QDomDocument xdfl) {
    XDFLHandler::XDFLHandler();
    setVM(vm);
    loadFromDom(xdfl);
}

void XDFLHandler::updateState(){
    if (vm_->isInitialized()&&!commands_.isEmpty()){
        handlerstate_=XDFLHandler::Ready;
    }else{
        handlerstate_=XDFLHandler::Stopped;
    }
}

double XDFLHandler::getEstimatedTime() {
    if (!estimationDone_) {
        estimate();
    }
    return estimatedTime_;
}

double XDFLHandler::getEstimatedVolume() {
    if (!estimationDone_) {
        estimate();
    }
    return estimatedVolume_;
}

QMap<int,Material> XDFLHandler::getMaterials() {
//    QMapIterator<int,Material> keys(mat_map);
//    QList<Material> materials;
//    while(keys.hasNext()) {
//        keys.next();
//        materials.append(keys.value());
//    }
//    return materials;
    return mat_map;
}

// Threadsafe slot. Processing can only be paused if it is currently running.
void XDFLHandler::pause() {
    QMutexLocker locker(&mutex_);

    if (handlerstate_ == XDFLHandler::Running) {
        printf("\nPausing...\n");
        handlerstate_ = XDFLHandler::Paused;
    }

    // (mutex automatically released upon locker destruction)
}

// Threadsafe slot. Processing can only be resumed if it currently paused.
void XDFLHandler::resume() {
    QMutexLocker locker(&mutex_);

    if (handlerstate_ == XDFLHandler::Paused) {
        printf("\nResuming...\n");
        handlerstate_ = XDFLHandler::Running;
        resumed_.wakeAll();
    }

    // (mutex automatically released upon locker destruction)
}

// Threadsafe slot. Processing can be cancelled if it is running or paused.
void XDFLHandler::cancel() {
    QMutexLocker locker(&mutex_);

    printf("\ncanceling...");
    if (handlerstate_ == XDFLHandler::Running) {
        handlerstate_ = XDFLHandler::Stopped;
    }
    else if (handlerstate_ == XDFLHandler::Paused) {
        handlerstate_ = XDFLHandler::Stopped;
        // Additionally wake the thread so that it can be stopped.
        resumed_.wakeAll();
    }

    // (mutex automatically released upon locker destruction)
}

void XDFLHandler::setVM(VMPrototype* vm) {
    vm_ = vm;
    laststate_= State(vm_->nstatesize(),0.0);

    //connect(this,SIGNAL(doNPath(NPath)),vm,SLOT(executeNPath(NPath)));
    updateState();
}

void XDFLHandler::loadFromDom(QDomDocument xdfl) {

    QDomElement root = xdfl.documentElement();
    if (root.isNull()) {
        printf("\nNULL ROOT");
        return;
    }
    QDomNode paletteNode = root.namedItem("palette");
    if (paletteNode.isNull()) {
        paletteNode = root.namedItem("Palette");// its case sensitive
        if (paletteNode.isNull()) {
            printf("\nNULL PALETTE");
            return;
        }
    }
    QDomNode commandsNode = root.namedItem("commands");
    if (commandsNode.isNull()) {
        printf("\nNULL COMMANDS");
        return;
    }
    commands_ = commandsNode.childNodes();
    emit numberOfCommands(commands_.length());
    if (commands_.isEmpty()) {
        printf("\nNO COMMANDS");
        // throw exceptions? Return false?
        return;
    }

    QDomNodeList materialTags  = paletteNode.childNodes();
    for (unsigned int k = 0; k < materialTags.length(); k++) {
        if ("material"==materialTags.at(k).nodeName().toLower()) {
            Material m = materialFromDom(materialTags.at(k));
            mat_map[m.id]=m;
        }
    }
    updateState();
}

/**
  Calculates the estimated time and volume of the currently set XDFL document.
  If there is none, estimatedTime_ and estimatedVolume_ are set to -1 and estimationDone is set to false.
  **/
void XDFLHandler::estimate() {

    // This method could be modified to find the estimated remaining time and volume by
    // starting calculation from current_command_ and using last_end_point_. Threadsafe
    // behavior would be required to obtain synchronized values for those variables.

    unsigned int current_command_est = 0; // = current_command_;
    FabPoint last_end_point_est = FabPoint(); // = last_end_point_;
    FabPoint new_start_point;
    double speed;

    estimatedTime_   = 0;
    estimatedVolume_ = 0;

    while (current_command_est < commands_.length()) {

        QDomElement commandTag = commands_.at(current_command_est).toElement();

        if ("path" == commandTag.nodeName().toLower()) {
            XDFLPath p = pathFromQDom(commandTag);

            if (p.isNull()) { continue; }// check to see if the path is valid

            // If the start of this XDFL path is not close to the end of the last one,
            // generate a transition path.
            // Set the speed of the queued XDFL path for the transition path.
            if (p.speed > 0) {
                speed = p.speed;
            } else {
                speed = mat_map[p.materialID].property["pathspeed"].toDouble();
            }
            new_start_point = p.start();

            if(!pointsEqual(new_start_point,last_end_point_est,0.1)) { // ensures that the machine doesn't jump between points
                // Add the transition path time but NOT the path volume (no extrusion)
                estimatedTime_ += distance(new_start_point,last_end_point_est) / speed;
            }

            // Add the XDFL path time and IF extruding the XDFL path volume.
            estimatedTime_ += p.length() / speed;

            if (!(p.materialID == 0 && p.speed != 0)) { // extrusion path
                QMap<QString,QString> properties = mat_map[p.materialID].property;
                estimatedVolume_ += properties.value("pathwidth").toDouble()
                                  * properties.value("pathheight").toDouble()
                                  * properties.value("areaconstant").toDouble()
                                  * p.length();
            }

            last_end_point_est = p.end();

        } else if ("voxel" == commandTag.nodeName().toLower()) {

            // If the XDFL voxel is not close to the end of the last movement,
            // we need to move between the points.
            // TODO: Add the transition path time.

            XDFLVoxel v = voxFromQDom(commandTag);

            // Add the XDFL voxel volume.
            estimatedVolume_ += v.volume;

            new_start_point.x = v.x;
            new_start_point.y = v.y;
            new_start_point.z = v.z;

            //SET LAST_END_POINT to location of voxel in ABS coordinates
            last_end_point_est = new_start_point;

        } else if ("dwell" == commandTag.nodeName().toLower()) {
            double dwelltime = commandTag.text().toDouble();

            // dwelltime is given in ms; add to estimatedTime_ in seconds.
            estimatedTime_ += dwelltime / 1000;
        } else {
        }
        current_command_est++;
    }
    estimationDone_ = true;
}

void XDFLHandler::run()
{
    // When this method is called, the current state should be Ready.

    printf("\nInitializing the XDFL handler thread.");

    QMutexLocker locker(&mutex_);
    current_command_ = 0;
    current_material_ = 0;
    last_end_point_ = FabPoint();
    if (handlerstate_ == XDFLHandler::Ready) {
        // Set up for processing.
        foreach (Bay* b,vm_->bays) {
            material_bay_mapping_[b->getMaterial().id] = b;
        }
        handlerstate_ = XDFLHandler::Running;
    }
    else {
        printf("\nERROR: XDFL handler was not ready.");
        handlerstate_ = XDFLHandler::Stopped;
    }

    while (handlerstate_ != XDFLHandler::Stopped) {
        if (handlerstate_ == XDFLHandler::Running) {
            // Allow state changes [pausing/stopping] while processing one path
            locker.unlock();
            processCommand();
            locker.relock();
            if (current_command_ == commands_.length()) {
                // XDFL file completed.
                printf("\nXDFL file processing completed.");
                handlerstate_ = XDFLHandler::Stopped;
            }
        }
        else if (handlerstate_ == XDFLHandler::Paused) {
            // Block thread until woken by resumed_.wakeAll().
            // The waking function is responsible for changing the state.
            resumed_.wait(&mutex_);
        }
        else {
            printf("\nERROR: XDFL handler state was incorrect.");
            handlerstate_ = XDFLHandler::Stopped;
        }
    }
    // XDFLHandler::Stopped:
    // Stop processing and reset progress.
    laststate_        = vm_->currentState();

    printf("\nExiting the XDFL handler thread.");
    vm_->moveToThread(QApplication::instance()->thread());
    // (mutex automatically released upon locker destruction)
}

void XDFLHandler::  processCommand() {

    FabPoint new_start_point;
    double speed=0;


    emit startingCommand(current_command_);

    QDomElement commandTag = commands_.at(current_command_).toElement();

    if ("path" == commandTag.nodeName().toLower()) {

        XDFLPath p = pathFromQDom(commandTag);

        if (p.isNull()) { return; }// check to see if the path is valid

        // Check to see if the material is listed in the header or if we are switching bays.
        setMaterial(p.materialID);

        // If the start of this XDFL path is not close to the end of the last one,
        // generate a transition path.
        // Set the speed of the queued XDFL path for the transition path.
        if (p.speed > 0) {
            speed = p.speed;
        } else {
            speed = mat_map[p.materialID].property["pathspeed"].toDouble();
        }
        new_start_point = p.start();
        if (!pointsEqual(new_start_point,last_end_point_,0.1)) { // ensures that the machine doesn't jump between points
            FabPoint delta = subtractpoints(new_start_point,last_end_point_);
            runNPath(vm_->xyzmotion->pathTo(delta.x,delta.y,delta.z,speed));
        }

        NPath n(vm_->nstatesize(),false);
        if (p.materialID == 0 && p.speed != 0) { // if the path is not an extrusion path we move along it
             n = vm_->xyzmotion->pathAlong(p,speed);
        } else { // if it is an extrusion path we feed it to the proper bay.
             n = material_bay_mapping_[p.materialID]->onPath(p);
        }
        runNPath(n);
        last_end_point_ = p.end();

    } else if ("voxel" == commandTag.nodeName().toLower()) {

        // If the XDFL voxel is not close to the end of the last movement,
        // we need to move between the points.

        XDFLVoxel v = voxFromQDom(commandTag);

        // Check to see if the material is listed in the header.
        setMaterial(v.id);

        new_start_point.x = v.x;
        new_start_point.y = v.y;
        new_start_point.z = v.z;

        //MAKE RELATIVE VOXEL to send to bay
        FabPoint delta = subtractpoints(new_start_point,last_end_point_);
        v.x = delta.x;
        v.y = delta.y;
        v.z = delta.z;

        //run NPATH from bay
        runNPath(material_bay_mapping_[v.id]->onVoxel(v));

        //SET LAST_END_POINT to location of voxel in ABS coordinates
        last_end_point_ = new_start_point;

    } else if ("dwell" == commandTag.nodeName().toLower()) {

        double dwelltime = commandTag.text().toDouble();
        runNPath(dwell(dwelltime));

    } else {
    }
    current_command_++;
    return;
}

NPath XDFLHandler::dwell(double time_in_ms) {
    double nstate = vm_->nstatesize();
    NPath n(nstate,true);
    State tempstate(nstate,0.0);
    tempstate[0] = time_in_ms/1000.0;
    n.addState(tempstate);
    return n;
}

void XDFLHandler::runNPath(NPath n) {
    n.setOrigin(laststate_);
    laststate_ = n.lastAbsolute();
    vm_->executeNPath(n);
//    emit doNPath(n);
}

void XDFLHandler::setMaterial(int id) {
    if (current_material_ == 0) {
        current_material_ = id;
    }else if ((current_material_ == id)||(id == 0)) {
        return;
    }else if (!mat_map.keys().contains(id)) {
        printf("Material not found.");
        fflush(stdout);
        emit needMaterialChange(id);
        // This should be checked at loading of commands
    }else if(!material_bay_mapping_.keys().contains(id)) {
        emit needMaterialChange(id);
    }else{
        // THIS MAY BE A PROBLEMATIC WAY OF HANDELING SHIFTING OF THE TOOL BAYS
        FabPoint Pnew = pointFromQVector(material_bay_mapping_[id]->getLocation());
        FabPoint Pold = pointFromQVector(material_bay_mapping_[current_material_]->getLocation());
        FabPoint delta = subtractpoints(Pnew,Pold);
        double speed = material_bay_mapping_[id]->getMaterial().property["pathspeed"].toDouble();
        current_material_ = id;
        printf("\nChanging materials.");
        fflush(stdout);
        runNPath(vm_->xyzmotion->pathTo(delta.x,delta.y,delta.z,speed));
    }
}
