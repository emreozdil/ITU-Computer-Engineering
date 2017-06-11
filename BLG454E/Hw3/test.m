%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% test all the perceptrons with the whole test data return the confusion
% matrix
%
function [weight, confusion] = test(testdata, weight)
    confusion = zeros(45,4);
    k = 1;
    for i = 1: 10
        for j = i+1: 10
            [weight, con] = testbi(i,j, testdata, weight);
            confusion(k,1) = con(1,1);
            confusion(k,2) = con(1,2);
            confusion(k,3) = con(2,1);
            confusion(k,4) = con(2,2);
            k = k + 1;
        end
    end
end