% Fetch drone .csv files in the directory of ´drones´
files = dir("drones");
k = 1;


% Read all the data belongs to the drones
for file = files'

    if (~file.isdir)
        fname = ['drones/' file.name];
        datas(:, :, k) = importDrones(fname);
        k = k + 1;
    end

end

sz = size(datas);
% Number of iteration to visualize
iter = sz(1);

if (length(sz) ~= 2)
    numberOfDrones = sz(3);
else
    numberOfDrones = 1;
end

a = figure('Visible', 'on');
hold on;
i = 0;

% Simple animation routine
for k = 1:100:iter

    for m = 1:numberOfDrones
        plot(datas(k, 1, m), datas(k, 2, m), 'o-', 'MarkerSize', 6);
    end

    axis equal;
    set(gca, 'xlim', [-10 30]);
    set(gca, 'ylim', [-10 30]);
    drawnow;
    i = i + 1;

    if (mod(i, 2) == 0)
        cla;
        i = 1;
    end

end

hold off;
