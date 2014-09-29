function onStartVoxel(){
    var cmds = [];
    return cmds
}

function onEndVoxel(){
    var cmds = [];
    return cmds
}


function onVoxel(voxel){
    var cmds = [];
    var time = voxel.volume / material.Q*1000.0;
    var suckbackQ = 1000*60;
    var amount = material.compressionVolume*revolutionsPerVolume;
    var cmd1 = "G1 X"+voxel.x+" Y"+voxel.y+" Z"+voxel.z+" F"+material.pathspeed;
    var cmd2 = "G1 "+actuatorIDs[0]+amount + " F"+suckbackQ;
    var cmd3 = "G4 P"+time;
    amount = - amount;
    var cmd4 = "G1 "+actuatorIDs[0]+amount+ " F"+suckbackQ;
    cmds[0] = cmd1;
    cmds[1] = cmd2;
    cmds[2] = cmd3;
    cmds[3] = cmd4;
    return cmds
}
function onStartPath(){
    var cmds = [];
    var suckbackQ = 1000*60;
    var amount = material.compressionVolume*revolutionsPerVolume;
    var cmd2 = "G1 "+actuatorIDs[0]+amount + " F"+suckbackQ;
    cmds[0]=cmd2;
    return cmds;
}
function onEndPath(){
    var cmds = [];
    var suckbackQ = 1000*60;
    var amount = -material.compressionVolume*revolutionsPerVolume;
    var cmd2 = "G1 "+actuatorIDs[0]+amount  + " F"+suckbackQ;
    cmds[0]=cmd2;
    return cmds;
}

function onPath(path){
    var speed = material.pathspeed*60;
    var cmds = [];
    function delta(p1,p2){
        return Math.sqrt(Math.pow(p1.x-p2.x)+Math.pow(p1.y-p2.y)+Math.pow(p1.z-p2.z));
    }
    var i=0;
    var lastPoint = path.points[0];
    for (i=1; i<path.points.length; i++){
        var point = path.points[i]
        var d = delta(lastpoint,point)
        var e = d/speed*revolutionsPerVolume;
        var cmd = "G1 X"+point.x+" Y"+point.y+" Z"+point.z" "+actuatorIDs[0]+e+" F"+speed;
        cmds[cmds.length]=cmd;
    }

    return cmds;
}
    