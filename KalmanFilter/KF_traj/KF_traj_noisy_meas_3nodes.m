%% nodes position 
% [4 3
%  1 2]
%%
% clear all;
% close all;
%% import measuremnets data from recording
%measurements_data_noisy = importdata('..\..\trajectory\goodTraj01\noisy_measuremnts_data.mat'); % load noisy_measurements
measurements_data_noisy = importdata('..\..\trajectory\goodTraj01\distances2all_abs_without_noise.mat'); % load measurements without noise
positionOfNodes = [-50 -50; 100 -50; 100 100; -50 100]'; % <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
%% initiation
x_0 = [0 0 1 1]';
P_0 = ones(4, 4); % TODO, make eye(), & choose to be all one, a litle too big, but it should converge at the end if the KF work 
% sampling time interval
dt = 2/3;
% state transition model matrix A
A = [1 0 dt 0; 0 1 0 dt; 0 0 1 0; 0 0 0 1];
% control-input model matrix B, control-input is zero
B = ones(4, 4);
u = zeros(4, 1);
% H = ; %TODO H matrix
% process noise covariance Q 
G = [dt^2/2*eye(2);dt*eye(2)];
sigma = 0.1;
RandnForGenTracj = randn(2, 1); % TODO: an besten, the randn(2, 1) should be the same as the one generated the traj
Q = G * (sigma * diag(RandnForGenTracj))^2 * G'; %since displacement cause by acceleration is G * sigma * randn(2,1) {acceleration is  sigma * randn(2,1)}
% measurement noise covariance R
R = 1.0 * eye(3); % shoule be relative to the value of 'noiseLevelForMeasurements.mat' in folder 'goodTraj01'
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
    P_minus = A * P(:, :, i-1) * A' + Q; 
    % measurement update
        % Never use the inverse of a matrix to solve a linear system Ax=b with 
        % x=inv(A)*b, because it is slow and inaccurate.
        % Replace inv(A)*b with A\b, Replace b*inv(A) with b/A, replace A*inv(B)*C with A*(B\C).
        % HERE replace K = P_minus * H' * invs(H * P_minus * H' +R) with P_minus * H' / (H * P_minus * H' +R)    
    %try a very naiiv way to calculate the H, should be improved
    %definitely. TODO
    z_expected = [
                    sqrt( (positionOfNodes(1,1) - x_minus(1))^2 + (positionOfNodes(2,1) - x_minus(2))^2 );
                    sqrt( (positionOfNodes(1,2) - x_minus(1))^2 + (positionOfNodes(2,2) - x_minus(2))^2 );
                    sqrt( (positionOfNodes(1,3) - x_minus(1))^2 + (positionOfNodes(2,3) - x_minus(2))^2 )
                 ];
    H = z_expected/x_minus;
    K_k = P_minus * H' / (H * P_minus * H' +R);
    X(:, i) = x_minus + K_k * (z(:, i) - H * x_minus);
    P(:, :, i) = (eye(length(x_0)) - K_k * H) * P_minus;
    K(:, :, i) = K_k;
    
end