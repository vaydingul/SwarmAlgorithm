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
v = VideoWriter('newfile','MPEG-4');
v.Quality = 50;
open(v)
a = figure('Visible', 'off');
hold on;

for k = 1:iter

    for m = 1:numberOfDrones
        plot(datas(k, 1, m), datas(k, 2, m), 'o');
    end

    frame = getframe(gcf);
    writeVideo(v,frame);
    axis equal

    drawnow;

    

end

hold off;

close(v)

