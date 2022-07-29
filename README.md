# Project: implement the Rho method of reduced SM3

### 刘硕-202000460043-shuosureS

##  简介

本项目通过实现了rho方法并且通过调用openssl中的sm3来验证碰撞是否成功，rho方法通过不断地循环寻找目标bit的碰撞，这里采用了前32bit，成功碰撞便会输出时间。

## 代码说明

代码很多部分与生日攻击的代码相同，像sm3的输入输出都是一样的

```c_cpp
    unsigned char tinput[256] = "";
    int tlen;
    unsigned char tagart[32];
    unsigned char input[256] = "";
    int ilen = 0;
    unsigned char output[32];
```

RHO方法的map函数用了x=x*x+1,q和i是可以改变的，这里设置q和i的最大值为60000，这样平方时不会超出unsigned int的最大值。每次循环判断输出的前32位是否相同。记录时间。

```c_cpp
 #define MAX 60000
 unsigned int q = 11;
    unsigned int i = 51;
    int start, end;
    start = clock();
    while (1) {

        q = (q * q + 1)%MAX ;
        ilen = inttohex(q, input);
        i = (i *i  + 1)%MAX ;
        i = (i *i  + 1)%MAX ;
        tlen = inttohex(i, tinput);
        sm3_openssl(tinput, tlen, tagart);
        sm3_openssl(input, ilen, output);

        if (output[0] == tagart[0]&& output[1] == tagart[1]&& output[2] == tagart[2]&& output[3] == tagart[3])
        {
            end = clock();
            printf("攻击成功\n");
            printf("time=%dms\n", end - start);

            break;
        }
        
    }
```

## 结果

由于直接调用的openssl，sm3的速度很快，成功碰撞的时间也很快

![image text](https://github.com/shuosureS/rho_sm3_openssl/blob/master/99bcbadd4e25d0f2a6dbc4804651cfcc.png)
