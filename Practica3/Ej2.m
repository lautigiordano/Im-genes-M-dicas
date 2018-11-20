theta = 0:5:359; R = 2;
%Ej a. 
%Perdon por esto, seguro con un for el programa se acorta un 66% :p
N=64; p=2*N;
    [A1p, b1p, x1p] = paralleltomo(N,theta,p);
    [A1f, b1f, x1f] = fanbeamtomo(N,theta,p,R);

    it = 10;
        Kp10 = kaczmarz(A1p, b1p, 1:it);
        Kf10 = kaczmarz(A1f, b1f, 1:it);
        Cp10 = cimmino(A1p, b1p, 1:it);
        Cf10 = cimmino(A1f, b1f, 1:it);

        figKp10 = Kp10;
        imwrite(reshape(figKp10(:,end),N,N),'Kp10N64.pgm');
        figKf10 = Kf10;
        imwrite(reshape(figKf10(:,end),N,N),'Kf10N64.pgm');
        figCp10 = Cp10;
        imwrite(reshape(figCp10(:,end),N,N),'Cp10N64.pgm');
        figCf10 = Cf10;
        imwrite(reshape(figCf10(:,end),N,N),'Cf10N64.pgm');

    it = 100;
        Kp100 = kaczmarz(A1p, b1p, 1:it);
        Kf100 = kaczmarz(A1f, b1f, 1:it);
        Cp100 = cimmino(A1p, b1p, 1:it);
        Cf100 = cimmino(A1f, b1f, 1:it);

        figKp100 = Kp100;
        imwrite(reshape(figKp100(:,end),N,N),'Kp100N64.pgm');
        figKf100 = Kf100;
        imwrite(reshape(figKf100(:,end),N,N),'Kf100N64.pgm');
        figCp100 = Cp100;
        imwrite(reshape(figCp100(:,end),N,N),'Cp100N64.pgm');
        figCf100 = Cf100;
        imwrite(reshape(figCf100(:,end),N,N),'Cf100N64.pgm');


N=128; p=2*N;
    [A2p, b2p, x2p] = paralleltomo(N,theta,p);
    [A2f, b2f, x2f] = fanbeamtomo(N,theta,p,R);

    it = 10;
        Kp10 = kaczmarz(A2p, b2p, 1:it);
        Kf10 = kaczmarz(A2f, b2f, 1:it);
        Cp10 = cimmino(A2p, b2p, 1:it);
        Cf10 = cimmino(A2f, b2f, 1:it);

        figKp10 = Kp10;
        imwrite(reshape(figKp10(:,end),N,N),'Kp10N128.pgm');
        figKf10 = Kf10;
        imwrite(reshape(figKf10(:,end),N,N),'Kf10N128.pgm');
        figCp10 = Cp10;
        imwrite(reshape(figCp10(:,end),N,N),'Cp10N128.pgm');
        figCf10 = Cf10;
        imwrite(reshape(figCf10(:,end),N,N),'Cf10N128.pgm');

    it = 100;
        Kp100 = kaczmarz(A2p, b2p, 1:it);
        Kf100 = kaczmarz(A2f, b2f, 1:it);
        Cp100 = cimmino(A2p, b2p, 1:it);
        Cf100 = cimmino(A2f, b2f, 1:it);

        figKp100 = Kp100;
        imwrite(reshape(figKp100(:,end),N,N),'Kp100N128.pgm');
        figKf100 = Kf100;
        imwrite(reshape(figKf100(:,end),N,N),'Kf100N128.pgm');
        figCp100 = Cp100;
        imwrite(reshape(figCp100(:,end),N,N),'Cp100N128.pgm');
        figCf100 = Cf100;
        imwrite(reshape(figCf100(:,end),N,N),'Cf100N128.pgm');


N=256; P=2*N;
    [A3p, b3p, x3p] = paralleltomo(N,theta,p);
    [A3f, b3f, x3f] = fanbeamtomo(N,theta,p,R);

    it = 10;
        Kp10 = kaczmarz(A3p, b3p, 1:it);
        Kf10 = kaczmarz(A3f, b3f, 1:it);
        Cp10 = cimmino(A3p, b3p, 1:it);
        Cf10 = cimmino(A3f, b3f, 1:it);

        figKp10 = Kp10;
        imwrite(reshape(figKp10(:,end),N,N),'Kp10N256.pgm');
        figKf10 = Kf10;
        imwrite(reshape(figKf10(:,end),N,N),'Kf10N256.pgm');
        figCp10 = Cp10;
        imwrite(reshape(figCp10(:,end),N,N),'Cp10N256.pgm');
        figCf10 = Cf10;
        imwrite(reshape(figCf10(:,end),N,N),'Cf10N256.pgm');

    it = 100;
        Kp100 = kaczmarz(A3p, b3p, 1:it);
        Kf100 = kaczmarz(A3f, b3f, 1:it);
        Cp100 = cimmino(A3p, b3p, 1:it);
        Cf100 = cimmino(A3f, b3f, 1:it);

        figKp100 = Kp100;
        imwrite(reshape(figKp100(:,end),N,N),'Kp100N256.pgm');
        figKf100 = Kf100;
        imwrite(reshape(figKf100(:,end),N,N),'Kf100N256.pgm');
        figCp100 = Cp100;
        imwrite(reshape(figCp100(:,end),N,N),'Cp100N256.pgm');
        figCf100 = Cf100;
        imwrite(reshape(figCf100(:,end),N,N),'Cf100N256.pgm');

