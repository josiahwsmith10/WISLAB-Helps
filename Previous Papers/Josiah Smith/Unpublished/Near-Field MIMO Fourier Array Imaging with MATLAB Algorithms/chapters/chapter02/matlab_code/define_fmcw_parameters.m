%% Define the FMCW radar chirp parameters
f0 = 77e9;
K = 100.036e12;
fS = 2000e3;
N = 79;

c = 299792458;

k = 2*pi/c * (f0 + K/fS*(0:N-1));