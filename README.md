# Sudoku
结对编程作业，可以实现要求的全部功能，命令格式与要求完全相同
# tips
对于-s参数，从指定路径读取sudoku game后，求解并存入txt文件，由于雨课堂中的-s用法示例只提到 “ 读取若干个数独游戏 ”，而按照给定格式，-s后面只指定了读取game文件路径，而没有指定需要求解的数独游戏个数，我们默认只求解前6个，并将它们的解存入txt文件。如果需要求解更多个数独，需要更改main.cpp中的代码：

main函数处理-s参数命令的代码：
```c++
else if (!strcmp(argv[1], "-s")) {
  char* gamePath = argv[2];

  if (gamePath != NULL) {
    int size = 1;
    ifstream read;
    read.open(gamePath);
    int** sudo = RequestMemory(0);
    int i = 0;
    while (read_from_text(sudo, read)) 
    {
      list<int**> sudo_list;
      GetAnswer(sudo, size, &sudo_list);

      list<int**>::iterator it_1 = sudo_list.begin();
      while (it_1 != sudo_list.end()) {
        output_result(*it_1);
        it_1++;
      }

      i++;
      if (i == 6)
        break;
    }
    cout << "game求解完毕" << endl;
    DeleteMemory(sudo);
  }
  else {
    cout << "please input something after -s" << endl;
    return 0;
  }
}
```

需要将判断是否break的 “if (i == 6)” 语句中的 “6” 改为需要求解数独游戏的个数，重新编译链接得到可执行文件myShudu.exe即可
