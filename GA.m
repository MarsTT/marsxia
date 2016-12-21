function varargout = tsp_ga(xy,dmat,pop_size,num_iter,show_prog,show_res)
%tsp_ga旅行商问题（TSP）的遗传算法（GA）
%   查找（近）的最佳解决方案，通过设置一个遗传算法搜索到的旅行商
%   的最短路线（最少的推销员旅行到每个城市准确的一次，回到起点城市）
%
%概要：
%   1、一个单一的推销员旅行到每个城市和完成
%       他从一开始就开始返回城市的路线
%   2、每一个城市都有一次被推销员拜访过
%
%输入：
%   XY（float）是城市位置的NX2矩阵，其中n是城市数量
%   DMAT（float）是一个n×n矩阵的点对点的距离
%   pop_size（scalar integer）是人口规模（应该是被4整除）
%   num_iter（scalar integer）是运行该算法所需迭代次数
%   show_prog（scalar logical）表明GA进步如果真的 布尔类型 真 /假
%   show_res（scalar logical）显示的结果如果真的
%
%输出：
%   opt_rte（整数数组）的算法找到最佳路线
%   min_dist（标量浮点）是最优路径的成本
%
% 2D Example:
%     n = 50;
%     xy = 10*rand(n,2);rand函数产生由在(50, 2)之间均匀分布的随机数组成的数组。
%     pop_size = 60;
%     num_iter = 1e4;
%     show_prog = 1;
%     show_res = 1;
%     a = meshgrid(1:n);
%     dmat = reshape(sqrt(sum((xy(a,:)-xy(a',:)).^2,2)),n,n);
%     [opt_rte,min_dist] = tsp_ga(xy,dmat,pop_size,num_iter,show_prog,show_res);
%
% 3D Example:
%     n = 50;
%     xyz = 10*rand(n,3);
%     pop_size = 60;
%     num_iter = 1e4;
%     show_prog = 1;
%     show_res = 1;
%     a = meshgrid(1:n);
%     dmat = reshape(sqrt(sum((xyz(a,:)-xyz(a',:)).^2,2)),n,n);
%     [opt_rte,min_dist] = tsp_ga(xyz,dmat,pop_size,num_iter,show_prog,show_res);
%
% See also: mtsp_ga, tsp_nn, tspo_ga, tspof_ga, tspofs_ga, distmat
%  
% Author: Joseph Kirk  
% Email: jdkirk630@gmail.com  
% Release: 2.2  
% Release Date: 6/2/09  
% Process Inputs and Initialize Defaults  
nargs = 6;
% nargin  在函数体内部， nargin是用来判断输入变量个数的函数
for k = nargin:nargs-1
    switch k
        case 0
            xy = 10*rand(50,2);
        case 1
            N = size(xy,1);% size：获取数组的行数和列数
            a = meshgrid(1:N); % meshgrid MATLAB中用于生成网格采样点的函数
            dmat = reshape(sqrt(sum((xy(a,:)-xy(a',:)).^2,2)),N,N);%n*n 距离矩阵 （任意两点之间的距离） reshape函数重新调整矩阵的行数、列数、维数
        case 2
            pop_size = 100;% 种群大小
        case 3
            num_iter = 1e4;% 代数
        case 4
            show_prog = 1;% 进化有效
        case 5
            show_res = 1;% 显示结果
        otherwise
    end
end
% Verify Inputs
% 校验输入
[N,dims] = size(xy);
[nr,nc] = size(dmat);
if N ~= nr || N ~= nc
    error('Invalid XY or DMAT inputs!')
end
n = N;
% Sanity Checks
% 理智检查
pop_size = 4*ceil(pop_size/4);% 种群规模（应该是被4整除）
num_iter = max(1,round(real(num_iter(1))));% 运行该算法所需迭代次数  [max] 返回一个数组各不同维中的最大元素
show_prog = logical(show_prog(1));% 表明GA进步如果真的 [L = logical(A)] 输入A为实数数组，返回值L为一个与A同维的逻辑数组，当A中的元素为非零元素时，L中对应的位置返回逻辑1，否则返回逻辑0。
show_res = logical(show_res(1));% 显示的结果如果真的
% Initialize the Population
% 初始化种群
pop = zeros(pop_size,n);% [zeros(m,n)]函数功能：产生m×n的double类零矩阵，zeros(n)产生n×n的全0方阵。
for k = 1:pop_size
    pop(k,:) = randperm(n);% [randperm]函数功能：随机打乱一个数字序列。
end
% Run the GA
% 运行遗传算法
global_min = Inf;% 最优路径的距离
total_dist = zeros(1,pop_size);% 总距离矩阵 1*种群大小
dist_history = zeros(1,num_iter);% 生成1*代数维的零矩阵
tmp_pop = zeros(4,n);% 缓存种群4*n 维的零矩阵
new_pop = zeros(pop_size,n);% 新种群 种群大小*n维的零矩阵
if show_prog% 当进化有效
    pfig = figure('Name','TSP_GA | Current Best Solution','Numbertitle','off');%绘图
end
for iter = 1:num_iter
    % Evaluate Each Population Member (Calculate Total Distance)
    % 任意两个城市之间的距离和（并计算总距离 d）
    for p = 1:pop_size
        d = dmat(pop(p,n),pop(p,1)); % Closed Path 封闭路径
        for k = 2:n
            d = d + dmat(pop(p,k-1),pop(p,k));
        end
        total_dist(p) = d;% 任意两个城市之间的距离和的和
    end
    % Find the Best Route in the Population
    % 在种群中找到最佳路线 
    [min_dist,index] = min(total_dist);% [min()]返回一个数组各不同维中的最小元素
    dist_history(iter) = min_dist;
    if min_dist < global_min% 保留距离最小值
        global_min = min_dist;
        opt_rte = pop(index,:);
        if show_prog
            % Plot the Best Route
            % 绘制最佳路线
            figure(pfig);% figure 能够创建一个用来显示图形输出的一个窗口对象
            rte = opt_rte([1:n 1]);
            if dims == 3, plot3(xy(rte,1),xy(rte,2),xy(rte,3),'r.-');% 创建一个三维坐标下的图
            else plot(xy(rte,1),xy(rte,2),'r.-'); end
            title(sprintf('Total Distance = %1.4f, Iteration = %d',min_dist,iter));
        end
    end
    % Genetic Algorithm Operators
    % 遗传算法
    rand_pair = randperm(pop_size);% randperm 函数功能：随机打乱一个数字序列。
    for p = 4:4:pop_size
        rtes = pop(rand_pair(p-3:p),:);
        dists = total_dist(rand_pair(p-3:p));
        [ignore,idx] = min(dists);
        best_of_4_rte = rtes(idx,:);
        ins_pts = sort(ceil(n*rand(1,2)));% [sort(A)]若A是向量不管是列还是行向量，默认都是对A进行升序排列 [ceil(n)]的意思是向正方向舍入
        I = ins_pts(1);% 取出两个维度的坐标
        J = ins_pts(2);
        % 变异
        for k = 1:4 % Mutate the Best to get Three New Routes 变异最好得到第三条路线
            tmp_pop(k,:) = best_of_4_rte;
            switch k
                case 2 % Flip 翻转
                    tmp_pop(k,I:J) = fliplr(tmp_pop(k,I:J));
                case 3 % Swap 交换
                    tmp_pop(k,[I J]) = tmp_pop(k,[J I]);
                case 4 % Slide 
                    tmp_pop(k,I:J) = tmp_pop(k,[I+1:J I]);
                otherwise % Do Nothing
            end
        end
        new_pop(p-3:p,:) = tmp_pop;
    end
    pop = new_pop;
end
if show_res
    % Plots the GA Results
    % 绘制遗传算法结果
    figure('Name','TSP_GA | Results','Numbertitle','off');
    subplot(2,2,1);
    if dims == 3, plot3(xy(:,1),xy(:,2),xy(:,3),'k.');
    else plot(xy(:,1),xy(:,2),'k.'); end
    % 城市位置
    title('City Locations');
    subplot(2,2,2);
    imagesc(dmat(opt_rte,opt_rte));
    % 距离矩阵
    title('Distance Matrix');
    subplot(2,2,3);
    rte = opt_rte([1:n 1]);
    if dims == 3, plot3(xy(rte,1),xy(rte,2),xy(rte,3));% plot3(x,y,z)用来绘制3维曲线图
    else plot(xy(rte,1),xy(rte,2)); end
    % 总距离
    title(sprintf('Total Distance = %1.4f',min_dist));
    subplot(2,2,4);
    plot(dist_history,'b','LineWidth',2);
    title('Best Solution History');
    % 最佳
    set(gca,'XLim',[0 num_iter+1],'YLim',[0 1.1*max([1 dist_history])]); %[set] Matlab中“坐标轴刻度”的不同风格 
end
% Return Outputs
% 返回结果
if nargout
    varargout{1} = opt_rte;% 通过varargout我们可以得到函数中多个返回值参数的返回值
    varargout{2} = min_dist;
end