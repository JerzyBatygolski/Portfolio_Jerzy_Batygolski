% parameters
number_of_bins = 1000;
n = 200;
size = 8;
P = '07';
P_num = 0.7;
T = [1.4 1.6 1.8 2.0 2.2]';
sum1 = 1;
sum2 = 0;
sum3 = 1;

% creating file names
fname_end = strcat(int2str(size),'x',int2str(size),'_P',P,'.txt');
fname1 = strcat('Hist_x_', fname_end);
fname2 = strcat('Hist_y_', fname_end);
    
% read data from file
hist_x = fopen(fname1,'r');
X = fscanf(hist_x,'%f\n');
fclose(hist_x);
    
hist_y = fopen(fname2,'r');
Y = fscanf(hist_y,'%f\n');
fclose(hist_y);

for i = 1:5
    
    % update index variable
    sum2 = sum2 + number_of_bins;
    
    % forward histogram
    x = X(sum3:(sum3+number_of_bins-1));
    yf = Y(sum1:sum2);
    
    % update index variable
    sum1 = sum1 + number_of_bins;
    sum2 = sum2 + number_of_bins;
    sum3 = sum3 + number_of_bins;

    % reverse histogram
    yr = Y(sum1:sum2);
    
    % plot
    plot(x,yf,x,yr,'--');
    hold on;
    
    % update index variable
    sum1 = sum1 + number_of_bins;
end

title_text = strcat('L = ',int2str(size), ', P = ', num2str(P_num),', n = ', num2str(n));
title(title_text);
xlabel('A');
ylabel('P(A)');
legend('T = 1.4 forw','T = 1.4 rev','T = 1.6 forw','T = 1.6 rev','T = 1.8 forw','T = 1.8 rev','T = 2.0 forw','T = 2.0 rev','T = 2.2 forw','T = 2.2 rev')



