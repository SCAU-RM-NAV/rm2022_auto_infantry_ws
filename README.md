# auto_infantry_ws
自动步兵仿真ROS工作空间

配置于 Ubuntu20.04 noetic

## 关于打开的仿真环境没有场地模型

可将场地模型放入.gazebo（隐藏文件夹，ctrl+h显示）下的models文件夹（如果没有，可自己建一个），然后在gazebo的左上方insert栏中插入，然后点击file中的save world as，保存为文件名.world（一定要带后缀名！！！！），然后在打开仿真环境的launch将原来的world文件修改为刚刚保存的world文件

## 关于gazebo的file中save world as时没反应如何解决

参考https://www.zhihu.com/question/439671228/answer/1985497283

## Tree
```
auto_car/      urdf模型，仿真配置
auto_control/      	云台仿真控制
roborts_msgs/      	机器人控制msgs
teleop_twist_keyboard/	键盘控制
auto_nav/  		机器人导航控制器

```

## 配置环境
1. 将auto_car功能包中的auto_world文件夹放入home目录下的 .gazebo/models(此为隐藏文件夹)
2. gazebo.launch 默认为不开启gazebo gui 修改 为true可以修改打开gui界面
3. 编译环境
```
catkin_make

```

## 一键启动脚本
```
source devel/setup.bash 

sh sh/1-启动仿真.sh 
```

## 开启打点导航

1. 打开工作空间的一个终端
```
source devel/setup.bash 

rostopic pub -r 10 /game_state roborts_msgs/GameStatus "header:
  seq: 0
  stamp: {secs: 0, nsecs: 0}
  frame_id: ''
area: 0
shoot_number: 0.0
health_point: 0.0
game_state: 4
heat_rest: 0.0" 

```
game_state: 4 代表为比赛开始

2. 进入小陀螺模式，可以在RVIZ上打点导航


## 单独启动（可忽略）
* 仿真环境
```
roslaunch auto_car gazebo.launch
```
* 仿真建图
```
roslaunch auto_nav auto_simulink_gmapping.launch
```
* teb导航
```
roslaunch auto_nav navi_simulink.launch
```
* 纯跟踪导航
```
roslaunch auto_nav navi_pure_follow_simulink.launch
```

* 云台控制
```
roslaunch auto_control taurus_control.launch
```


