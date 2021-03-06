clear;
time_position = importdata('uwb03-Unnamed__Time_Position.mat');
plot(time_position(:,2), time_position(:,3), '.');
i = length(time_position);
t_p_copy = [time_position zeros(length(time_position),1)];
% find the first non 0 position elements
for jj = 1:length(t_p_copy)
    if ~(t_p_copy(jj,2) == 0 && t_p_copy(jj,3) == 0 && t_p_copy(jj,4) == 0)
        last_t_p = t_p_copy(jj,:);
        disp(jj);
        break;
    end    
end 
for j = jj+1:length(t_p_copy)
    if ~(t_p_copy(j,2) == 0 && t_p_copy(j,3) == 0 && t_p_copy(j,4) == 0)
        disp(j);
        now_t_p = t_p_copy(j,:);
        diff_t_p = now_t_p - last_t_p;
        last_t_p = now_t_p;
        t_p_copy(j,2:4) = diff_t_p(2:4) / diff_t_p(1) /1000; %units: m/s
        t_p_copy(j, 5) = sqrt( sum( t_p_copy(j,2:4).^2 ) );
    end    
end 
%{
while i>0
    if t_p_copy(i,2) == 0 && t_p_copy(i,3) == 0 && t_p_copy(i,4) == 0
        t_p_copy(i,:) = [];
    end
    i = i -1;
end    

diff_t_p = diff(t_p_copy);
velocity = diff_t_p(:,2:4) ./ diff_t_p(:,1);
%}