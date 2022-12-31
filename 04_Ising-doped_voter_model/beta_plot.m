% parameters
size = 8;
P = '00';
P_num = 0.0;
sum = 1;
s = 1;
k = 6;
beta = 0.01:0.01:3.00;
f_sum = zeros(1,300);
ff = zeros(6,300);
fr = zeros(6,300);

% creating file name
fname = strcat('Beta_plot_',int2str(size),'x',int2str(size),'_P',P,'.txt');

% read data from file
file = fopen(fname,'r');
F = fscanf(file,'%f\n');
fclose(file);

for i = 1:k
    ff(i,:) = F(sum:(sum + 299));
    sum = sum + 300;
    fr(i,:) = F(sum:(sum + 299));
    sum = sum + 300;
    plot(beta,fr(i,:));
    hold on;

    for j = 1:(i-1)
        f_sum = f_sum +(fr(j,:) - fr(i,:)).^2;
    end
end

[M,I] = min(f_sum);
I = I*0.01;
disp(I);

if k == 3
    legend('n = 400 forw','n = 400 rev','n = 600 forw','n = 600 rev','n = 800 forw','n = 800 rev')
elseif k == 6
    legend('n = 5 rev','n = 10 rev','n = 20 rev','n = 50 rev','n = 100 rev','n = 200 rev')
elseif k == 9
    legend('n = 50 forw','n = 50 rev','n = 100 forw','n = 100 rev','n = 200 forw','n = 200 rev','n = 400 forw','n = 400 rev','n = 600 forw','n = 600 rev','n = 800 forw','n = 800 rev')
end
axis([0.0 3.0 -60.0 60.0])
xlabel('\beta')
ylabel('\DeltaF^J')