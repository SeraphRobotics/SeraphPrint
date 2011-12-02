var np = new NPath();
var s1 = new State();
var s2 = new State();
s2[0]=1.0;
s2[1]=-2.0;

np.addState(s1);
np.addState(s2);
for(var j=0; j<1;j++){
    var s = new State();
    s[0]=1;
    s[3]=1+j;
    np.addState(s);
}
cmotion.moveAlongPath(np);



var xmotor = motors[2];
for(var i=0;i<5;i++){
    xmotor.moveRelative(.1,1,1);
    xmotor.waitMove();
}
