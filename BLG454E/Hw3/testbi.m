%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% test one perceptron(d1,d2) on the test data set, and return the confusion
% matrix.
%
function [weight, con] = testbi(d1, d2, testdata, weight)
    con = zeros(2,2);
    for i = 1:size(testdata,1)
        if (testdata(i, 65) == d1)
            
            o = calcOutput(weight(d1,d2, :), testdata(i, :));
            if (sign(o) == 1)
                con(1,1) = con(1,1) + 1;
            else
                con(1,2) = con(1,2) + 1;
            end
        elseif (testdata(i, 65) == d2)
            o = calcOutput(weight(d1,d2, :), testdata(i, :));
            if (sign(o) == 1)
                con(2,1) = con(2,1) + 1;
            else
                con(2,2) = con(2,2) + 1;
            end
        end
    end 
end