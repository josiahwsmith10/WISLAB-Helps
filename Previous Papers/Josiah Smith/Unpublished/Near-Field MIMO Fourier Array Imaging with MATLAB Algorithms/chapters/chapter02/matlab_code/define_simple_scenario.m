%% Define a simple scenario
xyzT = [0,0,0]*1e-3;
xyzR = [4,0,0]*1e-3;
xyz0 = [0,0,0.5];

RT = pdist2(xyzT,xyz0);
RR = pdist2(xyzR,xyz0);