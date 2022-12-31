% parameters
number_of_bins = [400 800 1600 4000 8000 16000]';
n = [5 10 20 50 100 200]';
size = 64;
P = '07';
P_num = 0.7;
beta = 1.0;
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

for i = 1:6
    
    % update index variable
    sum2 = sum2 + number_of_bins(i);
    
    % forward histogram
    x = X(sum3:(sum3+number_of_bins(i)-1));
    yf = Y(sum1:sum2);
    
    % update index variable
    sum1 = sum1 + number_of_bins(i);
    sum2 = sum2 + number_of_bins(i);
    sum3 = sum3 + number_of_bins(i);

    % reverse histogram
    yr = Y(sum1:sum2);
    
    % plot
    plot(x,yf,x,yr,'--');
    hold on;
    
    % update index variable
    sum1 = sum1 + number_of_bins(i);
end

title_text = strcat('L = ',int2str(size), ', R = ', int2str(size), ', P = ', num2str(P_num), ', \beta = ', num2str(beta));
title(title_text);
xlabel('A');
ylabel('P(A)');
legend('n = 5 forw','n = 5 rev','n = 10 forw','n = 10 rev','n = 20 forw','n = 20 rev','n = 50 forw','n = 50 rev','n = 100 forw','n = 100 rev','n = 200 forw','n = 200 rev')



