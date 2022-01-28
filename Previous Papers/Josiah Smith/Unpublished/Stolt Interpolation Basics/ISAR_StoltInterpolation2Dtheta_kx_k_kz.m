function ISAR_StoltInterpolation2Dtheta_kx_k_kz(sxk,f,xStep,nSample,nFFTxk,nFFTz)
% 2D Stolt Interpolation from theta-kx and k-kZ
% f: 				Frequency Vector
% nHorMeasurement: 	# of Horizontal Measurements
% xStep:			Horizontal Step Size in m
% nSample: 			Number of Samples
% nFFTxk:			FFT size for x and k domains
% nFFTz:			FFT size for z domain
% Maintain sxk = s(x,k)
% size(sxk) == [nHorMeasurement,nSample]

%% Zeropad sxk
sxkPadded = sxk;
if (nFFTxk > size(sxk,1))
    sxkPadded = padarray(sxkPadded,[floor((nFFTxk-size(sxk,1))/2) 0],0,'pre');
    sxkPadded = padarray(sxkPadded,[ceil((nFFTxk-size(sxk,1))/2) 0],0,'post');
else
    nFFTxk = size(sxk,1);
end
%% Obtain SkXk
SkXk = fftshift(fft(conj(sxkPadded),nFFTxk,1),1);

%% Define Some Parameters
c = 299792458; % m/s
k = reshape(2*pi*f/c,1,[]); % Wavenumber Vector

kSx = 2*pi/(xStep);
kX = reshape(linspace(-kSx/2,kSx/2,nFFTxk),[],1);

% Consider only visible spectrum of kZ
kZU = reshape(linspace(0,2*max(k),nFFTz),1,[]);

KU = 1/2 * sqrt(kX.^2 + kZU.^2);

%% Interpolate (kX,k) -> (kX,kZ)
SkXkZ = zeros(size(KU));
for ii = 1:size(KU,1) % Replace with parfor to increase speed
    SkXkZ(ii,:) = interp1(k(:),SkXk(ii,:),KU(ii,:),"v5cubic");
end
% Works with: linear,nearest,next,previous,v5cubic
SkXkZ(isnan(SkXkZ)) = 0;

%% Recovered Reflectivity Function
pxz = ifft2(SkXkZ,nFFTxk,nFFTz);