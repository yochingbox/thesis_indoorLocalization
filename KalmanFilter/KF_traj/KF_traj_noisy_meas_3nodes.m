%% nodes position 
% [4 3
%  1 2]
%%
clear all;
close all;
format longG
%% import measuremnets data from recording
measurements_data_noisy = importdata('..\..\trajectory\goodTraj01\noisy_measuremnts_data.mat'); % load noisy_measurements
%measurements_data_noisy = importdata('..\..\trajectory\goodTraj01\distances2all_abs_without_noise.mat'); % load measurements without noise

% for small test, use a series measurements data generate when Tag stays at origin all the time
measurements_data_noisy = repmat([sqrt(50^2 + 50^2); sqrt(100^2 + 50^2); sqrt(100^2 + 100^2); sqrt(50^2 + 100^2)], 1, size(measurements_data_noisy, 2));  

positionOfNodes = [-50 -50; 100 -50; 100 100; -50 100]'; % <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
%% initiation
x_0 = [0 0 1.0 1.0]';
P_0 = eye(4, 4); % TODO, make eye(), & choose to be all one, a litle too big, but it should converge at the end if the KF work 
% sampling time interval
dt = 2/3;
% state transition model matrix A
A = [1 0 dt 0; 0 1 0 dt; 0 0 1 0; 0 0 0 1];
% control-input model matrix B, control-input is zero
B = ones(4, 4);
u = zeros(4, 1);

% H matrix
syms N_xy x_m Z_e
numNodes = 3; % <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
N_x_n = sym('N_x_n%d%d', [2 numNodes]); % posNodes %[n_x1 n_x2 n_x3; n_y1 n_y2 n_y3]. i.e. 'N_x_n21' means the y_posi of the ist node 
x_m = sym('x_m%d', [4 1]); % time_updated state vector
Z_e = [     % Z_e: expected measurements [numNodes 1]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
       sqrt( (N_x_n(1,1) - x_m(1))^2 + (N_x_n(2,1) - x_m(2))^2 );
       sqrt( (N_x_n(1,2) - x_m(1))^2 + (N_x_n(2,2) - x_m(2))^2 );
       sqrt( (N_x_n(1,3) - x_m(1))^2 + (N_x_n(2,3) - x_m(2))^2 )
       ];
H_symbolic = jacobian(Z_e, x_m);

% process noise covariance Q 
G = [dt^2/2*eye(2);dt*eye(2)];
sigma = 0.1;
%RandnForGenTracj = randn(2, 1); % TODO: an besten, the randn(2, 1) should be the same as the one generated the traj
%Q = G * (sigma * diag(RandnForGenTracj))^2 * G'; %since displacement cause by acceleration is G * sigma * randn(2,1) {acceleration is  sigma * randn(2,1)}
Q = G * sigma^2 * G';
% measurement noise covariance R
R = 0.01 * eye(3); % shoule be relative to the value of 'noiseLevelForMeasurements.mat' in folder 'goodTraj01'
% TODO, correct Q & R, they are square matrices
%% Kalman Filter
 % notation symbols please check Page 30 in 'An Intro to the Kalman Filter, G. Welch G. Bishop' 
X = zeros(4, size(measurements_data_noisy,2)); % state matrix
P = zeros(4, 4, size(measurements_data_noisy,2)); % state covariance matrix
K = zeros(4, 3, size(measurements_data_noisy,2)); % Kalman Gain matrix
X(:, 1) = x_0;
P(:, :, 1) = P_0;
% take only 3 out of 4 sets measurements, for KF here. TODO later do 4 sets
z = measurements_data_noisy(1:3,:);
% for loop, and plot position on map
for i = 2:size(measurements_data_noisy,2)
    % time update
    x_minus= A * X(:, i - 1) + B * u; % TODO, think about if the accelerations should be included into state vectors
    P_minus = vpa(A * P(:, :, i-1) * A' + Q); 
    % measurement update
        % Never use the inverse of a matrix to solve a linear system Ax=b with 
        % x=inv(A)*b, because it is slow and inaccurate.
        % Replace inv(A)*b with A\b, Replace b*inv(A) with b/A, replace A*inv(B)*C with A*(B\C).
        % HERE replace K = P_minus * H' * invs(H * P_minus * H' +R) with P_minus * H' / (H * P_minus * H' +R)    
    %try a very naiiv way to calculate the H, should be improved
    %definitely. TODO
%     z_expected = [
%                     sqrt( (positionOfNodes(1,1) - x_minus(1))^2 + (positionOfNodes(2,1) - x_minus(2))^2 );
%                     sqrt( (positionOfNodes(1,2) - x_minus(1))^2 + (positionOfNodes(2,2) - x_minus(2))^2 );
%                     sqrt( (positionOfNodes(1,3) - x_minus(1))^2 + (positionOfNodes(2,3) - x_minus(2))^2 )
%                  ];
%     H = vpa(z_expected/x_minus);
    H = vpa(eval(subs( subs(H_symbolic, x_m, x_minus), N_x_n, positionOfNodes(:,1:3))));
    K_k = P_minus * H' / (H * P_minus * H' +R);
    X(:, i) = x_minus + K_k * (z(:, i) - H * x_minus);
    P(:, :, i) = vpa((eye(length(x_0)) - K_k * H) * P_minus);
    K(:, :, i) = K_k; 
end

plot(X(1,:), X(2,:), '-o');