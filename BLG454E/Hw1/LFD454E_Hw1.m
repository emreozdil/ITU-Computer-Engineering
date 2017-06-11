%
% @Author
% Team Name: Bee Meister
% Student Name: Emre Özdil, Merve Ecevit
% Student ID : 150120138, 150140115
% Date: 09/03/2017
%

% loading Data
load('hw1.mat')

% Training Set includes elements of class0 from 1 to 800 and
% elements of class1 from 1001 to 1800
trainingSet = d(1:800,:);
trainingSet(801:1600,:) = d(1001:1800,:);

% Test Set includes remaining elements of class0 and class1
testSet = d(801:1000, 1:2);
testSet(201:400,:) = d(1801:2000,1:2);

% class 0 and class 1 are used to plot the points
class0 = d(1:800,1:2);
class1 = d(1001:1800,1:2);

% elements of class0 are red points, elements of class1 are blue points,
% and test elements are green points
figure('Name','Training Set and Test Set');
plot(class0(:,1), class0(:,2) ,'b.');
hold on;
plot(class1(:,1), class1(:,2), 'r.');
hold on;
plot(testSet(:,1), testSet(:,2) ,'g.');


% KNN3 implementation

% new class0 and class1 variables for KNN3 
class0knn3 = class0;
class1knn3 = class1;

% knnsearch function is used to find nearest points 
knn3 = knnsearch(trainingSet(:,1:2),testSet,'k',3);

% if dataSet class and knn3 class are same, accuracy will be increased by 1
accuracyKNN3=0;

% traverse testSet
for n=1:400
    counter = 0;
    % traverse nearest points
    for i=1:3
       % using counter to decide class
       if(knn3(n,i)>800)
           counter = counter + 1;
       end
    end
    % if counter equals to 2 or 3, point is class1, else class0
    if(counter>1)
        class1knn3 = cat(1, class1knn3, testSet(n,:));
        % 201 to 400 class1
        if(n>200)
            accuracyKNN3 = accuracyKNN3 + 1;
        end
    else
        class0knn3 = cat(1, class0knn3, testSet(n,:));
        % 1 to 200 class0
        if(n<201)
            accuracyKNN3 = accuracyKNN3 + 1;
        end
    end
end

% Figure KNN3
figure('Name','KNN3');
plot(class0knn3(:,1), class0knn3(:,2) ,'b.');
hold on;
plot(class1knn3(:,1), class1knn3(:,2), 'r.');

% accuracy calculating and printing
accuracyKNN3 = accuracyKNN3/400;
knn3accuracy = sprintf( 'Accuracy of KNN3 = %.4f\n', accuracyKNN3 ) ;
disp(knn3accuracy);


% KNN5 implementation

% new class0 and class1 variables for KNN5 
class0knn5 = class0;
class1knn5 = class1;

% knnsearch function is used to find nearest points 
knn5= knnsearch(trainingSet(:,1:2),testSet,'k',5);

% if dataSet class and knn3 class are same, accuracy will be increased by 1
accuracyKNN5=0;

% traverse testSet
for n=1:400
    counter = 0;
    % traverse nearest points
    for i=1:5
        % using counter to decide class
       if(knn5(n,i)>800)
           counter = counter + 1;
       end
    end
    % if counter equals to 3, 4, or 5, point is class1, else class0
    if(counter>2)
        class1knn5 = cat(1, class1knn5, testSet(n,:));
        % 201 to 400 class1
        if(n>200)
            accuracyKNN5 = accuracyKNN5 + 1;
        end
    else
        class0knn5 = cat(1, class0knn5, testSet(n,:));
        % 1 to 200 class0
        if(n<201)
            accuracyKNN5 = accuracyKNN5 + 1;
        end
    end
end

% Figure KNN5
figure('Name','KNN5');
plot(class0knn5(:,1), class0knn5(:,2) ,'b.');
hold on;
plot(class1knn5(:,1), class1knn5(:,2), 'r.');

% accuracy calculating and printing
accuracyKNN5 = accuracyKNN5/400;
knn5accuracy = sprintf( 'Accuracy of KNN5 = %.4f\n', accuracyKNN5 ) ;
disp(knn5accuracy);
