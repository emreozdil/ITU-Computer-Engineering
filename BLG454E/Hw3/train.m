%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% train all the perceptrons with the whole trainning data return the epochs
% used
%
function [weight, epoch] = train(traindata, weight)
    epoch = zeros(10, 10);
    for i = 1:10
        for j = (i+1):10
            [weight, epoch(i,j)] = trainbi(i, j, traindata, weight);
            
        end
    end
end

