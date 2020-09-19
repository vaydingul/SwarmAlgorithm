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

for k = 1:iter

    for m = 1:numberOfDrones
        plot(datas(k, 1, m), datas(k, 2, m), 'o-');
    end

    
    axis equal
    set(gca, 'xlim', [-3 3]);

    set(gca, 'ylim', [-3 3]);
    drawnow;

    if(mod(k,10) == 0)
     %   cla;
    end
end

hold off;


