%% Show range profile
range_data = fft(sk);
R_max = fS*c/(2*K);
range_axis = (0:N-1)/N*R_max;

figure; 
plot(range_axis,db(abs(range_data)));
title("Range Profile")
xlabel("Range (m)")
ylabel("Intensity (dB)")