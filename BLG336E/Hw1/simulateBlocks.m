function simulateBlocks (fileName, numberBlocks)
fileID = fopen(fileName);
C = fscanf(fileID,'%d %d %d %c');
fclose(fileID);
s = size(C);
index = 0;
numberStates = s(1)/(4*numberBlocks);
for i = 1:numberStates
rectangle('Position',[0, 0, 6,6],'FaceColor', 'w');   
for r = 1:numberBlocks
if C(r*4) == 104
    if r == 1
          rectangle('Position',[C(4*index + 2) - 1, 6 - C(4*index + 1), C(4*index + 3),1],'FaceColor', 'b');
    else
          rectangle('Position',[C(4*index + 2) - 1, 6 - C(4*index + 1), C(4*index + 3),1],'FaceColor', 'r');
    end
else
    rectangle('Position',[C(4*index + 2) - 1, 6 - C(4*index + 1), 1, C(4*index + 3)],'FaceColor', 'r');
end
index = index +1;
end
pause(3);
end
end