% MATLAB Code for Performance Analysis of Reliable UDP Protocol

clc;
clear;
close all;

% Packet Numbers
packet_no = 1:10;

% Sample Delay Values (seconds)
delay = [0.12 0.15 0.14 0.13 0.30 0.16 0.15 0.28 0.17 0.16];

% Retransmission Count
retransmissions = [0 0 0 0 1 0 0 1 0 0];

% Delay Analysis
figure;
plot(packet_no, delay,'-o','LineWidth',2);
grid on;
xlabel('Packet Number');
ylabel('Delay (s)');
title('Packet Delay Analysis');

% Retransmission Analysis
figure;
bar(packet_no,retransmissions);
grid on;
xlabel('Packet Number');
ylabel('Retransmissions');
title('Retransmission Analysis');

% Packet Delivery Ratio
total_packets = 10;
successful_packets = 10;
PDR = (successful_packets/total_packets)*100;

fprintf('Packet Delivery Ratio = %.2f%%\n',PDR);
