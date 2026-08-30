% parameters
num_of_hist = 1;
T_star = 8;
num_of_col = 10;
num_of_rows = num_of_col;

% read file
fname = strcat('hist',num2str(num_of_hist),'_',num2str(T_star),'_',num2str(num_of_col),'_',num2str(num_of_rows),'.txt');
fileID = fopen(fname, 'r');
formatSpec = '%f';
vx = fscanf(fileID, formatSpec, [num_of_rows num_of_col]);
vx = vx';
vy = fscanf(fileID, formatSpec, [num_of_rows num_of_col]);
vy = vy';
U = fscanf(fileID, formatSpec, [num_of_rows num_of_col]);
U = U';
n = fscanf(fileID, formatSpec, [num_of_rows num_of_col]);
n = n';
fclose(fileID);

% data analysis
bin_width = 100 / num_of_col;
pos1 = -50 + (bin_width)/2;
pos2 = 50 - (bin_width)/2;
[X,Y] = meshgrid(pos1:bin_width:pos2,pos2:-bin_width:pos1);
figure
quiver(X,Y,vx,vy,0)
axis equal
%figure
%heatmap(U)


