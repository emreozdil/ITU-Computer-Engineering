%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% x is 65 elements long, x(1..64) is the data, x(65) is the result
%
function weight = updateWeight(d1, d2, x, weight)
    if (x(65) == d1)
        t = 1;
    elseif (x(65) == d2)
        t = -1;
    else
        t = 0;
    end
    w = weight(d1,d2, :);
    output = calcOutput(w,x);
    o = signOf(output);
    rate = 0.5;
    coe = rate * (t-o);
    
    % updating the weight
    w(1) = w(1) + coe;
    
    for i = 1:64
       w(i+1) = w(i+1) + coe*x(i);
    end
    weight(d1,d2,:) = w;
end