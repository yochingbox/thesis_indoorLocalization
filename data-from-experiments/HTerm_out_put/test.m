%% test for generate horizontal distances
time = data_t_dist_calied(:,1);
data_t_dist_calied_copy = data_t_dist_calied/100; %unit:m
dist = data_t_dist_calied_copy(:,2:end);
dist(dist<1.18) = 1.18; 
dist_horizontal = sqrt(dist.^2 - 1.18^2); %unit:m
t_dist_horizontal = [time dist_horizontal];

test1(dist_horizontal);

%% test for the node and tag position

function test1(Dist)
    positionOfNodes = [2938.41844377029,-3013.26989169788; [184.822603869210,-143.127276884650];...
        [4161.77182689655,2235.61214448276]; [-1396.30540772784,-2433.57009459426]; [-1741.84732630000,2032.12649985000]]'/1000;
    plot(positionOfNodes(1,:),positionOfNodes(2,:),'*'); 
    hold on;
    pause(2)
    for j = 1:size(Dist,1)
        for i = 1 : size(positionOfNodes, 2)
            h(i) = plotCircle(positionOfNodes(1, i), positionOfNodes(2, i), Dist(j,i));
        end   
        %axis square;  %axis tight;
        axis([-6 8 -6 6])
        pause(0.8)
        delete(h)
    end

end
function h_circle = plotCircle(x,y,r)
    if ~isnan(r)
        %ang=ang_start:0.01:ang_end;
        ang=0:0.01:2*pi;
        xp=r*cos(ang);
        yp=r*sin(ang);
        h_circle = plot(x+xp,y+yp);
    else
        h_circle = plot(0,0,'bo');
    end
end


%% test for  replace the NaN of the HTerm data with Gradual transition value
%{
HT_calied_copy = data_t_dist_calied;
flag2replaceNaN = 0;
for j = 1:size(HT_calied_copy,2)
    for i = 1:size(HT_calied_copy,1)-1
        if isnan(HT_calied_copy(i,j)) && ~isnan(HT_calied_copy(i-1,j))
            index_begin_NaN = i;
        end
        if isnan(HT_calied_copy(i,j)) && ~isnan(HT_calied_copy(i+1,j))
            index_end_NaN = i;
            flag2replaceNaN = 1;
        end
        if flag2replaceNaN == 1
            tmp = linspace(HT_calied_copy(index_begin_NaN-1,j), ...
                HT_calied_copy(index_end_NaN+1,j), index_end_NaN-index_begin_NaN+3);
            HT_calied_copy(index_begin_NaN:index_end_NaN, j) = tmp(2:end-1);
            flag2replaceNaN = 0;
        end
    end
end    
%}