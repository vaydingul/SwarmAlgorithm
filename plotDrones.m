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
iter = sz(1);

if (length(sz) ~= 2)
    numberOfDrones = sz(3);
else
    numberOfDrones = 1;
end

a = figure('Visible', 'on');
hold on;
i = 0;

for k = 1:10:iter

    for m = 1:numberOfDrones
        plot(datas(k, 1, m), datas(k, 2, m), 'o-', 'MarkerSize', 6);
    end

    axis equal;
    set(gca, 'xlim', [-10 10]);
    set(gca, 'ylim', [0 30]);
    drawnow;
    i = i + 1;

    if (mod(i, 10) == 0)
        cla;
        i = 1;
    end

end

hold off;
