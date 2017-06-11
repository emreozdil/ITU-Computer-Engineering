%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

%
% calculate the output of the perceptron before sign
%
function res = calcOutput(w, x)
    res = w(1);
    for i = 1:64
        res = res + (w(i+1) * x(i));
    end
end