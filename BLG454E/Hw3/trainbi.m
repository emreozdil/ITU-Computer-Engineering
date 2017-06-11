%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% train a single perceptron d1 vs d2, where output 1 mean d1, -1 mean d2
% return the epoch used
%
function [weight, epoch] = trainbi(d1, d2, traindata, weight)
    
    for i = 1:65
        % randomly set the weight between -1 and 1
        weight(d1, d2, i) = rand*2 - 1;
        % fprintf('%g\n', weight(d1, d2, i));
    end
    
    epoch = 0;
    while 1
        [weight, con] = testbi(d1, d2, traindata, weight);
        oldacc = (con(1,1) + con(2,2)) / (con(1, 1) + con(1, 2) + con(2, 1) + con(2, 2));
        for i = 1:size(traindata, 1)
            if(traindata(i,65) == d1 || traindata(i,65) == d2)
                weight = updateWeight(d1, d2, traindata(i, :), weight);
            end
        end
        [weight, con] = testbi(d1, d2, traindata, weight);
        newacc = (con(1,1) +con(2,2)) / (con(1, 1) + con(1, 2) + con(2, 1) + con(2, 2));
        if (newacc <= oldacc)
            break;
        end
        epoch = epoch + 1;
    end
    return
end

