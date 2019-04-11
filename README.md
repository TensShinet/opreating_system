# 如何使用 OSLAB



1. 在 `oslab` 目录下面运行 ./run 运行 linux0.11 接着在 命令行里面输入 c 表示编译
2. 在 `oslab` 目录下面运行 ./run init 初始化文件
3. 初始化文件以后在 `linux0.11` 目录下运行 make all
4. 在 `oslab` 目录下运行  sudo ./mount-hdc 访问硬盘，hdc 下面的东西就是 linux0.11 的文件
5. 卸载 hdc 的时候输入 sudo umount hdc