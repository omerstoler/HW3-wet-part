
%% Definitions

set(0,'DefaultAxesColor','White');
set(0,'DefaultTextColor','Black');
set(0,'DefaultAxesFontName','Cambria Math');
set(0,'DefaultAxesFontSize',12);
set(0,'DefaultFigureColor','White');
set(0,'DefaultAxesXGrid','on','DefaultAxesYGrid','on');
close all;clc;clear all;


%% Part 3.1
N = 1:200;
A0 = 1;
LatencyA = 1./N ;
Q3F1 = figure;
plot(N,LatencyA);
title("Optimal speedup using N threads - LatencyA(N)");
legend("Latency[A](N)");
xlabel("N");
ylabel("$\frac{Latency(A)}{Latency(A_0)}$",'Interpreter','latex','FontSize',20);
saveas(Q3F1,'Q3F1.png');
%% Part 3.2
Q3F2 = figure;
s = [0 0.25 0.5 0.75 1];
LatencyA = ((1-s')./N+s');

plot(N,LatencyA);
title("Optimal speedup using N threads - LatencyA(N)");
legend("s = 0","s = 0.25","s = 0.5","s = 0.75","s = 1");
xlabel("N");
ylabel("$\frac{Latency(A)}{Latency(A_0)}$",'Interpreter','latex','FontSize',20);
ylim([-0.1 1.1]);
saveas(Q3F2,'Q3F2.png');