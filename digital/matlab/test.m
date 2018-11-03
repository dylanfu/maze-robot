clear
clc

startlocation = [1,2];
targetlocation = [6,2];

INF = 9000;
[retmap] = map_convert('test.txt');
[ROW,COL] = size(retmap);
numNodes = (ROW*COL) - sum(sum(retmap));

nodes = ones(numNodes,2) * -1;
cons = zeros(numNodes,1);
heurst = zeros(numNodes,1);
dist = ones(numNodes,1) * INF;
d_h = ones(numNodes,1) * INF;
prev = ones(numNodes,2) * -1;

ind = 1;
for r=1:ROW
    for c=1:COL
        if retmap(r,c)==0
            nodes(ind,1) = r;
            nodes(ind,2) = c;
            heurst(ind,1) = sqrt( (targetlocation(1)-r)^2 + (targetlocation(2)-c)^2 );
            ind = ind+1;
        end
    end
end

posIndex = nodeIndex(startlocation, nodes, numNodes);
dist(posIndex,1) = 0;
d_h(posIndex,1) = heurst(posIndex,1);

safety=0;
while safety<100
    curNodeInd = minIndex(d_h, cons, numNodes);
    
    if curNodeInd == nodeIndex(targetlocation, nodes, numNodes) || curNodeInd == -1
        break;
    end

    for i=1:numNodes
        if cons(i,1) == 0 && isNextTo(nodes(i,1), nodes(i,2), nodes(curNodeInd,1), nodes(curNodeInd,2))
            dist(i,1) = 1 + dist(curNodeInd,1);
            d_h(i,1) = dist(i,1) + heurst(i,1);
            prev(i,1) = nodes(curNodeInd,1);
            prev(i,2) = nodes(curNodeInd,2);
        end
    end
    cons(curNodeInd,1) = 1;
    safety = safety+1;
end

reversePath = ones(numNodes,2) * -1;
curNode = [targetlocation(1),targetlocation(2)];

ind = 1;
safety = 0;
while safety < 100
    reversePath(ind,1) = curNode(1);
    reversePath(ind,2) = curNode(2);

    if curNode(1) == startlocation(1) && curNode(2) == startlocation(2)
        break;
    end

    curNodeInd = nodeIndex(curNode, nodes, numNodes);
    curNode(1) = prev(curNodeInd,1);
    curNode(2) = prev(curNodeInd,2);

    ind=ind+1;
    safety=safety+1;
end

rem = numNodes;
ind = 1;
while rem > 0
    if (reversePath(rem,1) ~= -1)
        retsteps(ind,1) = reversePath(rem,1);
        retsteps(ind,2) = reversePath(rem,2);
        ind=ind+1;
    end
    rem=rem-1;
end

function ind = nodeIndex(node, nodes, numNodes)
ind = -1;
for i=1:numNodes
    if node(1)==nodes(i,1) && node(2)==nodes(i,2)
        ind=i;
    end
end
end

function min = minIndex(array, cons, numNodes)
min = -1;
for i=1:numNodes
    if cons(i,1)==0
        min = i;
        break;
    end
end
if (min == -1)
    return
end
for i=1:numNodes
    if array(i,1)<array(min,1) && cons(i,1)==0
        min = i;
    end
end
end

function check = isNextTo(r1, c1, r2, c2)
if (r1==r2-1 && c1==c2) || (r1==r2+1 && c1==c2) || (r1==r2 && c1==c2-1) || (r1==r2 && c1==c2+1)
    check=1;
else
    check=0;
end
end