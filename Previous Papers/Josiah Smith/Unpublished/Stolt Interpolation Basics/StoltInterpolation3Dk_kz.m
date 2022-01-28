function StoltInterpolation3Dk_kz(syxk,f,xStep,yStep,nSample,nFFTyxk,nFFTz)
% 3D Stolt Interpolation from k-kZ
% f: 				Frequency Vector
% nHorMeasurement: 	# of Horizontal Measurements
% nVerMeasurement: 	# of Vertical Measurements
% xStep:			Horizontal Step Size in m
% yStep:			Vertical Step Size in m
% nSample: 			Number of Samples
% nFFTyxk:			FFT size for x and k domains
% nFFTz:			FFT size for z domain
% Maintain syxk = s(x,k)
% size(syxk) == [nVerMeasurement,nHorMeasurement,nSample]

%% Zeropad syxk
syxkPadded = syxk;
if (nFFTyxk > size(syxk,1))
    syxkPadded = padarray(syxkPadded,[floor((nFFTyxk-size(syxk,1))/2) 0],0,'pre');
    syxkPadded = padarray(syxkPadded,[ceil((nFFTyxk-size(syxk,1))/2) 0],0,'post');
else
    nFFTyxk = size(syxk,1);
end
if (nFFTyxk > size(syxk,2))
    syxkPadded = padarray(syxkPadded,[0 floor((nFFTyxk-size(syxk,2))/2)],0,'pre');
    syxkPadded = padarray(syxkPadded,[0 ceil((nFFTyxk-size(syxk,2))/2)],0,'post');
else
    nFFTyxk = size(syxk,2);
end

%% Obtain SkYkXk
SkYkXk = fftshift(fftshift(fft(fft(conj(syxkPadded),nFFTyxk,1),nFFTyxk,2),1),2);

%% Define Some Parameters
c = 299792458; % m/s
k = reshape(2*pi*f/c,1,1,[]); % Wavenumber Vector

kSx = 2*pi/(xStep);
kX = reshape(linspace(-kSx/2,kSx/2,nFFTyxk),1,[]);

kSy = 2*pi/(yStep);
kY = reshape(linspace(-kSy/2,kSy/2,nFFTyxk),[],1);

% Consider only visible spectrum of kZ
kZU = reshape(linspace(0,2*max(k),nFFTz),1,1,[]);

KU = 1/2 * sqrt(kY.^2 + kX.^2 + kZU.^2);

%% Interpolate (kY,kX,k) -> (kY,kX,kZ)
SkYkXkZ = zeros(size(KU));
sizeKU2 = size(KU,2); % Necessary for parfor
for ii = 1:size(KU,1) % Replace with parfor to increase speed
    for jj = 1:sizeKU2
        SkYkXkZ(ii,jj,:) = interp1(k(:),squeeze(SkYkXk(ii,jj,:)),squeeze(KU(ii,jj,:)),"v5cubic");
    end
end
% Works with: linear,nearest,next,previous,v5cubic
SkYkXkZ(isnan(SkYkXkZ)) = 0;

%% Recovered Reflectivity Function
pyxz = ifftshift(ifftn(SkYkXkZ,[nFFTyxk,nFFTyxk,nFFTz]),1);
% I am not entirely sure why I have to do an ifftshift across the first dimension here