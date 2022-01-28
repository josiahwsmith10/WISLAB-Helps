%% Define the FMCW radar chirp parameters
f0 = 77e9;
K = 100.036e12;
fS = 2000e3;
N = 79;

c = 299792458;

k = 2*pi/c * (f0 + K/fS*(0:N-1));

%% Define a simple scenario
xyzT = [0,0,0]*1e-3;
xyzR = [4,0,0]*1e-3;
xyz0 = [0,0,0.5];

RT = pdist2(xyzT,xyz0);
RR = pdist2(xyzR,xyz0);

%% Simulate the echo signal for the simple scenario
sigma = 1;

sk = sigma/(RT*RR) * exp(1j*k*(RT + RR));

%% Show range profile
range_data = fft(sk);
R_max = fS*c/(2*K);
range_axis = (0:N-1)/N*R_max;

figure; 
plot(range_axis,db(abs(range_data)));
title("Range Profile")
xlabel("Range (m)")
ylabel("Intensity (dB)")