% Ej b.
eta = 0.05; %Relative noise.
N=100; P=2*N;
    [Ap, bp, xp] = paralleltomo(N,theta,p);
    [Af, bf, xf] = fanbeamtomo(N,theta,p,R);
    
% Noise level.
deltap = eta*norm(bp);
deltaf = eta*norm(bf);

% Add noise to the rhs.
randn('state',0);
ep = randn(size(bp));
ep = deltap*ep/norm(ep);
bpnoise = bp + ep;

ef = randn(size(bf));
ef = deltap*ef/norm(ef);
bfnoise = bf + ef;

it=1;
    Kp1noise = kaczmarz(Ap,bpnoise,1:it);
    Kf1noise = kaczmarz(Af,bfnoise,1:it);
    Cp1noise = cimmino(Ap,bpnoise,1:it);
    Cf1noise = cimmino(Af,bfnoise,1:it);
    
    figKp1noise = Kp1noise;
    figKf1noise = Kf1noise;
    figCp1noise = Cp1noise;
    figCf1noise = Cf1noise;

    imwrite(reshape(figKp1noise(:,end),N,N),'Kp1noise.pgm');
    imwrite(reshape(figKf1noise(:,end),N,N),'Kf1noise.pgm');
    imwrite(reshape(figCp1noise(:,end),N,N),'Cp1noise.pgm');
    imwrite(reshape(figCf1noise(:,end),N,N),'Cf1noise.pgm');
    
it=10;
    Kp10noise = kaczmarz(Ap,bpnoise,1:it);
    Kf10noise = kaczmarz(Af,bfnoise,1:it);
    Cp10noise = cimmino(Ap,bpnoise,1:it);
    Cf10noise = cimmino(Af,bfnoise,1:it);
    
    figKp10noise = Kp10noise;
    figKf10noise = Kf10noise;
    figCp10noise = Cp10noise;
    figCf10noise = Cf10noise;

    imwrite(reshape(figKp10noise(:,end),N,N),'Kp10noise.pgm');
    imwrite(reshape(figKf10noise(:,end),N,N),'Kf10noise.pgm');
    imwrite(reshape(figCp10noise(:,end),N,N),'Cp10noise.pgm');
    imwrite(reshape(figCf10noise(:,end),N,N),'Cf10noise.pgm');
    
it=50;
    Kp50noise = kaczmarz(Ap,bpnoise,1:it);
    Kf50noise = kaczmarz(Af,bfnoise,1:it);
    Cp50noise = cimmino(Ap,bpnoise,1:it);
    Cf50noise = cimmino(Af,bfnoise,1:it);
    
    figKp50noise = Kp50noise;
    figKf50noise = Kf50noise;
    figCp50noise = Cp50noise;
    figCf50noise = Cf50noise;

    imwrite(reshape(figKp50noise(:,end),N,N),'Kp50noise.pgm');
    imwrite(reshape(figKf50noise(:,end),N,N),'Kf50noise.pgm');
    imwrite(reshape(figCp50noise(:,end),N,N),'Cp50noise.pgm');
    imwrite(reshape(figCf50noise(:,end),N,N),'Cf50noise.pgm');
    
it=100;
    Kp100noise = kaczmarz(Ap,bpnoise,1:it);
    Kf100noise = kaczmarz(Af,bfnoise,1:it);
    Cp100noise = cimmino(Ap,bpnoise,1:it);
    Cf100noise = cimmino(Af,bfnoise,1:it);
    
    figKp100noise = Kp100noise;
    figKf100noise = Kf100noise;
    figCp100noise = Cp100noise;
    figCf100noise = Cf100noise;

    imwrite(reshape(figKp100noise(:,end),N,N),'Kp100noise.pgm');
    imwrite(reshape(figKf100noise(:,end),N,N),'Kf100noise.pgm');
    imwrite(reshape(figCp100noise(:,end),N,N),'Cp100noise.pgm');
    imwrite(reshape(figCf100noise(:,end),N,N),'Cf100noise.pgm');
    
it=500;
    Kp500noise = kaczmarz(Ap,bpnoise,1:it);
    Kf500noise = kaczmarz(Af,bfnoise,1:it);
    Cp500noise = cimmino(Ap,bpnoise,1:it);
    Cf500noise = cimmino(Af,bfnoise,1:it);
    
    figKp500noise = Kp500noise;
    figKf500noise = Kf500noise;
    figCp500noise = Cp500noise;
    figCf500noise = Cf500noise;

    imwrite(reshape(figKp500noise(:,end),N,N),'Kp500noise.pgm');
    imwrite(reshape(figKf500noise(:,end),N,N),'Kf500noise.pgm');
    imwrite(reshape(figCp500noise(:,end),N,N),'Cp500noise.pgm');
    imwrite(reshape(figCf500noise(:,end),N,N),'Cf500noise.pgm');
