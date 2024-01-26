1.下载kernel文件,复制到fs-image/binaries目录下
wget http://www.cs.utexas.edu/~parsec_m5/x86_64-vmlinux-2.6.28.4-smp

2.下载PARSEC对应的PAL code文件, 复制到fs-image/binaries目录下
wget http://www.cs.utexas.edu/~parsec_m5/tsb_osfpal

3.下载PARSEC-2.1 Disk Image并解压到fs-image/disks目录中
wget http://www.cs.utexas.edu/~parsec_m5/x86root-parsec.img.bz2
bzip2 -d x86root-parsec.img.bz2

4.下载PARSEC script生成包，并解压到benchmark目录下
wget http://www.cs.utexas.edu/~parsec_m5/TR-09-32-parsec-2.1-alpha-files.tar.gz
tar zxvf TR-09-32-parsec-2.1-alpha-files.tar.gz

5.生成script
 ./writescripts.pl <benchmark> <nthreads>

 我生成的脚本是blackscholes,利用gem5进行全系统测试
 ./writescripts.pl blackscholes 4

6.运行生成的脚本
M5_PATH=/home/hsc/fs-image ./build/X86/gem5.opt ./configs/example/fs.py -n 2 --script=../benchmark/TR-09-32-parsec-2.1-alpha-files/blackscholes_4c_test.rcS --disk-image x86root-parsec.img --kernel x86_64-vmlinux-2.6.28.4-smp

7.连接测试
telnet localhost 3456


修改的代码位置(箭头位置)
+-- nvmain/
|     +-- DataEncoders/
|     |        +-- FlipNWrite/
|     |        |       +--  FlipNWrite.h
|     |        |       +--  FlipNWrite.cpp
|     |        |       +--  SConscript
|     |        +-- DH-PSO/                  <-  
|     |        |       +--  DH-PSO.h        <-
|     |        |       +--  DH-PSO.cpp      <-
|     |        |       +--  SConsript           <-
|     |        +-- DataEncoderFactory.cpp       <-

nvmain/Config/PCM_MLC_example.config,在文件的末尾,加入如下内容:
DataEncoder DH-PSO

编译
scons --build-type=fast

测试
./nvmain.fast Config/PCM_MLC_example.config Tests/Traces/hello_world.nvt 1000000