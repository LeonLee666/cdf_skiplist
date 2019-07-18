# AIskiplist

本文是针对学术论文《李梁,吴刚,王国仁. **面向数据特征的内存跳表优化技术**.软件学报.》的实验项目。主要通过数据的分布信息和热度信息优化跳表的QPS

## Build
项目依赖google的单元测试库GoogleTest.

`git clone https://gitee.com/bombel/cdf_skiplist.git`

`cd cdf_skiplist/thirdparty/`

`git clone https://gitee.com/goa/googletest.git`

`cd ../cmake-build-debug/`

`cmake ..`

`make`

## Run

run 目录是具体的实验运行脚本,实验合成数据集采用R语言脚本生成.

plot目录是实验结果可视化的python脚本

