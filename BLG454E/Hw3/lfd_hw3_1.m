%
% @Author
% Team Name: Bee Meister
% Student Name: Emre ?zdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 21/05/2017
%

% Question 1
% Examine the dataset (You have train and test set separetely in this homework).
% Classify given dataset using Neural Network (MLP).
% Write comments below codes you implemented.


trainSet = 'optdigits.tra';
testSet = 'optdigits.tes';

traindata = csvread(trainSet);
testdata = csvread(testSet);

weight = zeros(10, 10, 65);

[weight, ep] = train(traindata, weight);
epoch = zeros(45,1);
k = 1;
for index = 1: 10
    for j = index+1:10
        epoch(k) = ep(index,j);
        k = k + 1;
    end
end

% TRAIN ACCURACY like a test Set (train and test set is same)

[weight, confusionTrain] = test(traindata, weight);
trainAcc = zeros(size(confusionTrain, 1),1);

for index = 1:size(confusionTrain,1)
    trainAcc(index) = (confusionTrain(index,1)+confusionTrain(index,4)) / (confusionTrain(index,1)+confusionTrain(index,2)+confusionTrain(index,3)+confusionTrain(index,4)); 
end

sum = 0;
for index = 1:size(trainAcc,1)
    sum = sum + trainAcc(index); 
end

trainAvarage = sum / size(trainAcc,1);
fprintf('Train set accuracy is: %g\n', trainAvarage);


% TEST ACCURACY

[weight, confusionTest] = test(testdata, weight);
testAcc = zeros(size(confusionTest, 1),1);

for index = 1:size(confusionTest,1)
    testAcc(index) = (confusionTest(index,1)+confusionTest(index,4)) / (confusionTest(index,1)+confusionTest(index,2)+confusionTest(index,3)+confusionTest(index,4)); 
end

sum = 0;
for index = 1:size(testAcc,1)
    sum = sum + testAcc(index); 
end

testAvarage = sum / size(testAcc,1);
fprintf('Test set accuracy is: %g\n', testAvarage);

% (You should evaluate classification results using 10-fold cross validation)
% CROSS VALIDATION

allData = [traindata; testdata];
testSize = size(allData,1)/10;

allSum = 0;
for i = 0:9
    cvTrainingData = allData;
    cvTrainingData(testSize*i+1:testSize*(i+1), :) = [];
    cvTestData = allData(testSize*i+1:testSize*(i+1), :);
    weight = zeros(10, 10, 65);
    [weight, ep] = train(cvTrainingData, weight);
    epoch = zeros(45,1);
    k = 1;
    for index = 1: 10
        for j = index+1:10
            epoch(k) = ep(index,j);
            k = k + 1;
        end
    end
    [weight, confusionTest] = test(cvTestData, weight);
    testAcc = zeros(size(confusionTest, 1),1);

    for index = 1:size(confusionTest,1)
        testAcc(index) = (confusionTest(index,1)+confusionTest(index,4)) / (confusionTest(index,1)+confusionTest(index,2)+confusionTest(index,3)+confusionTest(index,4)); 
    end

    sum = 0;
    for index = 1:size(testAcc,1)
        sum = sum + testAcc(index); 
    end

    testAvarage = sum / size(testAcc,1);
    allSum = allSum + testAvarage;
    %fprintf('Test set accuracy is: %g\n', testAvarage);
end
fprintf('10-fold cross validation accuracy is: %g\n', allSum/10);