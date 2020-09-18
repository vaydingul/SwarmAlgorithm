clear; clc; close all;
files = dir("drones");
k = 1;

for file = files'

    if (~file.isdir)
        fname = ['drones/' file.name];
        datas(:, :, k) = importDrones(fname);
        k = k + 1;
    end

end

sz = size(datas);
numberOfDrones = sz(3);
iter = sz(1);

a = figure('Visible', 'on');
hold on;

for k = 1:iter

    for m = 1:numberOfDrones
        plot(datas(k, 1, m), datas(k, 2, m), 'o');
    end

    
    axis equal

    drawnow;

    

end

hold off;


